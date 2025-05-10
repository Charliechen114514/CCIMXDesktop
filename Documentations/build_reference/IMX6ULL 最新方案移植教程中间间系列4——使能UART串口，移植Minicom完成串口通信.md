# IMX6ULL 最新方案移植教程中间间系列4——使能UART串口，移植Minicom完成串口通信 + WM8960音频驱动实验

## 前言

​	为什么放在一起呢？因为这里需要注意的是，新版本内核没办法使用正点原子提供的方案，这是因为新版本内核我们需要自己移植一些固件辅助我们的显示，否则的话就会出现问题（比如说Minicom串口罢工和WM8960加载失败等等，笔者后面查明是因为缺少了nxp的linux-firmware导致的），这里笔者就开始进行简单的说明，如何在Linux6.12.3上进行移植。

## Part 1: 使能UART串口，移植Minicom

​	我们的正点原子开发板上有一个RS232，对，就那个长得有点像HDMI接口（我室友吐槽的）的哪个，板子的左上角。我们的设备树默认是失能了这个串口，现在我们需要做的就是给这个串口拉起来。

​	我们需要做的是先在设备树文件中添加一个节点（注意，直接孤零的一个节点）

```
&uart3 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_uart3>;
	status = "okay";
};
```

​	在pinctrl_uart3中，我们设置一下使用的GPIO复用

```
	/* UART3 pins constrol*/
	pinctrl_uart3: uart3grp { 
		fsl,pins = <
			MX6UL_PAD_UART3_TX_DATA__UART3_DCE_TX       0X1b0b1
			MX6UL_PAD_UART3_RX_DATA__UART3_DCE_RX       0X1b0b1
		>;
	};
```

​	然后完事了之后编译设备树传递到板子上后，看看/dev下有没有多出来/dev/ttymxc2，多出来了就是成功了

```
~ # ls /dev/tty*
/dev/tty      /dev/tty20    /dev/tty33    /dev/tty46    /dev/tty59
/dev/tty0     /dev/tty21    /dev/tty34    /dev/tty47    /dev/tty6
/dev/tty1     /dev/tty22    /dev/tty35    /dev/tty48    /dev/tty60
/dev/tty10    /dev/tty23    /dev/tty36    /dev/tty49    /dev/tty61
/dev/tty11    /dev/tty24    /dev/tty37    /dev/tty5     /dev/tty62
/dev/tty12    /dev/tty25    /dev/tty38    /dev/tty50    /dev/tty63
/dev/tty13    /dev/tty26    /dev/tty39    /dev/tty51    /dev/tty7
/dev/tty14    /dev/tty27    /dev/tty4     /dev/tty52    /dev/tty8
/dev/tty15    /dev/tty28    /dev/tty40    /dev/tty53    /dev/tty9
/dev/tty16    /dev/tty29    /dev/tty41    /dev/tty54    /dev/ttymxc0
/dev/tty17    /dev/tty3     /dev/tty42    /dev/tty55    /dev/ttymxc2
/dev/tty18    /dev/tty30    /dev/tty43    /dev/tty56
/dev/tty19    /dev/tty31    /dev/tty44    /dev/tty57
/dev/tty2     /dev/tty32    /dev/tty45    /dev/tty58
~ # 
```

​	完事之后，我们还需要做的事情是移植minicom和添加linux-firmware固件。

### 编译ncurses作为minicom的显示中间件

