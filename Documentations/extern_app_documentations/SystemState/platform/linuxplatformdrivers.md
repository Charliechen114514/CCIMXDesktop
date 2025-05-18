# **LinuxPlatformDrivers**  

**头文件**: `linuxplatformdrivers.h`  
**平台**: Linux  
**依赖**: 系统文件（如`/proc/meminfo`、`/proc/stat`等）  

#### **驱动实现类**  

| 类名                                | 继承关系                             | 核心功能                          |
| ----------------------------------- | ------------------------------------ | --------------------------------- |
| `LinuxPlatformMemoryInfoDriver`     | `CCIMX_AbstractMemoryInfoDriver`     | 解析`/proc/meminfo`获取内存数据   |
| `LinuxPlatformCPUStateDriver`       | `CCIMX_AbstractCPUStateDriver`       | 解析`/proc/stat`计算CPU使用率     |
| `LinuxPlatformProcessBrowserDriver` | `CCIMX_AbstractProcessBroswerDriver` | 遍历`/proc/[pid]`目录获取进程信息 |

**特殊说明**：  

- 需要`sudo`权限获取完整进程信息  
- CPU使用率计算需维护历史状态  
