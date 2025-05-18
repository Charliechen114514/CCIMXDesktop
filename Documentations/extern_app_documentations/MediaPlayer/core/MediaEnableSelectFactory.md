

#### 命名空间：`MediaEnableSelectFactory`

该命名空间提供一组静态函数，用于选择和生成支持的媒体文件过滤器。

------

#### 函数声明

- `QString get_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);`
   该函数弹出同步文件选择对话框，允许用户选择一个符合媒体过滤条件的单个文件，返回所选文件的路径。
- `QString generateMediaEnableFilter();`
   生成并返回支持的媒体文件过滤字符串，用于文件对话框的过滤条件。
- `QStringList get_all_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);`
   弹出同步文件选择对话框，允许用户选择多个符合媒体过滤条件的文件，返回所有选中文件路径列表。

------

#### 依赖

- 使用了 `QString` 和 `QStringList` 类型。
- 使用了 Qt 界面类 `QWidget` 用作父窗口参数。

------

该头文件设计为工具性质，主要负责统一管理媒体文件的过滤条件和文件选择操作。

------