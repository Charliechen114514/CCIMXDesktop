# `MainWindow`

**文件位置：** `MainWindow.h`

**基类：** `QMainWindow`

**职责概述：**
 该类是整个应用程序的主窗口，负责管理界面布局、文件系统视图与信息展示逻辑。集成了用户界面、文件系统模型和多种文件信息提供器，能够响应用户的交互事件（如双击或选中）以更新显示内容。

------

#### 构造函数

```cpp
MainWindow(QWidget* parent = nullptr);
```

构造主窗口并初始化界面与相关数据结构，包括模型初始化、控件布置和信号连接。

------

#### 析构函数

```cpp
~MainWindow();
```

析构主窗口并释放相关资源。

------

#### 枚举类型

```cpp
enum InfoIndex {
	NameProviders,
	CountProviders,
	DirSizeProviders,
	TypeInfoProviders,
	InfoIndexMax
};
```

用于在 UI 中标识不同的文件信息提供器类型（如文件名、计数、目录大小、类型等），便于后续切换与索引操作。

------

#### 公有成员函数

```cpp
void try_goto_parent_view();
```

尝试跳转至当前目录的上级目录，通常用于响应工具栏中的“返回”按钮或快捷键操作。

```cpp
void switch_to_global_root();
```

切换到系统的根目录。该函数为绕过 Windows 系统中文件根路径处理问题提供手动刷新能力。

------

#### 私有槽函数

```cpp
void processing_switch_double_click(const QModelIndex& index);
```

响应用户在文件系统视图中双击某一项的行为，并处理路径跳转或内容展开等逻辑。

```cpp
void processing_filecheck_issue(const QModelIndex& index);
```

响应文件选中事件，用于更新相关信息展示区或状态栏等界面元素。

------

#### 私有成员函数

```cpp
void setupFileModels();
```

初始化 `CCIMXFileSystemModel` 以及各个附加的 `FileInfoProvider`，实现文件信息扩展能力。

```cpp
void setupUi();
```

布置和初始化主窗口界面，包括主控件、工具栏、状态栏等。

```cpp
void setup_connections();
```

建立信号与槽的连接，包括文件系统视图中的点击、双击信号与逻辑处理槽的绑定。

------

#### 私有成员变量

```cpp
QList<FileInfoProvider*> providers;
```

存储当前使用的所有信息提供器，便于统一绑定至模型并用于信息展示。

```cpp
Ui::MainWindow* ui;
```

通过 Qt Designer 生成的界面对象，负责主窗口布局和控件引用。

```cpp
CCIMXFileSystemModel* file_model { nullptr };
```

自定义的文件系统模型，封装了标准模型基础上的扩展信息支持。

```cpp
QComboBox* box { nullptr };
```

用于切换不同 `FileInfoProvider` 类型的下拉框控件，可能影响右侧显示的详细信息列。

```cpp
QLabel* pwd_label { nullptr };
```

状态栏或主窗口中的路径显示标签，用于展示当前浏览目录的绝对路径。

------