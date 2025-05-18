# VideoPlayerImpl

视频播放器的抽象基类，定义视频播放实现的接口规范，禁止复制操作。

静态常量

- INVALID_VIDEO_FRAME_N：无效帧编号，值为 -1。

枚举类型 VideoPlayerOpenErrorCode

- NoError：无错误。
- DupOpen：重复打开错误。
- FileUnExsited：文件不存在错误。
- OpenFailed：打开失败错误。

结构体 VideoPlayerInfo

- fps：视频帧率。
- width：视频宽度。
- height：视频高度。

成员函数（纯虚函数，需派生类实现）

- int total_frame() const：获取视频总帧数。
- int current_frame()：获取当前帧索引。
- bool rollto_nextFrame(CVImage& container)：播放到下一帧，并将帧图像存入 container。
- bool peek_frame(CVImage& container, int frame_request)：预览指定帧，不改变当前播放状态，图像存入 container。
- VideoPlayerInfo current_video_info() const：获取当前视频信息（帧率、尺寸等）。
- void escapeFrame()：跳过当前帧，后续帧播放将向前推进。
- void jumpToFrame(int frame_request)：跳转到指定帧索引。
- bool open(const char* filename, VideoPlayerOpenErrorCode& error_code)：打开视频文件，返回是否成功，错误通过 error_code 反馈。
- bool isOpened() const：判断视频是否已成功打开。
- void close()：关闭视频，释放资源。

构造与析构

- VideoPlayerImpl()：默认构造函数。
- virtual ~VideoPlayerImpl()：虚析构函数。

禁止复制

- 通过 Q_DISABLE_COPY 宏禁止复制构造和赋值操作。

类 VideoPlayerImplFactory

用于请求 VideoPlayerImpl 的具体实现实例。

静态函数

- static VideoPlayerImpl* request_impl()：请求一个派生 VideoPlayerImpl 的实例，供上层 VideoPlayer 使用。