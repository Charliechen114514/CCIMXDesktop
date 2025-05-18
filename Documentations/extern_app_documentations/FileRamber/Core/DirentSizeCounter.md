# 模块名称 DirentSizeCounter 与 DirentSizeWorker

功能概述
 DirentSizeWorker 是一个后台任务执行者，基于 QObject 与 QtConcurrent，用于异步计算指定目录项（文件或文件夹）的总大小，并通过信号通知任务完成。DirentSizeCounter 继承自 QObject 与 FileInfoProvider，作为文件系统模型的扩展提供者，在文件视图中为每个条目异步展示文件大小信息，并对计算结果进行缓存与去重请求控制。

DirentSizeWorker 说明
 DirentSizeWorker 构造时可指定父对象，析构时会释放挂起的任务。其核心方法 depatch_sizeCount_task 接收一个 QPersistentModelIndex 和对应的文件系统路径，向 QtConcurrent 提交大小计算任务，并在任务完成后通过 sizeCountFinish 信号返回条目索引与计算结果。内部维护一个 QFuture 列表 results，以防任务被过早销毁。

DirentSizeCounter 说明
 DirentSizeCounter 继承自 FileInfoProvider，实现了 provide_section_name 与 data 两个纯虚方法，用于在自定义的 CCIMXFileSystemModel 中生成“File Size”列的数据。构造时将模型指针传入基类，并实例化一个 DirentSizeWorker，用于并行计算文件大小。

公有接口
 provide_section_name 返回列标题“File Size”，用于在视图中显示该扩展列名称。
 data 接受 QModelIndex 与角色 role，当角色为 Qt::DisplayRole 时：

- 如果缓存中已有该索引的大小结果，直接返回 {true, QVariant(大小值)}；
- 如果尚未发起计算且路径非空，则通过 worker 发出异步计算请求，并标记为已请求，返回 {false, QVariant()} 表示暂不提供数据；
   对其他角色或不适用条目，返回 {false, QVariant()}。

槽函数
 onHandleWorkFinishJob 用于接收 DirentSizeWorker 的 sizeCountFinish 信号。收到索引与大小后，将结果存入 cache，并移除 requested 集合中的该索引，随后触发模型更新（例如调用 QAbstractItemModel::dataChanged），使视图在下次重绘时能够显示新的大小数据。

私有成员
 worker 指向 DirentSizeWorker 实例，负责实际的并行计算。
 cache 是一个可变 QHash，将已计算完成的索引与对应大小值存储起来，实现结果缓存。
 requested 是一个可变 QSet，用于记录已发起计算但尚未完成的索引，避免重复提交同一路径的计算任务。

## 使用示例

 在文件系统模型初始化时，将 DirentSizeCounter 实例添加到模型的提供者列表中；在视图展示过程中，模型在 data 回调中根据该提供者的返回值填充“File Size”列。第一次打开一个目录时，sizeCountCounter 会调度异步任务计算文件大小，并在计算完成后自动刷新该单元格显示最终大小；若用户切换到其他目录或同一条目再次显示，已缓存结果可立即呈现，无需重复计算。