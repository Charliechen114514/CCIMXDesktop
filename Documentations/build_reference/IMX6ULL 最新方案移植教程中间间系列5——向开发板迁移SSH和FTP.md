# IMX6ULL 最新方案移植教程中间间系列5——向开发板迁移SSH和FTP

## 前言

​	本篇教程是基于正点原子教程的进一步改进和补充。这个是笔者这段时间的第五部分工作，也就是向开发板上迁移我们的SSH和FTP，这样，我们就可以直接向板子传递文件 了，可能在NFS挂载的时候意义不大，因为我们对根文件系统的操作直接被同步了，但是如果我们的目标系统被烧写近了EMMC中，那么这就很有意义了，直接天天拿着U盘挂载卸载太麻烦了，不如直接FTP刷过去文件。

​	需要注意的是，下面两个软件要求你的登录主机和板子在同一个局域网，即——ping通才可以，否则的话是用不了的，意味着你的前置要求是能够联网。所以做不到的朋友先把网卡驱动啥的移植明白在看这个。

## 补充和备齐基本组件——libcrypt

​	我们的FTP和SSH现在需要依赖libcrypt来做加密，注意，这些项目的符号依赖不是OpenSSL的那个libcrypto，这是两个完全不一样的东西，老环境中，我们自带了libcrypt.so，因此正点原子的教程没有设计到这个问题，但是新版本的编译器则不带这些库了，所以，需要我们自己编译和补充库

```
https://github.com/besser82/libxcrypt
```

​	笔者选择的是最新的Release，也就是4.4.38，我们下载后：

```
./configure \
  --host=arm-linux-gnueabihf \
  --prefix=/home/charliechen/imx6ull/netusr-tools/crypt_res \
  --disable-static \
  --enable-shared
```

​	编译完成之后，我们记得我们的下载的位置，就可以安装FTP了

## 交叉编译我们的FTP

