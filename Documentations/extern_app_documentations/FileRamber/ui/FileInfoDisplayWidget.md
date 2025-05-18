# `FileInfoDisplayWidget`

**文件位置：** `FileInfoDisplayWidget.h`

**基类：** `QWidget`

**职责概述：**
 该类是一个用于图形界面展示的文件信息显示组件，结合 `CCIMXFileSystemModel`，能够根据用户选择的文件项展示该项的多个扩展属性信息，如大小、类型、文件数等。其界面通过 UI 设计器 `.ui` 文件实现布局，内部通过 `QModelIndex` 驱动数据更新。

------

#### 常量

```cpp
static constexpr const unsigned short ICON_SIZE = 32;
```

定义文件图标的统一显示尺寸（32 像素），用于与模型中关联的文件项配套渲染视觉标识。

------

#### 构造函数

```cpp
explicit FileInfoDisplayWidget(QWidget* parent = nullptr);
```

构造一个文件信息展示控件，并可指定其父窗口部件。初始化界面并准备模型绑定能力。

------

#### 析构函数

```cpp
~FileInfoDisplayWidget();
```

析构函数，负责资源清理，包括 UI 指针释放。

------

#### 公有成员函数

```cpp
inline void bind_models(CCIMXFileSystemModel* models);
```

绑定一个外部文件系统模型，该模型应包含拓展的 `FileInfoProvider` 支持。该函数应在数据展示前调用，以保证后续数据正确性。

```cpp
void setModelIndex(const QModelIndex& index);
```

设定当前正在展示的模型索引，触发内部 UI 更新操作。此函数应在用户选中文件项、文件树更新或响应点击事件时调用，从而使控件根据新索引刷新内容显示。

------

#### 私有成员变量

```cpp
Ui::FileInfoDisplayWidget* ui;
```

指向通过 Qt Designer 生成的界面对象，用于统一管理界面布局与控件。

```cpp
CCIMXFileSystemModel* models { nullptr };
```

当前绑定的数据模型指针，提供文件属性的源信息。



------