# 命名空间：`UiTools`

功能说明：

该命名空间包含一组与界面时间显示和滑块控制相关的工具函数。

具体函数：

- `static constexpr const char* TYPICAL_FORMAT = "HH:mm:ss";`
   典型时间格式字符串，表示时:分:秒。
- `QString toMediaTypicalTimeStr(const qint64 time);`
   将时间（毫秒为单位）转换为典型的时间字符串格式。
- `std::pair<qint64, qint64> downcast_to_sliderable_period(qint64 min, qint64 max);`
   将时间区间（毫秒）转换为适合滑块的秒级时间区间。
- `inline qint64 downcast_to_sliderable_position(qint64 position);`
   将时间（毫秒）向下转换为秒数，用于滑块位置。
- `inline qint64 upcast_to_mseconds(qint64 position);`
   将时间（秒）转换回毫秒。
- `QString toScrollLabelText(const QString& src_path);`
   根据文件路径生成用于滚动标签的文本。

------

该头文件定义的函数方便在 UI 组件中处理时间显示和滑块控制相关逻辑。

------