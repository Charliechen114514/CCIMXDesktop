------

# `CCMediaPlayList`

**文件位置：** `CCMediaPlayList.h`

**基类：** `QObject`

------

#### 结构体

- `MediaListMails`
   结构体包含播放列表状态信息：是否允许前一项和后一项，以及当前播放媒体名称。

------

#### 枚举

- `enum class PlayMode`
   播放模式，包含以下值：
  - `OneShot`：单曲播放一次。
  - `OneCycle`：单曲循环播放。
  - `ListPlay`：列表播放，播放完停止。
  - `ListCycle`：列表循环播放。
- `enum Direction`
   播放方向：
  - `FORWARD`：向前。
  - `BACKWARD`：向后。

------

#### 构造函数

```cpp
explicit CCMediaPlayList(QObject* parent = nullptr);
```

------

#### 常量

- `static constexpr const PlayMode DEF_MODE = PlayMode::ListCycle;`
   默认播放模式为列表循环。

------

#### 公有成员函数

- `void set_play_mode(const PlayMode mode);`
   设置播放模式。
- `void flow_mode();`
   切换播放模式。
- `PlayMode get_play_mode() const;`
   获取当前播放模式。
- `MediaListMails fetch_prev_play();`
   获取上一项播放信息。
- `MediaListMails fetch_next_play();`
   获取下一项播放信息。
- `MediaListMails fetch_current_play();`
   获取当前播放项信息。
- `MediaListMails fetch_from_name(const QString& where);`
   根据媒体名获取播放信息。
- `MediaListMails fetch_first_play();`
   获取第一项播放信息。
- `MediaListMails fetch_last_play();`
   获取最后一项播放信息。
- `QStringList currentPlayingList() const;`
   返回当前实际播放列表。
- `QStringList actualList() const;`
   返回原始播放列表。
- `int get_actualListlist_size();`
   返回原始播放列表大小。
- `void enqueue_play(const QStringList& media_sources);`
   向播放队列添加媒体。
- `void remove_play_list(const QStringList& media_sources);`
   从播放列表移除媒体。

------

#### 信号

- `void playModeChanged(const PlayMode mode);`
   播放模式改变信号。

------

#### 公有槽函数

- `void flush_play_list();`
   刷新播放列表，将播放列表内容同步到实际播放列表。

------

#### 私有成员变量

- `PlayMode current_mode { DEF_MODE };`
   当前播放模式。
- `QStringList play_list {};`
   原始播放列表。
- `QStringList actual_play_list {};`
   实际播放列表，刷新后使用。
- `int moving_index { -1 };`
   当前播放索引。

------

#### 私有成员函数

- `void flush_info_according_mode(Direction dir);`
   根据播放方向刷新播放信息。
- `MediaListMails flush_according_index();`
   根据当前索引刷新播放信息。

------