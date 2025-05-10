# IMX6ULL 最新方案移植教程中间间系列1——USB WLAN网卡移植方案

​	碎碎念：最近打完蓝桥杯之后就一直忙着迁移所有的中间件到新内核上了，基本上除了OV2640目前没有处理好，其他的都处理好了，很快一些移植教程就会发布。

​	需要注意的是——移植教程更加侧重于——如何做才能跑通，而不是“为什么这样做”。因此，对原理好奇的朋友，可能要等待的更长一些时间了！

​	值得一题的是，这里笔者需要说明的是笔者移植的内核是6.12.3，对于2025年来讲，这个内核非常新。因此还在拿老内核（对，就那个基本上我搜到的教程全用的4.1.15的）的朋友，这个的参考价值没那么大。

## 前言

​	这篇教程尝试在2025年4月时最新方案移植好我们的USB无线网卡，这个无线网卡笔者是按照正点原子的RTL8188EUS为芯片的USB无线网卡作为范例，对于使用其他型号的USB网卡的朋友，可以参考笔者的方案进行类比移植。

## Step1：添加社区支持的USB驱动

​	有点难绷的是——正点原子给的是已经过时的驱动，他是没法用在新内核的，使用新内核的朋友不要冒险修改，不然肯定会出现各种奇怪的问题（这是因为引用了太多旧内核的符号）

