# **ProcessBroswer**  

**头文件**: `ProcessBroswer.h`  
**继承关系**: QObject  
**简介**: 用于浏览和监控系统进程信息的类，提供进程列表刷新功能  

#### **公共成员函数**  

| 返回值类型 | 函数签名                                    | 说明                         |
| ---------- | ------------------------------------------- | ---------------------------- |
| `explicit` | `ProcessBroswer(QObject* parent = nullptr)` | 构造函数，可选父对象         |
| `void`     | `set_flush_freq(const int msecs)`           | 设置进程列表刷新频率（毫秒） |
| `void`     | `set_capture_state(bool st)`                | 启用/禁用进程信息捕获        |

#### **数据结构**  

```cpp
struct ProcessInfo {
    int pid;            // 进程ID
    int ppid;           // 父进程ID
    QString name;       // 进程名称
    QString fullPath;   // 进程完整路径
    int threadCount;    // 线程数
    qint64 memoryUsageKB; // 内存占用（KB）
    double cpuPercent;  // CPU占用百分比
    QString userName;   // 所属用户
};
```

#### **信号**  

| 签名                                            | 说明                                           |
| ----------------------------------------------- | ---------------------------------------------- |
| `fetch_finish(const QList<ProcessInfo>& infos)` | 当进程列表刷新完成时触发，返回当前进程信息列表 |

#### **私有成员**  

- `CCIMX_AbstractProcessBroswerDriver* platform_driver_base`: 平台相关的驱动接口  
- `flush_once()`: 执行单次进程列表刷新  
- 默认刷新间隔：1500毫秒  

