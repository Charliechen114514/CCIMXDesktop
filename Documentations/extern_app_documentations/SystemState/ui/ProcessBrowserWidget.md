# **ProcessBrowserWidget**  

**头文件**: `ProcessBrowserWidget.h`  
**继承关系**: QWidget  
**简介**: 进程列表展示控件  

#### **公共槽函数**  

| 签名                                               | 说明             |
| -------------------------------------------------- | ---------------- |
| `handle_process_issues(const QList<ProcessInfo>&)` | 处理进程数据更新 |

#### **UI特性**  

- 固定8列显示（`COL_CNT = 8`）  
- 自动响应`fetch_finish`信号  
