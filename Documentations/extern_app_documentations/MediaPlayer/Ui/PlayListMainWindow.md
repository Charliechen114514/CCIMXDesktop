------

# `PlayListMainWindow`

**文件位置：** `PlayListMainWindow.h`

**基类：** `QMainWindow`

------

#### 构造函数

```cpp
explicit PlayListMainWindow(QWidget* parent = nullptr);
```

允许指定父窗口的构造函数。

------

#### 析构函数

```cpp
~PlayListMainWindow();
```

析构函数，负责资源清理。

------

#### 公有成员函数

- `void flip_edit_mode();`
   切换编辑模式状态。

------

#### 信号

- `void refresh_media_list();`
   通知刷新媒体列表，通常由点击项目触发。
- `void play_media(const QString& media_src);`
   请求播放指定的媒体资源。
- `void delete_media(const QString& media_src);`
   请求删除指定的媒体资源。

------

#### 公有槽函数

- `void from_media_list(const QStringList& l);`
   从媒体列表接收数据。

------

#### 私有槽函数

- `void process_select_delete();`
   处理选择删除操作。
- `void process_item_click();`
   处理项目点击事件。

------

#### 私有成员变量

- `Ui::PlayListMainWindow* ui;`
   界面UI指针。
- `bool in_edit_mode { false };`
   标记是否处于编辑模式。

------