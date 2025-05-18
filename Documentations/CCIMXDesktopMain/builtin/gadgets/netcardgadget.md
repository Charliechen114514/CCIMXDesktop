# 模块名称：NetCardGadget

功能概述：NetCardGadget 类继承自 AppCardWidget，为网络状态监测卡片组件。该组件在预启动阶段和卡片渲染后分别执行相应的网络探测逻辑，通过 DesktopToast 提示用户当前的网络状态，并在界面上更新显示。

## 枚举说明

 NetCardGadget 定义了一个内部枚举 NetWorkState，用于表示网络连通状态。其值包括 UNKNOWN（未知状态），DISCONNECTED（未连接），LOCAL（本地网络可达）以及 ONLINE（互联网可访问）。

## 构造函数与拷贝限制

 显式构造函数 explicit NetCardGadget(DesktopToast* toast, QWidget* parent) 接收一个 DesktopToast 对象以用于状态提示和一个可选的父 QWidget 指针。类通过 Q_DISABLE_COPY 宏禁止拷贝构造和赋值操作，确保每个实例的状态管理不会因复制导致混乱。

## 公有方法

 invoke_preLaunch_work 方法在卡片显示前被调用，用于启动一次完整的网络状态探测流程。该方法会优先执行局域网连通性检查，再基于检查结果决定是否需要进行在线可达性测试，最终通过 DesktopToast 向用户弹出相应的文本提示，并更新缓存状态 cache_reachability。

## 受保护方法

 postAppCardWidget 方法在卡片渲染完成后被调用，用于启动周期性的状态刷新。默认实现会创建并启动一个 QTimer，定时触发 process_once_fresh 以实时更新网络状态并刷新界面显示。子类可重写该方法以定制卡片渲染后的行为。

## 私有成员

 cache_reachability 保存最近一次探测到的网络状态，初始值为 UNKNOWN。
 scan_timer 是一个 QTimer 对象指针，用于定期执行网络状态刷新任务。
 online_base_work 常量字符串指向默认在线检测地址 "[http://www.baidu.com"，用于在线可达性测试。](http://www.baidu.xn--com",-w41hj53atugiuwf73ascs1j0anx1blpl./)
 私有方法 process_once_fresh 用于在定时器触发时统一管理局域网和在线探测顺序。process_once_local_check 专职局域网连通性检测，若检测失败则更新状态并终止后续在线检测；process_once_online_check 则在局域网可达后尝试访问 online_base_work，以确认外网连通性。

## 使用示例

 在构造界面时，创建 NetCardGadget 实例并传入 DesktopToast 和父窗口指针，然后将该卡片添加到相应的布局中。应用启动后，框架会自动调用 invoke_preLaunch_work 进行初次探测，并在卡片渲染完成时启动定时器以实现实时监控。用户可通过订阅卡片自身信号或查询 cache_reachability 来获取最新网络状态。