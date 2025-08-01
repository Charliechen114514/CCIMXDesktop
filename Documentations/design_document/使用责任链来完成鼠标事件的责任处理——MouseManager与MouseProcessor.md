# Qt6 使用责任链来完成鼠标事件的责任处理 —— `MouseManager` 与 `MouseProcessor`

## 前言

​	这个部分是笔者设计的，用于提供一定优先级办法的鼠标事件处理的文档，主要介绍在library文件夹下的鼠标设计处理的文档。

​	大家都是看过很多Demo的人，都可以注意到，很多人写的MousePressEvent和MouseReleaseEvent简直是惨不忍睹，大长串的一片，搞得代码乱七八糟，非常不好维护，笔者的代码利用一定的设计后，化简成了这样：

```cpp
void DesktopMainWindow::mousePressEvent(QMouseEvent* event) {
    mouseManager->install_mousepoint(
        event->pos(),
        MouseManager::PointType::Press);
    event->accept();
}

void DesktopMainWindow::mouseReleaseEvent(QMouseEvent* event) {
    mouseManager->install_mousepoint(
        event->pos(),
        MouseManager::PointType::Release);

    if (!mouseManager->run_processor()) {
        event->ignore();
        return;
    }
    qDebug() << "Ok, handled!";
    event->accept();
}
```

​	其他处理器的部分依次由模块提供进行注册，可以说是非常的方便了。

```cpp
             MouseProcessor* updown_processor = new MouseProcessor(
                 [mainWindow](MouseRecorder* recorder) -> bool {
                              const QPoint diff = recorder->press - recorder->release;
                              return qAbs(diff.y()) >= mainWindow->tool_settings_bar_slide_limitive; },
                 [mainWindow](MouseRecorder* recorder) -> bool {
                                const QPoint diff = recorder->press - recorder->release;
                                if(diff.y() < 0){
                                    mainWindow->fastSettingsWidget->slideDown();
                                }else{
                                    mainWindow->fastSettingsWidget->slideUp();
                                }
                              return true; });
             updown_processor->setName("ToolSettingsProcessor");
             mainWindow->mouseManager->register_processor(updown_processor);
```

​	我们的目的很简单：我们知道在 GUI 应用程序中，鼠标事件的处理往往涉及多种组件与行为逻辑。传统事件分发机制（如事件过滤器）在复杂业务中容易导致耦合度高、可测试性差、可扩展性不足等问题。为了解耦事件处理逻辑、增强处理策略的可配置性与可插拔性，我们很自然的想到设计模式中的“责任链”模式，来帮助我们处理这个事情。

## 什么是责任链模式（Chain of Responsibility）？

责任链模式是一种**行为型设计模式**，其主要目的是：**使多个对象都有机会处理请求，从而避免请求的发送者与接收者之间的耦合关系。**这些对象被连成一条链，请求沿着链传递，直到某个对象处理它为止。本质上，它是一种将**请求处理与具体处理逻辑解耦**的设计策略。

​	我们先来看我们的MouseManager，MouseManager收集可靠的鼠标信息后，将我们的鼠标信息转发到我们的处理链上，如下图所示👇

```
+------------------+
|   MouseManager   |
+------------------+
         |
         v
+------------------+       +------------------+       +------------------+
|  MouseProcessor  | ----> |  MouseProcessor  | ----> |  MouseProcessor  |
+------------------+       +------------------+       +------------------+
       ^                           ^                            ^
       | tryProcess()              |                            |
       | directProcess()           |                            |
       | setNext() / next()        |                            |
```

​	你可以看到，在这个处理链条上，我们能抓出来三个角色，这里列一张表：

| 模式角色                      | 当前实现中的类                      | 说明                                                         |
| ----------------------------- | ----------------------------------- | ------------------------------------------------------------ |
| Handler（抽象处理者）         | `MouseProcessor`                    | 定义处理请求的接口（try_and_process）和设置下一个处理者的方法（setNext） |
| ConcreteHandler（具体处理者） | 继承/实例化的 `MouseProcessor` 对象 | 实现具体的 try + process 逻辑                                |
| Client（请求发起者）          | `MouseManager`                      | 构建处理链并发起处理请求                                     |

