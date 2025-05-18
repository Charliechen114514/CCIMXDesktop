# **SystemStateWindow**  

**头文件**: `SystemStateWindow.h`  
**继承关系**: QMainWindow  
**简介**: 系统状态监控主窗口，集成CPU/内存/进程监控功能  

#### **公共枚举**  

```cpp
enum PageIndex {
    CPUUsage,        // CPU使用率页面
    MemoryInfo,      // 内存信息页面
    ProcessBrowser,  // 进程浏览页面
    PageIndexMax     // 页面索引上限
};
```

#### **公共成员函数**  

| 返回值类型 | 函数签名                                       | 说明             |
| ---------- | ---------------------------------------------- | ---------------- |
| `explicit` | `SystemStateWindow(QWidget* parent = nullptr)` | 构造函数         |
| `void`     | `switch_index(PageIndex index)`                | 切换当前显示页面 |

#### **私有成员**  

- `MemoryInfoFetcher* mem_fetcher`: 内存数据获取器  
- `CPUStateFetcher* cpu_fetcher`: CPU数据获取器  
- `ProcessBroswer* process_fetcher`: 进程数据获取器  
- `CPUUsageChart* cpuchart_widget`: CPU图表控件  

