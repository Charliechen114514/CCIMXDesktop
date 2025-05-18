# 模块名称 FileInfoProvider

## 功能概述

 FileInfoProvider 是一个抽象基类，用于向自定义的 CCIMXFileSystemModel 提供文件信息的扩展接口。它将每个文件条目的分类名称与自定义数据生成逻辑封装在子类中，便于在文件系统模型中按需注入不同的显示或排序信息。

## 类结构说明

 FileInfoProvider 禁用复制构造与赋值操作，因此每个提供者实例只能在创建时绑定一次模型对象。该类通过构造函数接收一个 CCIMXFileSystemModel 指针，并将其保存在受保护的成员 models 中，以便子类在实现数据获取逻辑时访问模型的其它方法。

## 构造与析构

 构造函数 FileInfoProvider(CCIMXFileSystemModel* models) 将传入的模型指针保存至内部成员；析构函数为虚析构，保证继承层次中的动态释放能够正确调用子类析构逻辑。

## 公有接口

 provide_section_name 是一个纯虚函数，用于返回当前提供者所对应的文件分区或分类名称。子类必须实现此方法，以便 FileSystemModel 在界面上显示各个分区的标题。
 setCurrentHandlePath 和 currentHandlePath 是一对简单的路径缓存接口。调用 setCurrentHandlePath 可以将后续数据查询所依赖的目录路径保存至私有成员 cached_path，currentHandlePath 返回最新设置的路径字符串，方便子类在 data 方法中使用。
 data 同样为纯虚函数，接受一个 QModelIndex 对象和一个角色标识 role，返回一个 std::pair<bool, QVariant>。第一项布尔值表示该提供者是否为该索引和角色生成了有效数据，第二项 QVariant 则承载具体的值。子类应根据 index 指向的文件条目和 role 参数决定是否要返回自定义信息，并在成功时将 flag 设为 true。

## 受保护成员

 models 成员保存了构造时传入的 CCIMXFileSystemModel 指针，子类可在 data 实现中调用模型自身的方法或访问其内部数据。

## 私有成员

 cached_path 用于记录最后一次通过 setCurrentHandlePath 设置的目录路径，子类在 data 方法中可通过 currentHandlePath 获取该路径，便于基于当前处理目录的上下文逻辑。

## 使用示例

 在实际使用中，先定义一个继承自 FileInfoProvider 的子类，并在构造函数中将模型指针传入基类构造。重载 provide_section_name 返回例如“图片”、“文档”或“系统文件”等分区名称。重载 data 方法时，根据传入的 index.row 和 role 值，调用 models 提供的文件路径解析方法，并生成对应的文件大小、最后修改时间或自定义图标等信息。如果该提供者对当前索引无关，则返回 {false, QVariant()}。之后，将子类实例注册到 CCIMXFileSystemModel 中，模型即可在视图中自动调用这些提供者，展示分区标题及扩展列的数据。