# **Win32PlatformDrivers**  
**头文件**: `Win32PlatformDrivers.h`  
**平台**: Windows  
**依赖**: Windows API (`windows.h`)  

#### **驱动实现类**  
| 类名                                | 继承关系                             | 核心功能                                   |
| ----------------------------------- | ------------------------------------ | ------------------------------------------ |
| `Win32PlatformMemoryInfoDriver`     | `CCIMX_AbstractMemoryInfoDriver`     | 通过Windows API获取物理/虚拟内存信息       |
| `Win32PlatformCPUStateDriver`       | `CCIMX_AbstractCPUStateDriver`       | 使用`PDH`或`GetSystemTimes`获取CPU状态     |
| `Win32PlatformProcessBroswerDriver` | `CCIMX_AbstractProcessBroswerDriver` | 通过`CreateToolhelp32Snapshot`枚举进程信息 |

**共同特性**：  
- 禁用拷贝构造（`Q_DISABLE_COPY`）  
- 必须实现`factory()`纯虚函数  