​	[点击这里，这个是社区对8188EUS的驱动支持](https://github.com/aircrack-ng/rtl8188eus.git)，这个也是笔者找到的可行的。

```
git clone https://github.com/aircrack-ng/rtl8188eus.git
```

​	下一步就是编译了，这里，我们的编译流程非常的简单，只需要指定目标内核的根目录和使用的交叉编译前缀，就完事 了。

```
make KSRC=/home/charliechen/imx6ull/linux-imx/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```

​	这里是笔者的例子，编译器的选型和内核的根目录请自行调整。

​	之后，我们就可以把得到的模块文件拷贝到我们的根文件系统上了。

```
cp /home/charliechen/imx6ull/rtl8188eus/8188eu.ko /home/charliechen/imx6ull/nfs/rootfs/module_test/
```

​	如果你找不到8188eu.ko，先看编译日志有没有报错，报错的自行解决（提示，需要用比较新的编译器，不清楚见不兼容旧编译器的写法），然后试试在项目的根文件下开找：`find / -name "8188eu.ko"`。

​	然后你需要做的事情是——打开你的板子，然后在插好USB网卡的时候，加载你的内核。笔者的日志如下：

```
~ # lsmod
Module                  Size  Used by    Tainted: G  
gt9147                 12288  0 		# 这个是笔者的GT9147驱动LCD触摸屏的，与我们的本章没有任何关系
~ # insmod /lib/modules/8188eu.ko 
[   85.872855] usbcore: registered new interface driver 8188eu
~ # lsmod
Module                  Size  Used by    Tainted: G  
8188eu               1101824  0 	# 这个就是我们新加的驱动
gt9147                 12288  0 
```

​	现在，我们就来插入USB网卡（首先你需要确保你的芯片是8188eu的），我们一插入，其USB子系统就嗅探到了新的USB设备介入，跟我们挂载的8188eu内核对接上，当出现`bFWReady == _FALSE call reset 8051...`的时候，我们的网卡就被正确的复位。

```
~ # [  318.913239] usb 1-1.3: new high-speed USB device number 4 using ci_hdrc
[  319.135646] usb 1-1.3: New USB device found, idVendor=0bda, idProduct=8179, bcdDevice= 0.00
[  319.144301] usb 1-1.3: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[  319.151788] usb 1-1.3: Product: 802.11n NIC
[  319.156148] usb 1-1.3: Manufacturer: Realtek
[  319.160493] usb 1-1.3: SerialNumber: 000F00C00156
[  319.175111] bFWReady == _FALSE call reset 8051...
```

​	但是这个时候，我们的WIFI网卡还不可用

```
~ # ifconfig
eth0      Link encap:Ethernet  HWaddr B8:AE:1D:01:00:01  
          inet addr:10.41.0.2  Bcast:10.41.0.255  Mask:255.255.255.0
          inet6 addr: fe80::baae:1dff:fe01:1/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:9830 errors:0 dropped:0 overruns:0 frame:0
          TX packets:4533 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:12522726 (11.9 MiB)  TX bytes:772126 (754.0 KiB)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
```

​	看到这里是只有我们的网卡0的和本地回环的。我们需要看看内核的所有网卡。

```
~ # ifconfig -a
can0      Link encap:UNSPEC  HWaddr 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  
          NOARP  MTU:16  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:10 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
          Interrupt:217 

eth0      Link encap:Ethernet  HWaddr B8:AE:1D:01:00:01  
          inet addr:10.41.0.2  Bcast:10.41.0.255  Mask:255.255.255.0
          inet6 addr: fe80::baae:1dff:fe01:1/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:9865 errors:0 dropped:0 overruns:0 frame:0
          TX packets:4564 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:12555182 (11.9 MiB)  TX bytes:777036 (758.8 KiB)

eth1      Link encap:Ethernet  HWaddr FE:98:37:F8:18:A3  
          BROADCAST MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

sit0      Link encap:IPv6-in-IPv4  
          NOARP  MTU:1480  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

wlan0     Link encap:Ethernet  HWaddr 00:0F:00:C0:01:56  
          BROADCAST MULTICAST  MTU:2312  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
```

​	一个鼓舞人心的消息！我们看到了我们的WLAN0了，这个时候只需要把网卡激活即可：

```
~ # ifconfig wlan0 up
[  529.545104] ==> rtl8188e_iol_efuse_patch

~ # ifconfig 
eth0      Link encap:Ethernet  HWaddr B8:AE:1D:01:00:01  
          inet addr:10.41.0.2  Bcast:10.41.0.255  Mask:255.255.255.0
          inet6 addr: fe80::baae:1dff:fe01:1/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:9934 errors:0 dropped:0 overruns:0 frame:0
          TX packets:4625 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:12568432 (11.9 MiB)  TX bytes:787250 (768.7 KiB)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

wlan0     Link encap:Ethernet  HWaddr 00:0F:00:C0:01:56  
          inet6 addr: fe80::20f:ff:fec0:156/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:2312  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:8 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
```

​	非常好，这里我需要说明的是，我们的内核可以正常的认出来我们的USB网卡。如果拉不起来，看看是不是笔者使用的RTL8188EUS，RTL8188CUS的朋友，内核里就有驱动，但是正点说旧版本的驱动是不稳定的，但是我的内核新正点教程内核小10年，因此不好说，建议如果懒得找社区的朋友试一试内核自带的，但是要注意的是——你可能需要建立modprobe环境，对8192cu.ko扫描一次依赖之后，依次的进行挂载（笔者尝试发现是4个，但是依赖关系忘记了，这个事情问问GPT，我就是让GPT分析符号找的）

## Step2：添加基础的Wifi信息获取工具：wireless tools

**Wireless Tools** 是一组用于 Linux 系统中无线网络接口配置和管理的命令行工具。它由 Jean Tourrilhes 开发，主要用于基于 Wireless Extensions 接口的无线设备，虽然在较新的系统中已逐渐被 `iw` 和 `nl80211` 所取代，但在很多传统设备和嵌入式系统中仍然广泛使用。

Wireless Tools 的主要组成工具如下：

**1. iwconfig**
 用于查看和配置无线网络接口的参数。类似于 `ifconfig`，但专用于无线网络。你可以用它设置 ESSID（网络名称）、模式（如 Managed 或 Ad-Hoc）、频率、信道、速率等。

**2. iwlist**
 用于扫描周围的无线网络，显示每个网络的详细信息，例如信号强度、加密方式、频率等。

**3. iwspy**
 用于监视和记录特定无线客户端（通过 MAC 地址识别）的信号质量和强度。这个工具现在已经很少使用。

**4. iwpriv**
 用于设置驱动程序特定的参数，这些参数不属于标准的 Wireless Extensions 接口。每个无线网卡驱动提供的命令可能都不同。

**5. ifrename**
 用于为网络接口分配一致的名称（例如按 MAC 地址命名接口），不过这部分功能在现代系统中多由 `udev` 管理。

​	这几个东西，我们主要用的是iwlist，因为更多的情况下，我们是使用我们的无线网卡对外网进行通信（笔者因为是校园网环境，图方便测试是连接了笔者的手机热点）。所以下面，**我们就是编译wireless tools的基础组件工具集合，我们最终的目的，是确认我们的网卡可以正常的扫描到我们的目标WIFI**（哦对了，提示一下，建议不要开Windows的移动热点，配置很麻烦，而且失败率非常高，即便我的手机都可以连上Windows的热点，iwlist仍然扫描不出来我的Windows热点，手机的一开就能扫出来）。

​	wireless tools的github地址：[wireless-tools/wireless_tools at master · HewlettPackard/wireless-tools](https://github.com/HewlettPackard/wireless-tools/tree/master/wireless_tools)

```
git clone https://github.com/HewlettPackard/wireless-tools/tree/master/wireless_tools
```

​	Wireless Tools因为挺老的，因此他是使用Makefile构建的。一般需要修改的地方就两个：

> PREFIX或者是其他表达INSTALL前缀的变量：这个一般指代的是下载的位置，不确定的朋友看一看Makefile里面写的下载到哪些地方了
>
> CROSS_COMPILE：用来指定交叉编译部署环境

```
  1 ##
  2 ## Please check the configurion parameters below
  3 ##
  4 
  5 ## Installation directory. By default, go in /usr/local.
  6 ## Distributions should probably use /, but they probably know better...
  7 ifndef PREFIX
  8   PREFIX = /home/charliechen/imx6ull/wireless_tools/wiretools_res
  9 endif
 10 
 11 CROSS_COMPILE := arm-linux-gnueabihf-
 12 
 13 ## Compiler to use (modify this for cross compile).
 14 CC = ${CROSS_COMPILE}gcc
 15 ## Other tools you need to modify for cross compile (static lib only).
 16 AR = ${CROSS_COMPILE}ar
 17 RANLIB = ${CROSS_COMPILE}ranlib
```

​	笔者这里决定偷懒了，正常你喜欢的话：

```
make PREFIX=/path/to/root/install/ CROSS_COMPILE=cross-compile-prefix
```

​	这里笔者直接改Makefile了，省事。编译的结果如下:

```
➜  tree .
.
├── include
│   ├── iwlib.h
│   └── wireless.h
├── lib
│   ├── libiw.so -> libiw.so.29
│   └── libiw.so.29
├── man
│   ├── man5
│   │   └── iftab.5
│   ├── man7
│   │   └── wireless.7
│   └── man8
│       ├── ifrename.8
│       ├── iwconfig.8
│       ├── iwevent.8
│       ├── iwgetid.8
│       ├── iwlist.8
│       ├── iwpriv.8
│       └── iwspy.8
└── sbin
    ├── ifrename
    ├── iwconfig
    ├── iwevent
    ├── iwgetid
    ├── iwlist
    ├── iwpriv
    └── iwspy

```

​	这个项目很小，很快就能编译结束。我们下一步需要做的，就是检验一下我们的编译成果，然后扔到板子上，看看能不能正确的扫描到我们的WIFI。

​	我们把lib和sbin依次拷贝到对应的根文件系统的位置上,比如说lib就放到我们的usr/lib下,sbin就放到我们的usr/sbin或者/sbin那里都行,反正需要保证的是你的/bin/sh可以一下子检索到iwlist和它的依赖libiw.so.

```
~ # iwlist
Usage: iwlist [interface] scanning [essid NNN] [last]
              [interface] frequency 
              [interface] channel 
              [interface] bitrate 
              [interface] rate 
              [interface] encryption 
              [interface] keys 
              [interface] power 
              [interface] txpower 
              [interface] retry 
              [interface] ap 
              [interface] accesspoints 
              [interface] peers 
              [interface] event 
              [interface] auth 
              [interface] wpakeys 
              [interface] genie 
              [interface] modulation 
```

​	iwlist需要我们指定网卡进行检索(注意,没有出来你自己的热点不要着急,iwlist只是测试我们的网卡有没有能力扫描我们的无线WIFI).

```
➜  iwlist wlp2s0 scan
wlp2s0    Scan completed :
          Cell 01 - Address: 0E:74:9C:4C:A7:03
                    Channel:153
                    Frequency:5.765 GHz (Channel 153)
                    Quality=59/70  Signal level=-51 dBm  
                    Encryption key:off
                    ESSID:"JLU.PC"
				  // 其他信息略去
```

​	非常好,这里是笔者的PC校园网的无线网络,看起来我们移植成功了,网卡也可以正常的被用来扫描.

## 移植我们的WPA_SUPPLICANT

​	但是真正想要连接进入我们的WIFI,这样做是远远不够的,我们还需要一个更加重量级的工具,叫做WPA_SUPPLICANT,WPA_SUPPLICANT需要的一个基础的中间件是openssl,需要注意的是openssl要是选择新版本的话,其他的以此作为基础构建的所有组件都要选择新的,因为OpenSSL的一些符号在我移植的版本中发现了非常大的变化.以及如果你想要编译一些项目的更加重量的版本,openssl尽可能编译全(笔者不推介,第一件事情是板子很可能带不动,第二件事情是非常的麻烦,到时候处理的依赖太多了反而造成环境很不稳定,在嵌入式平台,小即好).

### 移植两个重要的更基本组件之OpenSSL

​	OpenSSL 是一个功能强大、用途广泛的开源加密工具包和库，它主要用于实现 SSL（Secure Sockets Layer）和 TLS（Transport Layer Security）协议，同时也提供了大量通用的加密算法函数，常用于加密通信、证书管理和密钥生成等任务。说真的,笔者在这几年的学习和开发中,经常可以看到它的身影,所以,我们的确需要慎重选择我们的OpenSSL版本,由于笔者下定了决心使用所有构建最新的编译,因此,笔者直接移植了最新的openSSL

​	OpenSSL可以到官网下载源码包:

```
https://openssl-library.org/source/
```

​	正好,笔者下载的时候刚好发布了最新的LTS(嘿!20254月8号的).笔者优先推介下载LTS的组件,这意味着长时间的维护,之后使用出问题了真不知道咋办了杀去问维护的社区,人家也会理你.所以事情变得简答:

```
wget https://github.com/openssl/openssl/releases/download/openssl-3.5.0/openssl-3.5.0.tar.gz
tar -xf openssl-3.5.0.tar.gz
cd openssl-3.5.0
```

​	使用这个命令进行编译:

```
./Configure linux-armv4 shared no-asm --prefix=/home/charliechen/imx6ull/openssl_res CROSS_COMPILE=arm-linux-gnueabihf- 
```

​	新版本的openssl中也没有linux-armv7这个选项,因为linux-armv4表达对所有的arm平台兼容的意思,具体的差异实际上是编译器的差异(嗯,奇怪的名称),**以及你需要注意Configure的C是大写的**

​	之后就是make和make install两步走,你的install路径记得修改成你指定的,然后这个目录建议收藏,之后我们编译非常多的组件还会见到它!

​	编译install之后呢,我们需要做的就是把libcrypto.so\*和libssl.so*这些文件拷贝到我们的lib下

### 移植两个重要的更基本组件之libnl

​	`libnl`（Netlink Library）是 Linux 系统下一个用于操作 **netlink 套接字** 的 C 语言用户态库。它封装了原生 netlink 通信接口，使得开发者可以更方便地通过 netlink 访问内核的网络子系统，进行网络配置和状态获取，比如网络接口管理、路由配置、邻居表项处理、网络命名空间管理、无线设备控制等。它是现代 Linux 网络栈（尤其是 `iproute2`、`iw`、`NetworkManager`、`systemd-networkd` 等工具）的底层依赖库之一。

​	所以让我们开干:

```
git clone https://github.com/thom311/libnl
```

​	我们的configure文件需要走一次autoconf来自动配好一部分的编译信息:

```
autoreconf -fi
```

​	然后就是我们最喜欢的编译时间

```
./configure --host=arm-linux-gnueabihf --prefix=/home/charliechen/imx6ull/libnl_res
```

​	然后就是梭哈make与make install,拷贝所有库到根文件系统

### 移植wpa_supplicant

​		嵌入式wpa_supplicant的移植有点麻烦,我们需要禁用两个组件,一个是联合DBus,另一个是MACSEC.这些配置不在我们的Makefile里搞,而是Makefile读取我们的.config来做的

```
cd wpa_supplicant-2.11/wpa_supplicant
cp defconfig .config
vim .config
```

​	第一件事情是配齐我们的编译依赖:

```
	# 这个填上自己使用的GCC
 12 CC = arm-linux-gnueabihf-gcc
 13 # Uncomment following two lines and fix the paths if you have installed OpenSSL
 14 # or GnuTLS in non-default location
 	# 这个部分是让你解除注释填上OpenSSL的依赖
 15 CFLAGS += -I/home/charliechen/imx6ull/wireless_tools/openssl_res/include
 16 LIBS += -L/home/charliechen/imx6ull/wireless_tools/openssl_res/lib -lssl -lcrypto
 
 38 # driver_nl80211.c requires libnl. If you are compiling it yourself
 39 # you may need to point hostapd to your version of libnl.
 40 # 这个是补齐我们libnl的信息
 41 CFLAGS += -I/home/charliechen/imx6ull/wireless_tools/libnl_res/include/libnl3
 42 LIBS += -L/home/charliechen/imx6ull/wireless_tools/libnl_res/lib
```

​	但是需要注意的是,除此之外,我们还是需要暴露libnl的pkgconfig路径(嗯,神奇,但是就是要这样做)

```
export PKG_CONFIG_PATH=/pth/tp/your/libnl_install/lib/pkgconfig:$PKG_CONFIG_PATH //指定 libnl 库 pkgconfig 包位置 
```

​	需要注意的是,比正点多两个部分的是我们需要禁用MACSEC和DBUS

> CONFIG_DRIVER_MACSEC_QCA,CONFIG_DRIVER_MACSEC_LINUX和CONFIG_MACSEC**要注释掉,注意不是写n**,因为他是直接判断有没有赋值来决定是否参与编译的(憋笑)

```
 77 # Driver interface for MACsec capable Qualcomm Atheros drivers
 78 #CONFIG_DRIVER_MACSEC_QCA=y
 79 
 80 # Driver interface for Linux MACsec drivers
 81 # CONFIG_DRIVER_MACSEC_LINUX=y
 ...
 189 # MACsec
 190 # CONFIG_MACSEC=y
```

> CONFIG_CTRL_IFACE_DBUS_NEW和CONFIG_CTRL_IFACE_DBUS_INTRO要被禁用

```
377 # Add support for new DBus control interface
378 # (fi.w1.wpa_supplicant1)
379 # CONFIG_CTRL_IFACE_DBUS_NEW=y
380 
381 # Add introspection support for new DBus control interface
382 # CONFIG_CTRL_IFACE_DBUS_INTRO=y

```

​	现在我们直接编译就好了

```
make -j($nproc)
```

​	编译结束之后,把wpa_cli和wpa_supplicant拷贝到开发板上,这个事情就办完了.

## 测试可否连接上我们的WIFI

​	现在我们重新试一下,这个时候我们拉起来我们的WIFI,**注意,这一次我们先插入USB网卡后再加载内核,然后开启网卡**,

```
~ # ifconfig
eth0      Link encap:Ethernet  HWaddr B8:AE:1D:01:00:01  
          inet addr:10.41.0.2  Bcast:10.41.0.255  Mask:255.255.255.0
          inet6 addr: fe80::baae:1dff:fe01:1/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:10320 errors:0 dropped:0 overruns:0 frame:0
          TX packets:5103 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:12970782 (12.3 MiB)  TX bytes:851378 (831.4 KiB)

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)

wlan0     Link encap:Ethernet  HWaddr 00:0F:00:C0:01:56  
          inet6 addr: fe80::20f:ff:fec0:156/64 Scope:Link
          UP BROADCAST MULTICAST  MTU:2312  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:0 errors:0 dropped:18 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
```

​	现在我们测试一下扫描:

```
~ # iwlist wlan0 scan | grep Charlie
                    ESSID:"CharliesWLAN"
```

​	笔者的WIFI热点名称的确是CharliesWLAN，下一步，我们就来配置我们的WIFI了.

​	我们在我们的etc目录下创建一个wpa_supplicant.conf 

```
~ # cat /etc/wpa_supplicant.conf 
ctrl_interface=/var/run/wpa_supplicant 

ap_scan=1

network={
ssid="this places the ssid of your wifi"
psk="the password is never correct,thus replace with your passwd!"
}
```

​	注意,这里的对齐和检查非常的严格,这里是不允许有tab键和空格造成不对齐的,严格的按照笔者的格式.此外看检查/var/run/wpa_supplicant,不存在自己搓一个:`mkdir -p /var/run/wpa_supplicant `

​	现在我们就试试看能不能拉起来WIFI.

```
wpa_supplicant -D wext -c /etc/wpa_supplicant.conf -i wlan0 -B
```

​	需要注意的是，人家wpa_supplicant本身就是提供幕后守护进程的写法的，别使用＆！

​	出现日志:

```
Successfully initialized wpa_supplicant
rfkill: Cannot open RFKILL contro[   22.164063] warning: `wpa_supplicant' uses wireless extensions which will stop working for Wi-Fi 7 hardware; use nl80211
l device
ioctl[SIOCSIWENCODEEXT]: Invalid argument
ioctl[SIOCSIWENCODEEXT]: Invalid argument
```

​	这个都没啥,不干扰我们使用网卡连接WIFI．到这里，我们就可以开始使用udhcpc来获取我们的WIFI网卡的IP了!

## 临门一脚:使用udhcpc来完成我们的通外网ping通的任务

​	如果你很幸运,一下子就能获得IP,那这个指令一下去,本章就结束了

```
udhcpc -i wlan0
```

​	然后你试试看看WLAN0接口有没有获得期望的IP.

```
wlan0     Link encap:Ethernet  HWaddr 00:0F:00:C0:01:56  
          inet addr:192.168.95.38  Bcast:192.168.95.255  Mask:255.255.255.0
          inet6 addr: fe80::20f:ff:fec0:156/64 Scope:Link
          inet6 addr: 2408:8435:600:8e86:20f:ff:fec0:156/64 Scope:Global
          UP BROADCAST RUNNING MULTICAST  MTU:2312  Metric:1
          RX packets:24 errors:0 dropped:0 overruns:0 frame:0
          TX packets:11 errors:0 dropped:6 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:2006 (1.9 KiB)  TX bytes:1790 (1.7 KiB)
```

​	各位,这个就是一个成功的输出,如果你没看到inet addr出现IPv4的地址,很不幸,那就是自动DHCP罢工了,我们需要自己编写DHCP脚本来完成我们对IP网卡的赋值.这个问题的解决办法就是,udhcpc可以正常的获取我们从热点申请来的动态IP,但是却没有赋值给我们的网卡.好在这个事情好办.

​	我们自己解析就好了!我们编写一个simple_dhcp.sh脚本放置到etc下

```
~ # cat /etc/simple_dhcp.sh
#!/bin/sh
[ -n "$ip" ] && ifconfig "$interface" "$ip" netmask "$subnet"
[ -n "$router" ] && route add default gw "$router"
[ -n "$dns" ] && echo "nameserver $dns" > /etc/resolv.conf
```

​	然后:

```
udhcpc -i wlan0 -s /etc/simple_dhcp.sh
```

​	哒哒!成功了!

```
wlan0     Link encap:Ethernet  HWaddr 00:0F:00:C0:01:56  
          inet addr:192.168.95.38  Bcast:192.168.95.255  Mask:255.255.255.0
          inet6 addr: fe80::20f:ff:fec0:156/64 Scope:Link
          inet6 addr: 2408:8435:600:8e86:20f:ff:fec0:156/64 Scope:Global
          UP BROADCAST RUNNING MULTICAST  MTU:2312  Metric:1
          RX packets:24 errors:0 dropped:0 overruns:0 frame:0
          TX packets:11 errors:0 dropped:6 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:2006 (1.9 KiB)  TX bytes:1790 (1.7 KiB)
```

```
~ # ping baidu.com
PING baidu.com (39.156.66.10): 56 data bytes
64 bytes from 39.156.66.10: seq=0 ttl=47 time=57.000 ms
64 bytes from 39.156.66.10: seq=1 ttl=47 time=75.479 ms
64 bytes from 39.156.66.10: seq=2 ttl=47 time=65.018 ms
64 bytes from 39.156.66.10: seq=3 ttl=47 time=84.427 ms
64 bytes from 39.156.66.10: seq=4 ttl=47 time=88.467 ms
^C
--- baidu.com ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss
round-trip min/avg/max = 57.000/74.078/88.467 ms
```

​	现在,你就可以开始做网络应用程序了!

## 附录

​	有朋友可能需要一个开机自动判断是否有网卡,有则扫描WIFI且尝试连接,没有目标WIFI就打日志的脚本,笔者这里提供一份笔者自己写的

```
# load the wifi issue
echo "Bringing up wlan0 interface..."
ifconfig wlan0 up

echo "Starting wpa_supplicant for Wi-Fi connection..."
wpa_supplicant -D wext -c /etc/wpa_supplicant.conf -i wlan0 -B

echo "Waiting for Wi-Fi connection..."
tries=0
while [ $tries -lt 10 ]; do
    if iwconfig wlan0 | grep -q "Access Point: Not-Associated"; then
        echo "Not connected to AP, retrying... ($tries)"
    else
        echo "Connected to Wi-Fi, proceeding to obtain IP."
        break
    fi
    tries=$((tries + 1))
    sleep 1
done

if [ $tries -eq 10 ]; then
    echo "Warning: Failed to connect to Wi-Fi. Skipping DHCP."
else
    echo "Requesting IP via DHCP..."
    udhcpc -i wlan0 -s /etc/simple_dhcp.sh
fi
```

​	当然,如果是事后需要连接,我也写了一个

```
#!/bin/sh

echo "Bringing up wlan0 interface..."
ifconfig wlan0 up

echo "Starting wpa_supplicant..."

echo "Checking for existing wpa_supplicant process..."
killall wpa_supplicant 2>/dev/null

if [ -e /var/run/wpa_supplicant/wlan0 ]; then
    echo "Removing stale wpa_supplicant control interface..."
    rm -f /var/run/wpa_supplicant/wlan0
fi
wpa_supplicant -D wext -c /etc/wpa_supplicant.conf -i wlan0 -B
echo "Waiting for Wi-Fi connection..."
tries=0
while [ $tries -lt 10 ]; do
    if iwconfig wlan0 | grep -q "Access Point: Not-Associated"; then
        echo "Not connected to AP, retrying... ($tries)"
    else
        echo "Connected to Wi-Fi, proceeding to obtain IP."
        break
    fi
    tries=$((tries + 1))
    sleep 1
done

if [ $tries -eq 10 ]; then
    echo "Warning: Failed to connect to Wi-Fi."
else
    echo "Requesting IP via DHCP..."
    udhcpc -i wlan0 -s /etc/simple_dhcp.sh
fi
```

