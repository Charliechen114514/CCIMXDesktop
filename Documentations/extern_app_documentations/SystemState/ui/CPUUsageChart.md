# **CPUUsageChart**  
**头文件**: `CPUUsageChart.h`  
**继承关系**: QWidget  
**简介**: 实时显示CPU使用率的折线图控件  

#### **公共槽函数**  
| 签名                                                     | 说明                |
| -------------------------------------------------------- | ------------------- |
| `flush_from_cpudriver(const CPUStateFetcher::CPUState&)` | 根据CPU状态更新图表 |

#### **关键特性**  
- 最大显示点数：30  
- 动态计算CPU使用率百分比  
- 包含X/Y轴坐标系统（`QValueAxis`）  

#### **私有数据结构**  
```cpp
struct {
    double last_tol;   // 上次总CPU时间
    double last_idle;  // 上次空闲时间
} cached_data;
```

