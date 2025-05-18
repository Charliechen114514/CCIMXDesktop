# 模块名称 FileTypeInfo

## 功能概述

 `FileTypeInfo` 是一个继承自 `FileInfoProvider` 的具体实现类，用于为 `CCIMXFileSystemModel` 提供每个文件条目的“文件类型”信息。其通过文件扩展名（suffix）查找对应的人类可读类型名称，并在 `QModelIndex` 请求时返回该值以供界面显示。该功能一般用于文件管理器中的“类型”列，使用户能快速识别文件内容。

## 构造与初始化

 `FileTypeInfo` 构造函数接收 `CCIMXFileSystemModel` 指针并传递给基类 `FileInfoProvider`，同时内部初始化一个 `QMap<QString, QString>` 类型的 `mappings` 成员，该映射表定义了扩展名与类型描述之间的对应关系，例如 `.jpg` 映射为“JPEG Image”。这张映射表的初始化过程不在头文件中体现，通常应在 cpp 实现文件中手动填充常见文件类型映射。

## 接口说明

 提供的 `provide_section_name()` 方法返回列标题字符串“File Type”，供模型在展示列名时使用。
 主要的数据接口 `data(const QModelIndex& index, int role)` 会在模型请求对应单元格数据时调用。内部应判断当前角色是否为显示数据角色（如 `Qt::DisplayRole`），若是则提取对应文件的后缀名，根据 `mappings` 查表获取人类可读类型描述，并封装为 `QVariant` 返回。如果是目录或无扩展名文件，可能返回“Folder”或“Unknown”等默认值（该逻辑一般位于 cpp 实现中）。返回值为 `std::pair<bool, QVariant>`，其中布尔值表示是否提供了数据。

## 额外辅助方法

 成员函数 `typeInfo(const QString& suffix)` 公开映射查询接口，允许外部直接使用后缀名获取类型描述字符串，其内部实现即为 `mappings.value(suffix)`。

## 成员变量

 `mappings` 是用于存储扩展名到类型描述的映射表，定义了支持识别的文件类型。例如：`"jpg" -> "JPEG Image"`，`"cpp" -> "C++ Source File"`，`"mp4" -> "MPEG-4 Video"` 等。

## 使用说明

 该类实例应由模型创建并注册至其提供者链中，当视图请求某一行文件的“File Type”列数据时，即通过 `data()` 接口返回相应的类型字符串。适用于文件浏览器、资源管理器、桌面管理器等需要显示文件类型信息的场合。通过集中映射控制，支持可扩展性与统一风格管理。