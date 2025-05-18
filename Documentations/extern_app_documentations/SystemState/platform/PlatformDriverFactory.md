# **PlatformDriverFactory**  

**头文件**: `PlatformDriverFactory.h`  
**模式**: 工厂模式（静态工厂）  

#### **工厂方法**  

| 方法签名                        | 返回类型                              | 说明                       |
| ------------------------------- | ------------------------------------- | -------------------------- |
| `meminfo_from_platform()`       | `CCIMX_AbstractMemoryInfoDriver*`     | 创建当前平台的内存驱动实例 |
| `cpustate_from_platform()`      | `CCIMX_AbstractCPUStateDriver*`       | 创建当前平台的CPU驱动实例  |
| `processdriver_from_platform()` | `CCIMX_AbstractProcessBroswerDriver*` | 创建当前平台的进程驱动实例 |

**实现逻辑伪代码**：  

```cpp
#ifdef Q_OS_WIN
    return new Win32PlatformXXXDriver();
#elif defined(Q_OS_LINUX)
    return new LinuxPlatformXXXDriver();
#endif
```

