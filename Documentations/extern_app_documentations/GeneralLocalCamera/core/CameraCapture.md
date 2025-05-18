------

# 类名：`CameraCapture`

**文件位置：** `CameraCapture.h`

**基类：** `QObject`

**职责概述：**
 `CameraCapture` 类用于控制摄像头的开启、关闭与图像采集，并可将图像结果传递给绑定的显示部件，适用于视频采集与预览功能的构建。

------

#### 枚举类型

```cpp
enum class Error {
	CAMERA_UNEXSITED,
	CAMERA_UNOPENED,
	CAMERA_UNBIND_DISPLAY,
	CAMERA_MULTI_OPENED
};
```

表示摄像头操作过程中可能发生的错误类型，包括设备不存在、未能打开、未绑定显示部件或重复打开等情况。

------

#### 构造函数

```cpp
explicit CameraCapture(const int index, QObject* parent);
```

创建一个 `CameraCapture` 实例，绑定指定索引的摄像头。构造时不立即启动采集，仅配置基本状态。

------

#### 析构函数

```cpp
~CameraCapture();
```

销毁对象，释放摄像头句柄与相关资源。

------

#### 公有函数

```cpp
void bind_display_widget(CameraDisplayWidget* widget);
```

将一个显示部件绑定至此采集器，用于展示采集到的图像帧。必须在开始采集前绑定。

```cpp
void set_capture_delay_time(const int gap_time);
```

设置图像帧采集的时间间隔，单位为毫秒。影响内部采集线程的休眠时间。

```cpp
bool isActivate() const;
```

返回当前采集器是否处于工作状态。

```cpp
bool start();
```

尝试启动摄像头采集流程。成功后将持续读取图像并投递至显示部件。

```cpp
bool close();
```

停止当前摄像头采集流程，并释放资源。

------

#### 信号

```cpp
void cameraOpened(int index);
```

摄像头成功打开后发出的信号，参数为摄像头索引。

```cpp
void cameraClosed(int index);
```

摄像头被关闭时发出的信号，参数为摄像头索引。

```cpp
void errorOccur(CameraCapture::Error e);
```

在采集过程中发生错误时发出的信号，参数为错误类型枚举值。

------

#### 私有成员变量

```cpp
cv::VideoCapture* videoCaptureHandle { nullptr };
```

OpenCV 的摄像头句柄指针，用于底层图像采集。

```cpp
int current_index { -1 };
```

当前采集的摄像头索引编号。

```cpp
CameraDisplayWidget* widget { nullptr };
```

用于图像展示的绑定部件指针。

```cpp
QMutex* capMutex;
```

用于采集线程同步的互斥锁指针。

```cpp
std::atomic_bool internal_running_state_holder { false };
```

内部采集状态标志，控制是否继续采集图像帧。

```cpp
int msleep_time { 10 };
```

每帧采集后的休眠时间，单位为毫秒。

------

#### 私有成员函数

```cpp
void capture_internal();
```

摄像头内部循环采集函数。注意，这里采用的实际上是基于QTimer的SingleShot触发机制，让采集纳入大循环当中，因为照片采集不需要太强的实时性

------