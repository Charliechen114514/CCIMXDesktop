# IMX6ULL 内核调试方案与仿真学习方案

## 前言

​	笔者现在打算开始仔细的聊一聊内核的调试方案（注意，没有模块部分，模块部分笔者没有进行完全的测试，但是大致的办法笔者会给出），笔者使用的内核是6.12.3这个新内核，办法是使用kgdb + 串口的经典办法进行内核调试（笔者没钱买JTAG，而且板子上也没有接口，KGDB的方案笔者也认为更加的轻量，现代和方便。），然后投射到我们的VSCode上，当然，终端GDB和VSCode的办法笔者都会介绍

​	下面，笔者准备计划简单说一说笔者的调试方案（笔者实际上不太满意，因为实在是发现效果不算很丝滑），后面还会附上一个如果只是想丝滑的调试内核的QEMU调试方案

## 调试之前的准备

​	在我们准备好调试之前，我们需要做的事情是给我们的内核打补丁。你需要做的事情很简单，就是查看我们的内核有没有编译进入相关的辅助调试信息。

```
➜  cat config | grep DEBUG_INFO
CONFIG_DEBUG_INFO=y
# CONFIG_DEBUG_INFO_NONE is not set
CONFIG_DEBUG_INFO_DWARF_TOOLCHAIN_DEFAULT=y
# CONFIG_DEBUG_INFO_DWARF4 is not set
# CONFIG_DEBUG_INFO_DWARF5 is not set
# CONFIG_DEBUG_INFO_REDUCED is not set
CONFIG_DEBUG_INFO_COMPRESSED_NONE=y
# CONFIG_DEBUG_INFO_COMPRESSED_ZLIB is not set
# CONFIG_DEBUG_INFO_COMPRESSED_ZSTD is not set
# CONFIG_DEBUG_INFO_SPLIT is not set
➜  cat config | grep KGDB
# CONFIG_SERIAL_KGDB_NMI is not set
CONFIG_HAVE_ARCH_KGDB=y
CONFIG_KGDB=y
CONFIG_KGDB_HONOUR_BLOCKLIST=y
CONFIG_KGDB_SERIAL_CONSOLE=y
# CONFIG_KGDB_TESTS is not set
# CONFIG_KGDB_KDB is not set
```

> 如你所见，我开启的是DEBUG_INFO调试信息，CONFIG_DEBUG_INFO_DWARF_TOOLCHAIN_DEFAULT也就是DWARF信息格式是默认，以及开启了KGDB（但是没有开启KDB，回跟我们习惯的调试撞车，而且那属于搭建另一套完整的调试方案了，可以参考其他的博客）
>
> 如果你计划纯GDB + 侧重模块调试，记得开启GDB_SCRIPTS，开启gdb的时候加载这个脚本可以辅助你的调试更近一步。
>
> ```
> ➜  cat config | grep SCRIPTS
> CONFIG_GDB_SCRIPTS=y
> ```

​	准备完成之后，你就可以开始编译内核了，开启这样的内核编译，你需要注意的是，会把所有的文件重新编译一次，笔者的建议是自己在拷贝一份编译后的无Debug Info的内核源码，这样你可以完全建立一份对等的调试版本的内核，然后在克隆版本的内核源码中开启调试构建。准备完成之后，带好你的设备树和内核，放到tftp目录之下，或者任何你能够传递给板子内核的办法，我们需要调整bootargs参数了。

## 调整bootargs参数

​	**我看到很多博客是将调试串口和日志串口混在同一个，然后使用gdb-agent-proxy代理分用串口为两个UDP服务器，这个时候使用telnet连接端口进行调试和日志观察**，这个方案听起来不错，但是你也看到了，满天飞的日志乱码，这就是内核端没有实现分用的麻烦之处。笔者测试的在VScode上的调试更是把笔者使用的Microsoft GDB调试插件搞崩了（哦，他喜欢做一点额外的事情，比如说非得多发点东西确认，但是遗憾的是KGDB不认，会送给你一大堆乱码把插件搞炸了）

​	所以，对于如果**已经使能了第二个串口**的朋友，上面的方案就显得很没有必要了，如何使能第二个串口（注意，如果你是使用了其他板子，自己评估一下有没有第二个串口？没有的话，还是老老实实gdb-agent-proxy分用端口吧，这个救不了）笔者在之前的博客中提到了，这里不再赘述。笔者最后的UART端口是ttymuxc2，因此，我们需要这样调整我们的bootargs

```
console=ttymxc0,115200 kgdboc=ttymxc2,115200 kgdbwait ... // 其他的参数照旧
```

​	kgdboc说明我们的调试沟通串口是第二个串口，跟我们的操作端口是分开的，当然，自然我们需要设置一下波特率，最后的kgdbwait，是当我们希望调试内核启动后，内核的用户控制台启动之前内核的行为的时候，最好打开的。

​	提前说一下，内核的调试跟普通应用程序的调试很不一样，因此等会即使我们使用了VSCode + GDB插件，也没办法完全的按照如同应用程序那样丝滑的调试，因为内核默认总是以运行为优先，想要调试，就必须要在下位机中手动打调试中断让内核挂起来（这就是为什么最好日志控制台和调试控制台分离了）

​	我们传递好调试的内核和设备树之后，就可以按照预期的开始调试了。

## 连接内核，准备调试

### 终端GDB调试方案

​	我们设置了kgdbwait，这个时候，内核就会等待我们用户态GDB的连接，这个时候，我们就可以开始调试了。由于笔者的端口分开了，笔者是日志端口介入了Windows的XShell，这个时候我只需要看XShell的日志和控制内核行为即可，Ubuntu24.04来负责指挥调试行为。

