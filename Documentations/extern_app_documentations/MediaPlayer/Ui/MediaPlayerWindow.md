------

# `MediaPlayerWindow`

**文件位置：** `MediaPlayerWindow.h`

**基类：** `QMainWindow`

------

#### 友元类

- `MediaPlayerWindowHelper`

------

#### 构造函数

```cpp
MediaPlayerWindow(QWidget* parent = nullptr);
```

构造函数，允许指定父窗口。

------

#### 析构函数

```cpp
~MediaPlayerWindow();
```

析构函数，负责释放相关资源。

------

#### 公有成员函数

- `void open_media();`
   通过对话框打开单个媒体文件。
- `void open_medias();`
   通过对话框打开多个媒体文件。
- `void toggle_playing_status();`
   切换播放和暂停状态。
- `void forward10sec();`
   快进10秒。
- `void backward10sec();`
   后退10秒。
- `void flow_mode_once();`
   执行一次播放模式切换。

------

#### 私有槽函数

- `void handle_display_src(bool available, const QImage& image);`
   处理是否有可用图像显示。
- `void handle_imageDisplay(const QImage& image);`
   处理图像显示。
- `void handle_new_durations(qint64 duration);`
   处理新时长更新。
- `void handle_position_changed(qint64 position);`
   处理播放位置变化。
- `void handle_media_end();`
   处理媒体播放结束事件。
- `void handle_slider_position_changed(int position);`
   处理滑块位置变化。
- `void handle_slider_pressed();`
   处理滑块按下事件。
- `void handle_slider_released();`
   处理滑块释放事件。

------

#### 私有成员变量

- `Ui::MediaPlayerWindow* ui;` 界面UI指针。
- `MediaPlayer* mediaPlayer { nullptr };` 媒体播放器对象指针。
- `MediaInfoWindow* infoWindow { nullptr };` 媒体信息窗口指针。
- `CCMediaPlayList* medialist { nullptr };` 播放列表对象指针。
- `PlayListMainWindow* playListWindow { nullptr };` 播放列表窗口指针。
- `bool manual_sliding { false };` 是否手动拖动滑块标志。
- `bool is_playing { false };` 播放状态标志。
- `bool video_available { false };` 视频可用状态标志。

------

#### 私有成员函数

- `void init_memories();`
   初始化存储相关的设置或状态。
- `void init_core_connections();`
   初始化核心信号槽连接。
- `void init_ui_connections();`
   初始化界面信号槽连接。
- `void init_connections();`
   初始化综合信号槽连接。
- `void post_do_video_unavailable();`
   当视频不可用时的处理逻辑。
- `void post_init_ui();`
   界面初始化后的处理。
- `void process_playing_status();`
   处理播放状态变化。
- `void process_playmode_switching();`
   处理播放模式切换。
- `void handle_according_mails(const MediaListMails mails);`
   根据播放列表邮件类型执行相应处理。

------