​	你突然发现，这个时候，我们的逻辑就没有写死了，我们可以动态的注册我们的模块接口，他不关心是从哪里来的数据，只需要把数据接受进来，发现是自己可以处理的，就进行处理，希望截至处理的，就返回处理完毕的信号，反之，就返回false表达这个事件还需要继续被其他Processor进行处理。这样的话：

- **解耦发送者与处理者**：`MouseManager` 不需要知道哪个处理器能处理请求，职责完全委托给链；
- **提高可扩展性**：增加或修改处理器不影响其他逻辑，只需按需插入链条；
- **运行时灵活配置**：处理器链可以在运行时动态调整顺序或启用状态；
- **天然支持优先级**：链条顺序即优先级，先注册的处理器优先尝试处理。

#### 典型处理流程（序列图）

```
MouseManager      ProcessorA     ProcessorB     ProcessorC
     |                 |              |              |
     | run_processor() |              |              |
     |---------------->|              |              |
     | try_and_process |              |              |
     |   tryProcess?   |              |              |
     |     false       |              |              |
     |-----------------------------> try_and_process |
                       |              tryProcess?    |
                       |                true         |
                       |            directProcess?   |
                       |               true          |
                       |           <-- handled OK ---|
     |<---------------------------------------------|
```

## 核心类结构说明

### 1. MouseProcessor —— 事件处理器节点

每一个 `MouseProcessor` 表示一个独立的鼠标事件处理节点，它拥有两个策略：

- `tryProcess(recorder)`：判断是否有资格处理该事件；
- `directProcess(recorder)`：执行实际处理逻辑。

若当前节点未启用、或 `tryProcess` 不满足条件、或 `directProcess` 执行失败，则会尝试交由下一个处理节点继续尝试，体现出典型的责任链传播模式。

```cpp
bool MouseProcessor::try_and_process(MouseRecorder* recorder) {
    if (!enabled) {
        return next_one ? next_one->try_and_process(recorder) : false;
    }

    if (tryProcess(recorder)) {
        if (directProcess(recorder)) {
            qInfo() << processor_name << ": handle OK!";
            return true;
        } else {
            qInfo() << processor_name << ": processing failed, pass to next!";
            return next_one ? next_one->try_and_process(recorder) : false;
        }
    } else {
        qInfo() << processor_name << ": tryProcess failed, pass to next!";
        return next_one ? next_one->try_and_process(recorder) : false;
    }
}
```

该类的职责是抽象一个处理能力单位，通过链式结构组织成完整的处理流程。处理器链的顺序由注册时决定，内部维护 `next_one` 指针指向下一个处理器。

### 2. MouseManager —— 管理器与入口

`MouseManager` 负责管理整个责任链，它负责：

- 注册处理器（`register_processor`）并构建链结构；
- 接收与记录鼠标事件的关键点位（`install_mousepoint`）；
- 触发链处理入口（`run_processor`）。

```cpp
bool MouseManager::run_processor() {
    if (!head_processor) {
        qCritical() << "No processor is registered, manager do nothing!";
        return false;
    }

    bool isHandled = head_processor->try_and_process(recorder.get());
    if (!isHandled) {
        qCritical() << "Current Chain failed to process the events!";
    } else {
        qDebug() << "Ok, event is processed!";
    }

    return isHandled;
}
```

该类本身并不处理具体的鼠标事件逻辑，而是以管理者的身份，组织、传递并控制处理链的执行。

------

## 数据结构辅助：MouseRecorder

`MouseRecorder` 是辅助结构，用于记录当前一次鼠标事件的 Press/Release 两个点位，是各处理器共享的上下文数据结构，支持：

```cpp
recorder->press
recorder->release
```

处理器根据这些点位判断自身是否有能力处理该事件。