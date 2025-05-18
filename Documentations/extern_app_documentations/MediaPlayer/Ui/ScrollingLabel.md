------

# `ScrollingLabel`

**文件位置：** `ScrollingLabel.h`

**基类：** `QWidget`

------

#### 静态常量

```cpp
static constexpr const int ANIMATION_INTERVAL = 100;
```

动画定时器触发的时间间隔，单位为毫秒。

```cpp
static constexpr const short STEP_SHORT = 2;
```

文本滚动的步进长度，单位为像素。

------

#### 构造函数

```cpp
explicit ScrollingLabel(QWidget* parent = nullptr);
```

构造函数，可指定父控件，默认无父控件。

------

#### 公有方法

```cpp
void setText(const QString& text);
```

设置显示的文本内容，启动或重置滚动动画。

------

#### 析构函数

```cpp
~ScrollingLabel();
```

析构函数，释放资源。

------

#### 保护方法

```cpp
void resizeEvent(QResizeEvent*) override;
```

重载窗口大小改变事件，触发滚动显示更新。

------

#### 私有槽函数

```cpp
void scrollText();
```

滚动文本位置的槽函数，由定时器周期调用。

```cpp
void updateScroll();
```

更新滚动显示参数，重新计算文本显示区域。

------

#### 私有成员变量

```cpp
Ui::ScrollingLabel* ui;
```

指向界面布局的指针。

```cpp
QTimer timer;
```

定时器，用于控制文本滚动的刷新频率。

```cpp
int offset { 0 };
```

当前文本滚动的偏移量，单位为像素。