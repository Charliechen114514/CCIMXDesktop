# **StackpageSwitcherAnimation**  

**头文件**: `stackpage_switcher_animation.h`  
**继承关系**: QObject  
**简介**: 为QStackedWidget提供页面切换动画效果  

#### **核心方法**  

```cpp
static void process_animations(
    QStackedWidget* binding_widget,  // 绑定的堆叠控件
    AnimationInfo* animation_info    // 动画参数
);
```

#### **动画参数结构**  

```cpp
struct AnimationInfo {
    int new_index;          // 目标页面索引
    bool toLeft;            // 是否向左切换
    int animation_duration; // 动画时长（默认400ms）
};
```

