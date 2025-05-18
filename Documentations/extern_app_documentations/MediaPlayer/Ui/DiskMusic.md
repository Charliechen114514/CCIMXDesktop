------

# `DiskMusic`

**文件位置：** `DiskMusic.h`

**基类：** `QWidget`

------

#### 属性

- `Q_PROPERTY(qreal armAngle READ armAngle WRITE setArmAngle NOTIFY armAngleChanged)`

  表示唱针的旋转角度，支持读取、写入及变化通知。

------

#### 静态常量

- `ANIMATION_DURATION`：动画持续时间，单位毫秒，值为300。
- `ANIMATION_FPS`：动画帧率，值为60帧每秒。
- `BEGIN_ANGLE`：唱针初始角度，-30度。
- `END_ANGLE`：唱针结束角度，-10度。
- `SWITCH_COLOR_MSEC_INTERVAL`：颜色切换间隔时间，20000毫秒。
- `COLOR_SWITCH_PROCESS_INTERVAL`：颜色切换过程时间，2000毫秒。
- `BEGIN_COLOR`：颜色渐变起始色，RGB(173,216,230)。
- `END_COLOR`：颜色渐变结束色，RGB(0,51,102)。

------

#### 构造函数

```cpp
explicit DiskMusic(QWidget* parent = nullptr);
```

可指定父控件的构造函数。

------

#### 析构函数

```cpp
~DiskMusic();
```

析构函数。

------

#### 公有方法

```cpp
void setStatus(bool set_is_playing);
```

设置播放状态，控制动画播放或暂停。

```cpp
void setPixmap(const QString& pixmap_path);
```

设置唱片封面图片路径。

```cpp
qreal armAngle() const;
```

获取当前唱针角度。

```cpp
void setArmAngle(qreal angle);
```

设置唱针角度，并触发界面更新与信号通知。

------

#### 信号

```cpp
void armAngleChanged();
```

唱针角度变化信号。

------

#### 保护方法

```cpp
void paintEvent(QPaintEvent*) override;
```

重载绘制事件，负责绘制唱片、唱针等界面元素。

------

#### 私有成员变量

- `Ui::DiskMusic* ui;` 界面指针。
- `qreal angle` 当前唱针角度，初始为`BEGIN_ANGLE`。
- `float current_rotations` 当前唱片旋转角度，单位度。
- `bool is_playing` 播放状态标志。
- `QTimer animate_timer` 动画计时器，用于驱动旋转。
- `QPropertyAnimation* animation` 用于唱针角度的属性动画。
- `QVariantAnimation* color_animation` 用于颜色渐变动画。
- 结构体 `pixmaps` 存储封面图、唱针图和唱片图。
- `QColor beginColor, endColor` 当前渐变颜色起止色。
- `QColor targetStart, targetEnd` 目标渐变颜色起止色。
- `QTimer color_switch_timer` 用于定时切换颜色。

------

#### 私有方法

- `void initUi();` 界面初始化。
- `void initCore();` 核心逻辑初始化。
- `void process_rotation();` 更新唱片旋转角度及界面刷新。
- `void process_the_color_change(QPainter& p);` 绘制时处理颜色渐变。
- `void startColorTransition();` 启动颜色渐变动画。

------