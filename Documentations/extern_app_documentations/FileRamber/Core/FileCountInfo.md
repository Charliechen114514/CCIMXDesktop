# 模块名称 FileCountInfo 与 FileCountImplWorker

功能概述
 FileCountImplWorker 是一个后台计数任务执行者，继承自 QObject，利用 QtConcurrent 提交异步任务，统计指定目录下文件和子目录的总数，并通过信号回调将结果传回。FileCountInfo 同时继承自 QObject 和 FileInfoProvider，用于向自定义的文件系统模型 CCIMXFileSystemModel 提供“文件计数”列数据，通过异步统计和缓存机制，在视图中动态呈现每个目录条目的文件数量。

FileCountImplWorker 说明
 FileCountImplWorker 构造时可指定父对象以加入 Qt 对象树，析构时负责清理挂起的异步任务。其核心方法 deptach_count_task 接收一个 QPersistentModelIndex 和对应的目录路径字符串，向 QtConcurrent 提交统计任务并将结果通过 fileCountFinished 信号返回。内部维护一个 QFuture 列表以避免任务被提前销毁。

FileCountInfo 说明
 FileCountInfo 在构造时将传入的 CCIMXFileSystemModel 指针传递给 FileInfoProvider 基类，并实例化一个 FileCountImplWorker 用于并行统计工作。provide_section_name 方法返回列标题“fileCounts”，用于文件视图显示该列名称。data 方法在接收到模型请求时，根据角色和索引决定是否提供数据：如果当前角色为显示角色且缓存中已有结果，则立即返回包含计数值的 QVariant；如果尚未请求且路径有效，则通过 worker 发起异步统计并将该索引加入 requested 集合，返回空数据以等待后续更新。其他情况均返回不提供数据。

信号与槽机制
 FileCountImplWorker 的 fileCountFinished 信号在统计任务完成后发出，携带对应的 QModelIndex 和统计得到的文件数量。FileCountInfo 通过 onHandleWorkFinishJob 槽接收该信号，将结果存入缓存 cache，并从 requested 集合中移除该索引，随后通知模型触发数据更新（通常通过 QAbstractItemModel::dataChanged），以在视图中刷新显示最终的文件数量。

内部成员
 worker 成员指向 FileCountImplWorker 实例，负责后台任务提交与执行。cache 使用可变的 QHash 将已完成统计的索引与对应数量存储，实现缓存以避免重复计算。requested 使用可变的 QSet 记录正在进行统计的索引，防止重复提交相同目录的统计任务。

## 使用说明

 在模型初始化阶段，将 FileCountInfo 实例注册到 CCIMXFileSystemModel 的提供者列表中。首次显示某个目录时，模型会调用该提供者的 data 方法触发异步统计，待统计完成后 FileCountInfo 会自动更新视图中的“fileCounts”列，后续再次访问同一目录则直接从缓存中读取计数结果，提高性能并保证界面响应流畅。