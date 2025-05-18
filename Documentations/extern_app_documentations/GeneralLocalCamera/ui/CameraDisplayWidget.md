------

# `CameraDisplayWidget`

**文件位置：** `CameraDisplayWidget.h`

**基类：** `QWidget`

**职责概述：**
 提供用于显示摄像头捕获图像的界面组件，支持更新当前帧图像并获取当前显示内容。

------

#### 构造函数

```cpp
explicit CameraDisplayWidget(QWidget* parent = nullptr);
```

构造函数，允许指定父控件，默认无父控件。

------

#### 公有方法

```cpp
void setCurrentFrame(const QImage& image);
```

设置当前显示的摄像头捕获帧，参数为图像数据。

```cpp
QPixmap current_captures() const;
```

获取当前显示的图像内容，返回一个 `QPixmap` 类型。

------

#### 析构函数

```cpp
~CameraDisplayWidget();
```

析构函数，释放相关资源。

------

#### 私有成员

```cpp
Ui::CameraDisplayWidget* ui;
```

指向界面布局的指针，管理UI控件。