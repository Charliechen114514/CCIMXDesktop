------

# `CameraWindow`

**文件位置：** `CameraWindow.h`

**基类：** `QMainWindow`

------

#### 构造函数

```cpp
CameraWindow(QWidget* parent = nullptr);
```

构造函数，可指定父窗口，默认为无父窗口。

------

#### 公有方法

```cpp
void fresh_cameralists();
```

刷新摄像头设备列表。

```cpp
void redirect(const QString path);
```

重定向保存路径到指定目录。

------

#### 析构函数

```cpp
~CameraWindow();
```

析构函数，清理相关资源。

------

#### 私有槽函数

```cpp
void on_btn_oppose_camera_clicked();
```

响应反向摄像头按钮点击事件。

------

#### 私有方法

```cpp
void setup_internal();
```

初始化内部组件和状态。

```cpp
void select(int index);
```

选择指定索引的摄像头设备。

```cpp
void process_oppose_state(bool prev_opened);
```

处理摄像头开启或关闭的状态切换，参数表示之前是否已开启。

```cpp
void capture_photo_once();
```

执行一次拍照操作。

------

#### 私有成员变量

```cpp
Ui::CameraWindow* ui;
```

指向界面布局的指针。

```cpp
CameraCapture* camera_capture;
```

摄像头捕获管理对象指针。

```cpp
DesktopToast* toast;
```

桌面提示组件指针。

```cpp
QString cached_path;
```

缓存的照片保存路径。