​	笔者使用的是gdb-multiarch，输入

```
gdb-multiarch /path/to.your/vmlinux!
```

​	设置一下（喜欢偷懒的笔者建议写一个gdbinit脚本，这样你不用每一次都输入这些玩意）

```
set architecture arm
set serial baud 115200
target remote /dev/ttyUSB0	# 在连接之前，确保/dev/ttyUSB0是可以被你执行的，至少权限必须是777，临时调试就用sudo chmod 777 /dev/ttyUSB0, 持久的可以加入设备规则组，但是笔者没有采用，我很少调试内核
```

​	然后等待连接，这个时候，我们的终端就会提示我们已经在arch_kgdb_breakpoint函数上等待了，输入c回车之后，内核就会停止挂起！然后继续运行，我们这个时候在日志端口上正常的操作（比如说激活我们的终端，完成一些用户态操作），想要进入调试状态很简单：

```
echo g > /proc/sysrq-trigger
```

​	这个时候你发现日志终端就僵死，调试终端会告诉你断点停下来了，这个时候，你就可以开始正常打断点调试即可。一切照旧！

### VSCode

```
{
    "version": "0.2.0",
    "configurations": [
      {
        "name": "Attach to KGDB Remote",
        "type": "cppdbg",
        "request": "launch",
        // 注意，指向的是没有压缩的符号文件，下面所示！
        "program": "/home/charliechen/imx6ull/linux-imx-debug/vmlinux",   
        "cwd": "${workspaceFolder}",
        "MIMode": "gdb",
        "miDebuggerPath": "/usr/bin/gdb-multiarch",       // 远程 Linux 上的 GDB
        "setupCommands": [
          { "text": "set architecture arm" },   
          { "text": "set serial baud 115200" },          
          { "text": "target remote /dev/ttyUSB0" }
        ],
        "externalConsole": false
      }
    ]
  }
  
```

​	对的，就是这样，然后在内核被KGDB挂起的时候，摁下debug小按钮就行了，之后的调试中，你需要先`echo g > /proc/sysrq-trigger`再打断点！不然的话断点会失效，不起作用！

## QEMU仿真模拟

​	QEMU的仿真模拟可以实现更专一的对内核层次的调试，而且这个时候由于运行的是虚拟机，调试上就更接近应用程序了，但是麻烦的地方在于，他没法完全模拟硬件特性。因此，笔者没有特别认真的探索这个方案。

​	笔者要提醒的是，QEMU是没有对IMX6ULL这款芯片进行支持的，只有IMX6UL，提醒你，**不要只看差了一个L，两个完全没法互用！设备树的解析规则不一样，回直接导致内核挂死**。

​	因此，笔者是使用了vpressa9这个仿真方案：

```
qemu-system-arm -M vexpress-a9 -m 512M \
-kernel arch/arm/boot/zImage \
-dtb arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb \
-drive file=/home/charliechen/imx6ull/nfs/rootfs.ext4,format=raw,if=sd \
-append "root=/dev/mmcblk0 rw rootfstype=ext4 console=ttyAMA0" \
-nographic \
-S -gdb tcp::1234 \
-monitor telnet:127.0.0.1:5555,server,nowait
```

`qemu-system-arm`
 表示使用 QEMU 模拟 ARM 架构的系统。

------

`-M vexpress-a9`
 指定模拟的平台为 **ARM Cortex-A9 的 Versatile Express 板子**，这是 QEMU 中广泛支持的一个 ARM 板子，常用于内核测试。

------

`-m 512M`
 指定分配给虚拟机的内存大小为 **512MB**。默认是 128MB，不够的话会导致内核或用户空间无法正常运行。

------

`-kernel arch/arm/boot/zImage`
 指定内核镜像为 zImage。路径是你编译好的内核镜像的位置。

------

`-dtb arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb`
 使用的设备树文件，**vexpress-a9 板子的官方匹配设备树**，与 `-M vexpress-a9` 配合使用。

------

`-drive file=/home/charliechen/imx6ull/nfs/rootfs.ext4,format=raw,if=sd`
 挂载一个存储设备作为 **SD 卡**。

- `file=...` 指定要挂载的 ext4 文件系统映像文件
- `format=raw` 表明这是个裸映像，不是 qcow2 等格式
- `if=sd` 指定以 SD 卡设备模拟，最终在系统内会作为 `/dev/mmcblk0`

------

`-append "root=/dev/mmcblk0 rw rootfstype=ext4 console=ttyAMA0"`
 这是传给内核的启动参数：

- `root=/dev/mmcblk0` 指定根文件系统所在的设备
- `rw` 表示以读写方式挂载根文件系统
- `rootfstype=ext4` 指定文件系统类型
- `console=ttyAMA0` 指定控制台使用 ARM PrimeCell UART0（vexpress 默认串口设备）

------

`-nographic`
 关闭图形界面，将串口输出和标准输入输出重定向到当前终端，非常适合串口调试。

------

`-S`
 **不自动启动 CPU**。进入后 QEMU 会卡在第一条指令处，直到你通过 GDB 或 monitor 手动让它运行，常用于调试。

------

`-gdb tcp::1234`
 开启 GDB 服务器，监听 1234 端口。你可以用 GDB 通过 `target remote :1234` 连接上来调试内核。

------

`-monitor telnet:127.0.0.1:5555,server,nowait`
 开启 QEMU monitor，并将其绑定为一个 telnet 服务器，监听 127.0.0.1:5555，允许你从另一个终端通过 telnet 登录 monitor 执行 QEMU 内部命令（例如 `info registers`、`xp`、`stop`、`cont` 等）。











