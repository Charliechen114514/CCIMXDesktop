------

# `MediaInfoWindow`

**文件位置：** `MediaInfoWindow.h`

**基类：** `QMainWindow`

------

#### 构造函数

```cpp
explicit MediaInfoWindow(QWidget* parent = nullptr);
```

构造函数，可指定父窗口。

------

#### 析构函数

```cpp
~MediaInfoWindow();
```

析构函数，负责清理资源。

------

#### 公有槽函数

```cpp
void filled_metainfo(const MediaInfo info);
```

接收并填充媒体信息，参数为 `MediaInfo` 类型的数据结构。

------

#### 私有成员变量

- `Ui::MediaInfoWindow* ui;` 指向界面UI对象的指针。

------