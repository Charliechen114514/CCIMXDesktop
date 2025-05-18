# **CPUStateFetcher**  

**头文件**: `CPUStateFetcher.h`  
**继承关系**: QObject  
**简介**: 实时获取CPU使用状态的类  

#### **公共成员函数**  

| 返回值类型 | 函数签名                                     | 说明                 |
| ---------- | -------------------------------------------- | -------------------- |
| `explicit` | `CPUStateFetcher(QObject* parent = nullptr)` | 构造函数             |
| `void`     | `set_capture_state(bool st)`                 | 启用/禁用CPU状态捕获 |

#### **数据结构**  

```cpp
struct CPUState {
    double idle;    // 空闲比例
    double user;    // 用户态使用比例
    double kernel;  // 内核态使用比例
    double tol;     // 总使用比例
};
```

#### **信号**  

| 签名                                    | 说明                                 |
| --------------------------------------- | ------------------------------------ |
| `flush_cpustate(const CPUState& state)` | 当CPU状态刷新时触发，返回当前CPU状态 |

#### **私有成员**  

- `CCIMX_AbstractCPUStateDriver* platform_driver_base`: 平台相关的驱动接口  
- 默认刷新间隔：1500毫秒  

