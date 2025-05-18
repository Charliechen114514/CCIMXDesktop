# VideoPlayerOpencvImpl

继承自 VideoPlayerImpl，基于 OpenCV 实现的视频播放器。

构造与析构函数

- VideoPlayerOpencvImpl()：构造函数，初始化播放器实例。
- ~VideoPlayerOpencvImpl()：析构函数，释放资源。

重载函数

- int total_frame() const：返回视频总帧数。
- int current_frame()：返回当前播放的帧索引。
- bool rollto_nextFrame(CVImage& container)：读取下一帧图像到 container，成功返回 true，失败返回 false。
- bool peek_frame(CVImage& container, int frame_request)：预览指定帧（frame_request）到 container，成功返回 true，失败返回 false。
- VideoPlayerInfo current_video_info() const：返回当前视频的信息（如宽度、高度、帧率等）。
- bool open(const char* filename, VideoPlayerOpenErrorCode& error_code)：打开视频文件，失败时通过 error_code 返回错误码，成功返回 true。
- void close()：关闭当前视频并释放资源。
- bool isOpened() const：判断视频是否已成功打开。
- void escapeFrame()：跳过当前帧，准备读取下一帧。
- void jumpToFrame(int frame_request)：跳转到指定帧索引。

私有成员

- cv::VideoCapture* internal_capture：OpenCV 视频捕获对象指针。
- int internal_current_frame：当前帧索引，初始化为无效帧常量 INVALID_VIDEO_FRAME_N。