# ApplicationWrapper

​	功能概述：ApplicationWrapper 类封装了外部应用程序的调度与运行流程。它基于 QObject，实现了对外部可执行文件启动前的检查、启动过程及运行结束后的状态回调。该类适用于在 Qt 应用中以编程方式管理和监控子进程，提供了预检查钩子、错误处理钩子和完成处理钩子等扩展接口。

## ApplicationWrapper 类说明

 ApplicationWrapper 继承自 QObject，负责对指定可执行文件进行存在性检查、启动并监控其运行状态。其主要职责包括应用调度（depatch）、参数设置、进程句柄获取以及运行结束后的结果通知。

构造函数说明

```
explicit ApplicationWrapper(QObject* parent, QMainWindow* desktopWindow)
```

该构造函数接收两个参数用于对象初始化，其一 parent 指定 QObject 的父对象以支持 Qt 对象树管理，其二 desktopWindow 用于关联主窗口，必要时可用于显示子进程相关的 UI 或消息对话框。

拷贝限制
通过 Q_DISABLE_COPY(ApplicationWrapper) 宏禁用了拷贝构造与赋值操作，以防止多重实例对同一子进程的管理冲突。

内部结构体说明
 ApplicationDepatchResult 结构体用于封装调度检查结果。其中枚举 AppDepatchResult 支持三种结果状态：应用启动正常（APP_RUN_OK）、可执行文件缺失（APP_FILE_MISSING）及其他错误（APP_OTHER_ERROR）；布尔成员 depatched 表示是否已执行过调度；字符串 someOtherDetails 可用于描述更详细的错误或警告信息。
 ApplicationFinishResult 结构体用于封装进程退出状态，枚举 AppFinishResult 包含正常退出（QUIT_NORMAL）和异常退出（QUIT_OTHER）；整型 exit_code 表示子进程的返回码。

公有方法说明

```
bindAppWidget(AppWidget* appWidget) noexcept 
```

用于绑定 UI 层的 AppWidget 对象，该方法不抛出异常，调用后可通过 app_widget() 获取。

```
app_widget() const 
```

返回先前绑定的 AppWidget 指针，若未绑定则返回空指针。

```
install_app_code(AppCode code) noexcept 
```

接收一个整型应用标识符，用于快速定位或区分不同子进程实例。

```
app_code() const 
```

返回已安装的应用标识符。

```
set_app_path(const QString& app_path) noexcept
```

 将待执行的应用程序完整路径保存至内部成员，不抛出异常。

```
get_app_path() const
```

 返回此前设置的应用程序路径字符串。

```
install_args(const QStringList& l) noexcept
```

 用于传入命令行参数列表，不抛出异常。

```
args() const
```

 返回当前保存的命令行参数列表。

```
process_handle() const
```

 返回指向内部 QProcess 对象的指针，用户可通过该指针获取标准输入输出流或进一步控制进程。

```
depatch_app() 
```

用于启动应用调度流程。若已安装预检查函数（通过 install_prelaunched），则先调用该函数以决定是否执行真正的启动操作。调度完成后根据结果触发 app_depatch_status 信号或调用错误处理钩子。

```
install_prelaunched(PreLaunchIndicate precheck)
```

 将用户自定义的预检查函数保存至内部成员，该函数原型为 

```
ApplicationDepatchResult(*)(ApplicationWrapper*)
```

，可在调度前执行自定义逻辑，并返回是否允许启动或错误信息。

```
install_finhook(HandlingFinHook hook)
```

 安装用户自定义的运行结束钩子，函数原型为 

```
void(*)(ApplicationWrapper*, int, QProcess::ExitStatus)
```

，可在子进程退出时执行额外处理。
 install_error_handler(ErrorDepatchHook hook) 安装调度错误处理钩子，函数原型为 

```
void(*)(ApplicationWrapper*)
```

，当调度失败且未通过信号处理时将调用该钩子。

### 信号说明

```
app_depatch_status(ApplicationWrapper::ApplicationDepatchResult) 
```

当调度检查完成后发出，携带 ApplicationDepatchResult 结构体，可用于 UI 更新或日志记录。

```
app_finished(ApplicationWrapper::ApplicationFinishResult)
```

当子进程退出时发出，携带 ApplicationFinishResult 结构体，用于通知外部进程结束状态。

私有方法说明

```
do_fin_hook(int exitCode, QProcess::ExitStatus status)
```

 为内部调用方法，用于在接收到 QProcess 的 finished 信号后执行用户安装的完成钩子或默认逻辑，并最终发出 app_finished 信号。

```
def_error_handler()
```

 为内部默认的调度错误处理函数，当用户未安装自定义错误处理钩子且调度失败时，将执行该方法。

私有成员说明

-  mainWindow 保存传入的主窗口指针，用于跟桌面 UI 交互。
-  appProcess 指向实际管理子进程的 QProcess 对象，初始化为 nullptr，在 depatch_app 方法中创建并启动。
-  app_path 与 app_args 分别存储待执行文件路径与参数列表。
-  internal_app_code 存储用户安装的整数型应用标识符。
-  appWidget 保存外部传入的 AppWidget，用于 UI 显示或其它绑定需求。
-  pre_indicate、rawAppFinHook 与 error_handler 分别保存用户安装的预检查钩子、完成钩子与调度错误钩子。

​	当然，各位使用这些代码的朋友，除非是想更改这样的底层派发逻辑，不需要直接修改这里的代码，想要自己静态的修改默认的行为，可以在同文件夹调用PageSetuper接口中的方法定制化的完成自己的任务（包括单开一页等）