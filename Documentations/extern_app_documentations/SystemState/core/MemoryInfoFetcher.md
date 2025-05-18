# **MemoryInfoFetcher**  

**头文件**: `MemoryInfoFetcher.h`  
**继承关系**: QObject  
**简介**: 获取物理和虚拟内存使用信息的工具类  

#### **公共成员函数**  

| 返回值类型       | 函数签名                                       | 说明                                     |
| ---------------- | ---------------------------------------------- | ---------------------------------------- |
| `static QString` | `format_size(quint64 size)`                    | 将字节数格式化为易读字符串（如"1.2 GB"） |
| `explicit`       | `MemoryInfoFetcher(QObject* parent = nullptr)` | 构造函数                                 |
| `void`           | `set_flush_freq(const int msecs)`              | 设置内存信息刷新频率（毫秒）             |
| `void`           | `set_capture_state(bool st)`                   | 启用/禁用内存监控                        |

#### **数据结构**  

```cpp
struct MemoryStat {
    quint64 total_phys_memory;  // 物理内存总量（字节）
    quint64 avail_phys_memory;  // 可用物理内存（字节）
    quint64 total_virt_memory;  // 虚拟内存总量（字节）
    quint64 avail_virt_memory;  // 可用虚拟内存（字节）
};
```

#### **信号**  

| 签名                                      | 说明                     |
| ----------------------------------------- | ------------------------ |
| `finish_detect_memory(const MemoryStat&)` | 当内存信息刷新完成时触发 |

#### **其他说明**  

- 禁用拷贝构造（`Q_DISABLE_COPY`）  
- 默认刷新间隔：1500毫秒  

---

### **公共特性**  

1. **平台驱动架构**：  
   所有类均采用`CCIMX_Abstract*Driver`抽象基类实现跨平台支持，具体平台需实现`factory()`方法  
2. **刷新机制**：  
   - 均使用`QTimer`定时刷新  
   - 默认刷新频率均为1500毫秒  
   - 提供`set_flush_freq()`动态调整频率  

3. **线程安全**：  
   未明确标注线程安全性，建议在UI线程使用（因涉及信号槽通信）


