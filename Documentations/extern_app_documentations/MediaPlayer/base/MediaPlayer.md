# MediaPlayer

用于音视频播放的封装类，集成了视频播放和音频播放功能，并支持音视频同步。

## 枚举类型 MediaError

定义了可能的媒体错误状态，包括无错误、资源不存在、仅视频、仅音频、不支持的资源等。

## 命名空间 MediaPlayerPublicSettings

定义媒体播放器的公共设置，包括允许的最大音视频不同步延迟，默认值为 500 毫秒。

## 结构体 MediaInfo

存储媒体元信息，包括标题、作者、专辑标题、专辑艺术家、作曲家、类型、时长（毫秒）、日期、曲目号、音频码率、音频编码格式、媒体类型、采样率、发布者和封面图片。

## 结构体 MediaPlayerStatus

包含媒体的状态信息，包括音频准备好、视频准备好标志，以及视频和音频的描述信息。

## 方法

构造与析构函数

- explicit MediaPlayer(QObject* parent = nullptr)

  构造函数，可选指定父对象。

- 禁用拷贝构造与赋值操作。

主要成员函数

- void setSource(const char* local_file)

  设置媒体源文件路径。

- QString source() const

  获取当前媒体源路径。

- void setVolume(float percentage)

  设置音量百分比。

- float volume() const

  获取当前音量百分比。

- qint64 get_durations() const

  获取媒体总时长（毫秒）。

- qint64 get_position() const

  获取当前播放位置（毫秒）。

- bool resume()

  继续播放，若媒体可显示且已准备好。

- bool pause()

  暂停播放。

- bool close()

  关闭媒体，强制释放资源。

- bool isPlaying() const

  查询是否正在播放（音频或视频任一在播放即返回真）。

- void set_accept_missync_msecond(unsigned int msec = 500)

  设置允许的音视频不同步最大毫秒数，默认为 500。

- void set_position(qint64 position)

  设置当前播放位置（毫秒）。

信号

- void display_frame(QImage image)

  当有新视频帧可显示时发出。

- void volumeChanged(float percentage)

  音量变化时发出。

- void sourceOpened(const QString source, MediaPlayerStatus status)

  媒体资源打开完成时发出，包含当前媒体状态。

- void videoAvailable(bool sourceAvailable, const QImage firstPage)

  视频流可用时发出，并提供第一帧图像。

- void mediaEnd()

  媒体播放结束时发出。

- void durationChanged(qint64 new_duration)

  媒体总时长变化时发出。

- void positionChanged(qint64 position)

  播放位置变化时发出。

- void metaDataAvailable(const MediaInfo info)

  媒体元数据可用时发出。

私有成员变量

- QMediaPlayer* audioPlayer

  用于音频播放的 Qt 媒体播放器对象。

- VideoPlayer* videoPlayer

  用于视频播放的自定义视频播放器对象。

- MediaPlayerStatus media_status

  当前媒体状态信息。

- unsigned int mis_sync_seconds

  允许的最大音视频不同步毫秒数。

- qint64 durations

  媒体总时长（毫秒）。

- qint64 position

  当前播放位置（毫秒）。

私有成员函数

- void init_allocations()

  初始化分配资源。

- void init_connections()

  初始化信号槽连接。

- void process_sync(const CVImage& current_frame)

  处理音视频同步，基于当前视频帧。

- void handle_sync_duration(qint64 durations)

  处理同步时长信息。

- void handle_sync_position(qint64 position)

  处理同步播放位置。

- void extract_metainfo()

  提取媒体元数据信息。