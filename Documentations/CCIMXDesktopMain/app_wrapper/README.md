# App Wrapper

​	App Wrapper文件夹是CCIMX Desktop的核心，本质上是这个桌面可以启动新Application的重要保证。这里，AppWrapper实际上将应用封装成对进程的抽象，使用给定的地址派生新的应用进程。

​	目前为止，这里只有applicationwrapper和pagesetuper两个抽象，他们依次完成的是——物理派发新的应用程序运行（脱离桌面，解耦合防止用户的进程崩溃连带桌面一起崩溃）；建立标准的IOS的桌面的一个页。

​	具体的文档依次参考本文件夹下的接口文档即可