​	笔者选择的是vsftpd，官方地址在：[vsftpd - Secure, fast FTP server for UNIX-like systems](https://security.appspot.com/vsftpd.html#download)

```
wget https://security.appspot.com/downloads/vsftpd-3.0.5.tar.gz
```

​	现在我们需要做的就是进入编译。但是现在因为crypt库不在默认位置，我们需要修改一下Makefile。

```
LINK    =       -L/home/charliechen/imx6ull/netusr-tools/crypt_res/lib -Wl,-s
```

​	我们在LINK中追加一下搜索路径即可，然后我们不下载，直接拷贝就行（因为他是路径写死的。。。）

```
make CC=arm-linux-gnueabihf-gcc
```

​	一下就能完事。然后就是拷贝我们的vsftpd和vsftpd.conf分别到usr/sbin/和etc/目录下，**进入开发板，而且需要修改权限为**

```
chmod +x /usr/sbin/vsftpd 
chown root:root /etc/vsftpd.conf 
```

​	下面修改/etc/vsftpd.conf

```
# Uncomment this to allow local users to log in.
local_enable=YES
#
# Uncomment this to enable any form of FTP write command.
write_enable=YES
```

​	local_enable和write_enable需要解除注释。此外还需要创建路径

```
mkdir /home 
mkdir /usr/share/empty -p 
mkdir /var/log -p 
touch /var/log/vsftpd.log 
```

​	我们还需要做的是写/etc/passwd

```
root:x:0:0:root:/root:/bin/sh
```

​	和/etc/group

```
root:x:0:
```

​	然后我们就需要创建几个重要的用户：

```
adduser nobody
# 会让你设置密码，随意，最好自己熟悉的，怕万一之后调试要用到
adduser ftp
# 会让你设置密码，随意，最好自己熟悉的，怕万一之后调试要用到
adduser 自己喜欢的名称
# 会让你设置密码，随意，最好自己熟悉的，因为之后我们要自己登录使用
```

```
vsftpd &
```

​	上面的指令就是启动vsftpd，现在我们就可以使用FTP登录我们的板子了，需要注意的是，协议只能是FTP而不是SFTP，否则的话登不上去的！

## OpenSSH的移植

​	我们下面移植OpenSSH，这样的话，我们就可以直接使用VSCode等软件直接交互我们的板子，

### 基础1：移植zlib

​	zlib很好移植

```
git clone https://github.com/madler/zlib
```

​	之后，我们设置

```
export CC=arm-linux-gnueabihf-gcc 
export LD=arm-linux-gnueabihf-ld 
export AS=arm-linux-gnueabihf-as 
./configure -=-prefix=/home/charliechen/imx6ull/zlib_res 
make -j4
```

​	完事。然后就往开发板上迁移就好了

### 基础2：移植OpenSSL

​	这个事情在我之前的迁移博客中提到了，所以自行翻前面的无线网卡驱动移植那个部分。

### openssh的编译

​		这里笔者选择的是阿里源：

```
wget https://mirrors.aliyun.com/pub/OpenBSD/OpenSSH/portable/openssh-9.9p2.tar.gz
```

​	解压后进入配置：

```
./configure --host=arm-linux-gnueabihf --with-libs --with-zlib=/home/charliechen/imx6ull/zlib_res \
	--with-ssl-dir=/home/charliechen/imx6ull/openssl_res --disable-etc-default-login \
	CC=arm-linux-gnueabihf-gcc AR=arm-linux-gnueabihf-ar
```

​	这里的-with-zlib和--with-ssl-dir依次指向我们自己install的时候的目录。

### 创建开发板环境

​	创建这些目录

```
/usr/local/bin 
/usr/local/sbin 
/usr/local/libexec
/usr/local/etc 
/var/run 
/var/empty 
```

上述目录创建好以后将如下文件拷贝到开发板的/usr/local/bin 目录下： 

```
scp sftp ssh ssh-add ssh-agent ssh-keygen ssh-keyscan 
```

 将如下文件拷贝到开发板的/usr/local/sbin 目录下： 

```
 sshd 
```

将如下文件拷贝到开发板的/usr/local/etc 目录下： 

```
moduli ssh_config sshd_config 
```

 将如下文件拷贝到开发板的/usr/local/libexec 目录下： 

```
sftp-server ssh-keysign sshd-session
```

 创建软连接，进入开发板中的/bin 目录下，输入如下命令创建软连接： 

```
cd /bin/ 
ln -s /usr/local/bin/scp 
ln -s /usr/local/bin/sftp 
ln -s /usr/local/bin/ssh 
ln -s /usr/local/bin/ssh-add 
ln -s /usr/local/bin/ssh-agent 
ln -s /usr/local/bin/ssh-keygen 
ln -s /usr/local/bin/ssh-keyscan 
```

 再进入开发板的/sbin 目录下，输入如下命令创建软连接： 

```
cd /sbin/ 
ln -s /usr/local/sbin/sshd 
```

软连接创建完成以后就可以直接调用上面 ssh 相关命令了。

​	最后，我们编辑一下/usr/local/etc/sshd_config，把PermitRootLogin那一行的注释解开后，设置成yes

```
~ # cat /usr/local/etc/sshd_config  | grep PermitRootLogin
PermitRootLogin yes
```

​	之后添加一个ssh用户和在/usr/local/etc生成一些密匙辅助我们的通信安全后：

```
adduser sshd
cd /usr/local/etc
ssh-keygen -t rsa -f ssh_host_rsa_key -N "" 
ssh-keygen -t ecdsa -f ssh_host_ecdsa_key -N "" 
ssh-keygen -t ed25519 -f ssh_host_ed25519_key -N ""
```

​	我们的配置就结束了，开启SSH服务只需要/sbin/sshd & 即可，确定没有任何报错日志之后，记得top一下看看有没有守护进程做事情：

```
CPU:  0.4% usr  0.8% sys  0.0% nic 98.7% idle  0.0% io  0.0% irq  0.0% sirq
Load average: 0.00 0.00 0.00 2/66 202
  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND
  202   107 root     R     2740  0.5   0  0.6 top
  173     2 root     SW       0  0.0   0  0.4 [RTW_CMD_THREAD]
   30     2 root     IW       0  0.0   0  0.2 [kworker/0:3-eve]
  179     1 root     S     7344  1.4   0  0.0 wpa_supplicant -D wext -c /etc/wpa
  103     1 root     S     5112  1.0   0  0.0 sshd: /sbin/sshd [listener] 0 of 1
  191     1 root     S     2740  0.5   0  0.0 udhcpc -i wlan0 -s /etc/simple_dhc
   91     1 root     S     1840  0.3   0  0.0 vsftpd
```

​	可以看到我们部署的OK，其中103号进程就是我们的sshd，91号进程就是我们的vsftpd。之后就可以使用ssh和ftp了！enjoy!!!