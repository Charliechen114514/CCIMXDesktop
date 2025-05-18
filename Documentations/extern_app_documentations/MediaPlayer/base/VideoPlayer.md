# VideoPlayer

基于 QObject，封装视频播放功能，依赖 VideoPlayerImpl 实现具体细节，支持 OpenCV 视频播放。

构造与析构函数

- explicit VideoPlayer(QObject* parent = nullptr)：构造函数，可指定父对象。
- ~VideoPlayer()：析构函数，释放资源。

核心接口

- bool open(const char* video_path)：打开指定路径的视频文件，成功返回 true，失败通过信号反馈。
- QString current_handle() const：返回当前打开的视频路径。
- bool close()：关闭当前视频，释放资源。
- bool play()：开始或继续播放视频。
- bool pause()：暂停视频播放。
- int total_frame() const：获取视频总帧数。
- int total_msecs() const：获取视频总时长，单位毫秒。
- VideoPlayerInfo get_info() const：获取当前视频信息（宽度、高度、帧率等）。
- int current_frame() const：获取当前播放帧索引。
- bool valid_video() const：判断当前视频是否有效。
- bool is_playing() const：判断视频是否正在播放。
- qint64 currentFrameMSec() const：获取当前帧对应的毫秒时间。
- bool setCurrentFrameMSec(const qint64 msec)：跳转到指定毫秒位置的帧，成功返回 true。
- void escapeFrame()：跳过当前帧，下一帧将被跳过显示。
- bool peekFrame(CVImage& container, int frame_request)：预览指定帧（frame_request）图像，成功返回 true。

信号

- void openError(const VideoPlayerOpenErrorCode error)：打开视频出错时发出错误码。
- void frameReady(const CVImage image)：当前帧图像准备好，等待显示。
- void about_fetch_frame()：即将获取新帧。
- void videoEnd()：视频播放结束。

私有槽

- void time_to_fetch_next_frame()：定时器触发，处理下一帧的获取和显示。

私有成员

- VideoPlayerImpl* impl：视频播放实现的接口指针。
- bool on_play：播放状态标记，true 表示正在播放。
- VideoPlayerInfo info：当前视频的基本信息。
- int play_sleep：播放间隔时间（毫秒），控制播放节奏。
- QString last_open：当前打开视频文件路径。