​	笔者选择的是ncurse6.5这个最新的版本。[Index of /pub/gnu/ncurses](https://ftp.gnu.org/pub/gnu/ncurses/)，如果你想使用其他的版本，随意。

```
wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.5.tar.gz
```

​	然后解压缩后就是一个配置：

```
./configure --prefix=/home/charliechen/imx6ull/ncurses_res --host=arm-linux-gnueabihf --target=arm-linux-gnueabihf --with-shared --without-profile --disable-stripping --without-progs --with-manpages --without-tests
```

​	然后就是make，make和make install结束后，你需要看一眼，得到的结果是啥：

```
➜  ls
libformw.a       libmenuw_g.a     libncurses++w_g.a   libpanelw_g.a
libformw_g.a     libmenuw.so      libncursesw_g.a     libpanelw.so
libformw.so      libmenuw.so.6    libncursesw.so      libpanelw.so.6
libformw.so.6    libmenuw.so.6.5  libncursesw.so.6    libpanelw.so.6.5
libformw.so.6.5  libncurses++w.a  libncursesw.so.6.5  terminfo
libmenuw.a       libncursesw.a    libpanelw.a
```

​	之后我们编译minicom的时候，也就需要连接的是ncursesw库，而不是正点的ncurses。同样的，我们把所有的编译结果都上传到开发板上。

### 移植minicom

​	minicom的github地址：[Distrotech/minicom](https://github.com/Distrotech/minicom)

```
./configure CC=arm-linux-gnueabihf-gcc --prefix=/home/charliechen/imx6ull/minicom_res --host=arm-linux-gnueabihf CPPFLAGS=-I/home/charliechen/imx6ull/ncurses_res/include LDFLAGS=L/home/charliechen/imx6ull/ncurses_res/lib -enable-cfg-dir=/etc/minicom 
```

​	但是笔者编译的时候就出现了这些问题：

```
/usr/lib/gcc-cross/arm-linux-gnueabihf/13/../../../../arm-linux-gnueabihf/bin/ld: vt100.o:/media/charliechen/KESU/reserverd_old_code/minicom/minicom/src/vt100.c:94: multiple definition of vt_outmap'; minicom.o:/media/charliechen/KESU/reserverd_old_code/minicom/minicom/src/minicom.h:144: first defined here
...
/usr/lib/gcc-cross/arm-linux-gnueabihf/13/../../../../arm-linux-gnueabihf/bin/ld: sysdep1_s.o:/media/charliechen/KESU/reserverd_old_code/minicom/minicom/src/sysdep1_s.c:31: multiple definition of portfd_is_socket'; minicom.o:/media/charliechen/KESU/reserverd_old_code/minicom/minicom/src/minicom.h:116: first defined here
```

​	后来查明发现，是因为这些涉及到的变量的EXTERN是空的，自己手改一下，改成extern就好了，之后我们把编译的bin下的所有文件拷贝到开发板上。

​	同时不要忘记在/etc/profile中塞上这两行。

```
export TERM=vt100 
export TERMINFO=/usr/share/terminfo
```



### 移植固件

​	按照正点原子的配置打开串口会炸这个：

```
[  135.759971] imx-uart 21ec000.serial: We cannot prepare for the TX slave dma!!
[  135.767429] imx-uart 21ec000.serial: We cannot prepare for the TX slave dma!
[  136.366890] imx-uart 21ec000.serial: We cannot prepare for the TX slave dma!
[  136.896694] imx-uart 21ec000.serial: We cannot prepare for the TX slave dma!
```

```
https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git
```

​	上面就是firmware的地址，找到里面的sdma-imx6q.bin后，烧录到内核中：

```
CONFIG_EXTRA_FIRMWARE="imx/sdma/sdma-imx6q.bin"
CONFIG_EXTRA_FIRMWARE_DIR="firmware"
```

​	具体的设置自行博客，笔者推介使用menuconfig设置。之后我们就可以准备好使用minicom了，minicom的使用请参考正点的或者是minicom的教程，这里不打算重复造轮子了。

## WM8960音频驱动

​	我们现在就直接来移植WM8960的驱动，因为WM8960跟LCD会打架，以及还有一些电源需要配置（想自己尝试的朋友可以自己先CV正点原子的配置后看日志结合自己的需求进行调整），因此我们这里也就不浪费大家时间说明为什么非得要这样写，这属于设备树和驱动的交互，你可以抄其他人的，这件事情都是一样的。

### 修订一下默认的内核寄存器配置

​	找到wm8960.c文件，需要修改一下

```
/*{ 0x17, 0x01c0 },*/ 
{ 0x17, 0x01c4 },
```

​	因为正点原子的板子是声卡只有一个左声道，这里不这样配置录不出来声音（笔者测试过），具体的原因正点原子的参考手册里有。

### 配置一下wm8960的根设备信息

​	我们的wm8960也是一个经典的IIC设备，这里，我们按照板子的外设分布，接到了I2C1上进行驱动，如下所示

```
	codec: wm8960@1a {
		#sound-dai-cells = <0>;
		compatible = "wlf,wm8960";
		reg = <0x1a>;
		wlf,shared-lrclk;
		wlf,hp-cfg = <3 2 3>;
		wlf,gpio-cfg = <1 3>;
		clocks = <&clks IMX6UL_CLK_SAI2>;
		clock-names = "mclk";
		AVDD-supply = <&reg_audio_avdd>;
		DBVDD-supply = <&reg_audio_dbvdd>;
		DCVDD-supply = <&reg_audio_dcvdd>;
		SPKVDD1-supply = <&reg_audio_spkvdd1>;
		SPKVDD2-supply = <&reg_audio_spkvdd2>;
	};
```

​	其中这里就设计到了一些电源的信息，笔者补充一下：

```
	reg_audio_avdd: regulator-avdd {
    	compatible = "regulator-fixed";
    	regulator-name = "audio-avdd";
    	regulator-min-microvolt = <3300000>;
    	regulator-max-microvolt = <3300000>;
    	regulator-always-on;
	};

	reg_audio_dbvdd: regulator-dbvdd {
    	compatible = "regulator-fixed";
    	regulator-name = "audio-dbvdd";
    	regulator-min-microvolt = <1800000>;
    	regulator-max-microvolt = <1800000>;
    	regulator-always-on;
	};

	reg_audio_dcvdd: regulator-dcvdd {
    	compatible = "regulator-fixed";
    	regulator-name = "audio-dcvdd";
    	regulator-min-microvolt = <1800000>;
    	regulator-max-microvolt = <1800000>;
    	regulator-always-on;
	};

	reg_audio_spkvdd1: regulator-spkvdd1 {
    	compatible = "regulator-fixed";
    	regulator-name = "audio-spkvdd1";
    	regulator-min-microvolt = <5000000>;
    	regulator-max-microvolt = <5000000>;
    	regulator-always-on;
	};

	reg_audio_spkvdd2: regulator-spkvdd2 {
    	compatible = "regulator-fixed";
    	regulator-name = "audio-spkvdd2";
    	regulator-min-microvolt = <5000000>;
    	regulator-max-microvolt = <5000000>;
    	regulator-always-on;
	};
```

​	这些就描述了我们的驱动如何控制供电的事情，这样内核就不会爆警告了。

​	下面的部分，则是描述了WM8960的音频信息：

```
	sound-wm8960 {
		compatible = "fsl,imx-audio-wm8960";
		model = "wm8960-audio";
		audio-cpu = <&sai2>;
		audio-codec = <&codec>;
		pinctrl-names = "default";
		pinctrl-0 = <&pinctrl_audio>;
		audio-asrc = <&asrc>;
		hp-det-gpio = <&gpio5 4 0>;
		audio-routing =
			"Headphone Jack", "HP_L",
			"Headphone Jack", "HP_R",
			"Ext Spk", "SPK_LP",
			"Ext Spk", "SPK_LN",
			"Ext Spk", "SPK_RP",
			"Ext Spk", "SPK_RN",
			"LINPUT2", "Mic Jack",
			"LINPUT3", "Mic Jack",
			"RINPUT1", "AMIC",
			"RINPUT2", "AMIC",
			"Mic Jack", "MICB",
			"AMIC", "MICB";
	};
```

​	设备树的修改就到这里。想要确认的话，你可以看看/dev/snd

```
~ # ls /dev/snd
comprC0D0  controlC1  pcmC1D0p   pcmC1D1p
controlC0  pcmC1D0c   pcmC1D1c   timer
```

​	和内核的日志信息：

```
~ # dmesg | grep wm8960
[    3.757513] fsl-asoc-card sound-wm8960: ASoC: source widget CPU-Playback overwritten
[    3.765512] fsl-asoc-card sound-wm8960: ASoC: sink widget CPU-Capture overwritten
[    3.773161] fsl-asoc-card sound-wm8960: ASoC: sink widget CPU-Playback overwritten
[    3.780760] fsl-asoc-card sound-wm8960: ASoC: source widget CPU-Capture overwritten
[    7.231462]   #1: wm8960-audio
~ # 
```



### 移植一下 alsa-lib 和 alsa-utils

​	alsa-lib 编译过程中会生成一些配置文件，而这些配置信息的路径都是绝对路径，因此为了保证 ubuntu 和开发板根文件系统中的路径一致！我们需要在 ubuntu 和开发板中各创建一 个路径和名字完全一样的目录，这里我们都创建一个/usr/share/arm-alsa 目录。这样的话就可以无缝的迁移了。

```
https://github.com/alsa-project/alsa-lib.git
```

​	下载之后按照经典的配置给prefix和交叉编译信息之后，还需要给出：

```
./configure --host=arm-linux-gnueabihf --prefix=/home/charliechen/imx6ull/alsa-lib_res --with-configdir=/usr/share/arm-alsa 
```

​	对的，必须要这样写。

​	需要注意的是，make install的时候因为一定要mirror到我们的/usr目录下，因此需要一个sudo。

​	最后就是拷贝一下库lib/和/usr/share/arm-alsa下的东西放到开发板的/usr/lib和/usr/share/arm-alsa

## alsa utils

​	笔者这里根正点原子一样翻车了，没有配好，这里是--disable-alsamixer了，不然死活搞不了

```
wget https://www.alsa-project.org/files/pub/utils/alsa-utils-1.2.9.tar.bz2
```

```
./configure --host=arm-linux-gnueabihf --prefix=/home/charliechen/imx6ull/alsautils_res --with-alsa-inc-prefix=/home/charliechen/imx6ull/alsalib_res/include/ --with-alsa-prefix=/home/charliechen/imx6ull/alsalib_res/lib/ --disable-xmlto --disable-alsamixer
```

​	然后就是make 和 make install一条龙。拷贝bin sbin和share到对应的文件夹位置上。

​	我们还需要补充一下：ALSA_CONFIG_PATH在etc/profile中

```
export ALSA_CONFIG_PATH=/usr/share/arm-alsa/alsa.conf 
```

​	然后，我们使用一下设置（注意你不想折磨自己就直接搬运笔者的配置），否则就自己调试

### 笔者播放声音的配置

```
amixer -c 1 sset 'Speaker' 100
amixer -c 1 sset 'Headphone' 100
amixer -c 1 sset 'Right Output Mixer PCM' on
amixer -c 1 sset 'Left Output Mixer PCM' on
```

### 笔者录音的配置

```
# Set capture volume
amixer cset name='Capture Volume' 90,90

# PCM configuration
amixer sset 'PCM Playback -6dB' on
amixer sset 'Playback' 256
amixer sset 'Right Output Mixer PCM' on
amixer sset 'Left Output Mixer PCM' on

# ADC PCM input gain
amixer sset 'ADC PCM' 230

# Headphone/Speaker volume setup (DC/AC paths)
# Enable headphone output
amixer sset 'Headphone Playback ZC' on
# Set headphone volume (98%, MaxVolume is 127)
amixer sset Headphone 125,125
# Enable speaker output
amixer sset 'Speaker Playback ZC' on
# Set speaker volume (98%, MaxVolume is 127)
amixer sset Speaker 125,125
# Set speaker AC path volume (80%, MaxVolume is 5)
amixer sset 'Speaker AC' 4
# Set speaker DC path volume (80%, MaxVolume is 5)
amixer sset 'Speaker DC' 4

# Left audio input management
amixer cset name='Left Input Mixer Boost Switch' on
# Disable Left Input Mixer Boost
amixer sset 'Left Input Mixer Boost' on
amixer sset 'Left Boost Mixer LINPUT1' on
amixer sset 'Left Input Boost Mixer LINPUT1' 0M6
amixer sset 'Left Boost Mixer LINPUT2' on
amixer sset 'Left Input Boost Mixer LINPUT2' 0
# Disable LINPUT3
amixer sset 'Left Boost Mixer LINPUT3' on
amixer sset 'Left Input Boost Mixer LINPUT3' 0

# Right audio input management
# Enable Right Input Mixer Boost
amixer sset 'Right Input Mixer Boost' on
amixer sset 'Right Boost Mixer RINPUT1' off
amixer sset 'Right Input Boost Mixer RINPUT2' 0
amixer sset 'Right Boost Mixer RINPUT2' on
amixer sset 'Right Input Boost Mixer RINPUT2' 127
amixer sset 'Right Boost Mixer RINPUT3' off
amixer sset 'Right Input Boost Mixer RINPUT3' 0

amixer -c 1 cset numid=46 on
amixer -c 1 cset numid=44 on
amixer -c 1 cset numid=45 on
amixer -c 1 cset numid=9 3
amixer -c 1 sset 'Left Input Boost Mixer LINPUT2' 7
amixer -c 1 sset 'Left Input Boost Mixer LINPUT3' 7
```

​	以及需要注意的是，我们还需要比正点原子多一步，就是设置默认的声卡

```
pcm.!default {
    type hw
    card 1
}

ctl.!default {
    type hw
    card 1
}
```

​	这样的话我们就可以直接使用简单的aplay和arecord直接播放和录制声音了。下面就是随意的找一个wav音频开始测试，然后自己随意的录一段音在播放看看效果了。

