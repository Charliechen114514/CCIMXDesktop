# 模块名称 FileNameProviders

功能概述
 `FileNameProviders` 是一个继承自 `FileInfoProvider` 的信息提供器类，用于在文件系统视图中增强“文件名”列的展示效果。它的主要职责是根据文件扩展名对不同类型的文件名应用颜色标记，同时为目录指定特定颜色。该类适用于在 UI 中突出显示具有特定类型或重要性的文件，使用户能快速区分和识别文件内容。

构造与初始化
 构造函数 `FileNameProviders(CCIMXFileSystemModel* models)` 将外部文件系统模型传入并传递给基类。构造过程中不承担具体逻辑初始化任务，颜色映射关系需通过后续注册函数完成配置。

主要接口说明
 方法 `provide_section_name()` 返回固定字符串 `"FileName"`，标识该提供器服务于“文件名”一栏的装饰处理。
 核心函数 `data(const QModelIndex& index, int role)` 实现了根据模型索引返回颜色信息的功能。该方法内部会调用私有函数 `handle_extension_color()`，判断当前条目是否为目录或普通文件，并根据其扩展名或目录属性选择合适的颜色。

颜色映射机制
 类使用 `QMap<QString, QColor>` 类型的成员变量 `mappings` 维护文件扩展名与对应颜色的映射关系。通过方法 `registerColorPairs(const ColorPairs& pairs)` 可注册额外的映射条目，其中 `ColorPairs` 是扩展名与颜色的配对形式，用于批量或动态扩展支持的文件类型。
 此外，可通过 `register_special_dircolor()` 方法单独设置目录类型的统一显示颜色，默认情况下为深洋红（`Qt::darkMagenta`）。

行为逻辑说明
 私有函数 `handle_extension_color()` 会优先判断条目是否为目录；若是，则直接返回 `dirent_color`。若为普通文件，则获取其扩展名，并在 `mappings` 表中查找对应颜色。若未找到，可能返回空颜色或保持默认。该处理逻辑通常在 `Qt::ForegroundRole` 或 `Qt::TextColorRole` 下触发，实现对文件名文字颜色的自定义。

功能特性
 `FileNameProviders` 提供了简单有效的视觉高亮能力，适用于基于内容类型的可视化管理需求，例如高亮脚本文件、可执行文件、文档类文件或媒体类文件等。同时，该类可作为 UI 侧风格系统的组成部分，与图标映射、标签显示等模块协同工作。