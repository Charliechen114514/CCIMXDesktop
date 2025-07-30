# CCIMXDesktop日志系统设计——如何给自己的Qt项目设计一个高可扩展的日志系统

## 前言

​	下面这部分的内容是笔者打算介绍的一个简单的问题：就是如何自己接管Qt的日志系统，做自己的一个支持 **热插拔、可扩展、多后端输出** 的日志系统。。因此这里决定简单的介绍一下设计抽象。

## Qt自己的接口

​	我们自己写项目的时候都是自己直接qDebug到终端上去的，没啥意思，看日志的时候有时候我们希望收集到现场的崩溃日志，从而将这个日志保存下来看看发生了什么。但是默认的Qt是做不到这一点的。

​	Qt给我们留了后手：

```
qInstallMessageHandler
```

​	我们需要传递一个接受的指针，他：

```cpp
typedef void (*QtMessageHandler)(QtMsgType, const QMessageLogContext &, const QString &);
```

​	这个指针就是整个项目中，我们用到了qDebug等一系列的日志信息，都会流转到整个QtMessageHandler中进行处理，因此，我们更多的是结合对QtMessageHandler的处理。

​	下面，就是我们的核心类：

## `CCIMXDesktopLoggerCenter` 

`CCIMXDesktopLoggerCenter` 是整个日志系统的**核心管理类**，主要职责是集中管理所有日志后端（`DesktopLoggerBackends`），通过 Qt 的 `qInstallMessageHandler` 截获全局日志，并将日志消息分发给注册的后端。

​	这个核心类是使用了C++11的静态局部变量保证线程安全的懒汉式初始化，我们使用单例的时候，使用 `global_instance()` 静态函数来返回全局唯一实例。（构造函数私有化，防止外部实例化，配合 `Q_DISABLE_COPY_MOVE` 禁止复制与移动。）

```cpp
static CCIMXDesktopLoggerCenter instance;
return instance;
```

------

## 多发射的基础：后端抽象`DesktopLoggerBackends`

​	`DesktopLoggerBackends`是日志系统中所有日志后端实现的 **抽象基类**，它定义了日志处理的核心流程：**消息格式化** + **消息消费**，并提供了动态热插拔的机制。

​	后端类继续真正的完成我们的日志函数：

```
DesktopLoggerBackends::LogStatus DesktopLoggerBackends::processMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    if (!enabled)
        return LogDisabled;

    return message_consume_backend->consume_message(
               format_factory->formativeFactory(type, context, msg))
        ? LogSuccess
        : LogFailed;
}
```

- 通过 `processMessage()` 方法，将日志消息交由 `FormativeFactory` 格式化，再传递给 `LoggerBaseConsumer` 消费。
- 返回值为 `LogStatus` 枚举（`LogSuccess`、`LogDisabled`、`LogFailed`），用于表示日志是否处理成功。

​	我们同样还支持运行时的热插拔后端：

- 提供 `hot_install_factory()` 和 `hot_install_consumer()` 方法，支持在 **运行时替换日志格式化器和消费者**，不需要重启应用。

- 使用 `__PROPERTY_GETSET(bool, enabled)` 宏生成 `enabled` 属性，快速控制日志后端是否参与日志输出。

------

## **核心接口**

### **1. 构造函数**

```cpp
DesktopLoggerBackends(std::shared_ptr<FormativeFactory> factory,
                      std::shared_ptr<LoggerBaseConsumer> consumer);
```

- 通过 **依赖注入**（DI）传入格式化器与消费者，解耦不同策略。

### **2. processMessage()**

```cpp
virtual LogStatus processMessage(QtMsgType type,
                                 const QMessageLogContext& context,
                                 const QString& msg);
```

- 日志处理的核心函数：
  - 如果 `enabled` 为 `false`，直接返回 `LogDisabled`。
  - 否则调用 `format_factory->formativeFactory(...)` 格式化日志，再交给 `message_consume_backend->consume_message()` 处理。

### **3. postSelfStatus()**

```cpp
virtual bool postSelfStatus() = 0;
```

- **纯虚函数**，用于由派生类（例如 `ConsoleLogger`）实现后端的自检逻辑。

### **4. 热插拔接口**

- `hot_install_factory(std::shared_ptr<FormativeFactory> factory)`
  - 线程安全替换日志格式化策略。
- `hot_install_consumer(std::shared_ptr<LoggerBaseConsumer> consumer)`
  - 线程安全替换日志消费策略。

## Center中如何处理后端基类的？

- **注册与移除后端**
  - `registerBackend(DesktopLoggerBackends* backend)`
    - 检查后端有效性并调用其 `postSelfStatus()` 确认可用后加入 `backends`。
  - `removeBackend(DesktopLoggerBackends* backend)`
    - 从容器中删除指定后端。
- **获取后端快照**
  - `backend_shots()`：返回当前所有后端的 `std::shared_ptr` 列表，方便外部操作或查看状态。

------

### **3. 启用/禁用控制**

- `availableTargetBackendOnly(DesktopLoggerBackends* backend)`
  - 仅指定后端保持启用状态，其余禁用。
- `availableBackends()`
  - 启用所有已注册的后端。
- `disableTargetBackends(DesktopLoggerBackends* backend)`
  - 禁用指定后端以外的所有后端。
- `silentBackends()`
  - 禁用所有后端（完全静默）。

------

### **4. 与 Qt 日志系统集成**

- **`globalMessageHandler`**
  - 通过 `qInstallMessageHandler()` 注册为 Qt 全局日志回调。
  - 每次 Qt 调用 `qDebug()`, `qWarning()`, `qCritical()` 等时，都会进入该函数。
  - 内部流程：
    1. 如果 `broadcast_to_old` 为 `true`，先调用旧的 Qt 日志处理器 `old_handler`。
    2. 遍历所有已注册且启用的 `DesktopLoggerBackends`，调用其 `processMessage()` 进行日志分发。

------

### **5. 线程安全**

- 使用 `std::shared_ptr<QMutex>` 作为互斥锁，确保 `backends` 列表的增删和访问是线程安全的。
- `QMutexLocker locker(mutex.get())` 自动加锁/解锁，RAII 风格避免死锁。

## 两个更加底层的完成类：

### LoggerBaseConsumer：真正将日志信息写入的类

`LoggerBaseConsumer` 是日志系统中**日志消息最终输出的抽象接口**，负责定义“日志消费”的统一行为。它是 `DesktopLoggerBackends` 的组成部分之一，所有的日志后端都必须实现该接口，用于将格式化后的日志数据发送到实际目标（控制台、文件、网络等）。

- **日志消费接口**：提供 `consume_message()` 纯虚函数，派生类必须实现如何将日志写入到目标位置。
- **错误报告接口**：提供 `errorString()`，用于返回消费过程中的错误信息。

------

## **主要接口解析**

### **1. `consume_message(const QString&& message)`**

```cpp
virtual bool consume_message(const QString&& message) = 0;
```

- 负责接收格式化后的日志字符串并执行实际的输出操作（如写入文件、控制台输出、发送到远程服务器等）。
- 返回值 `bool` 表示写入是否成功。

------

### **2. `errorString() const`**

```cpp
virtual QString errorString() const = 0;
```

- 返回上一次 `consume_message()` 的错误描述（若有）。
- 适用于日志写入失败时提供调试信息，例如文件权限错误、磁盘已满等。

------

## **典型实现**

- **ConsoleConsumer**
  - 将日志直接写入标准输出（`stdout`）。

`FormativeFactory` 是日志系统中的 **日志格式化策略接口**，其职责是**将原始日志消息（type + context + msg）转换成最终的字符串格式**，然后交给 `LoggerBaseConsumer` 进行输出。

------

## **核心职责**

- **格式化日志消息**
  - 将日志级别、时间戳、代码位置（文件、行号、函数）以及消息本身组合成可读性强的日志字符串。
- **可扩展格式策略**
  - 不同日志风格（如简洁模式、标准模式、带颜色模式）可以通过实现不同的 `FormativeFactory` 派生类实现。

------

## **接口说明**

### **1. `formativeFactory()`**

```cpp
virtual QString formativeFactory(QtMsgType type, 
                                 const QMessageLogContext& context, 
                                 const QString& msg) = 0;
```

- **输入参数**：
  - `type`：日志类型（`QtDebugMsg`、`QtWarningMsg`、`QtCriticalMsg`、`QtInfoMsg`、`QtFatalMsg`）。
  - `context`：包含日志产生位置的上下文（文件名、行号、函数）。
  - `msg`：原始日志字符串。
- **返回值**：
  - 返回格式化后的 `QString`。
- **实现方式**：不同的子类实现各自的日志格式规则，例如：
  - `PlainFormarter`：直接返回 `msg`。
  - `StandardFormater`：返回 `[2025-07-25 10:00:00] [Info] main.cpp:123 main() Message text`。
  - `ConsoleColorDecorator`：在格式化文本前后添加 ANSI 颜色码。

------

## **典型实现**

1. **PlainFormarter**

   ```cpp
   QString PlainFormarter::formativeFactory(QtMsgType, const QMessageLogContext&, const QString& msg) {
       return msg;
   }
   ```

2. **StandardFormater**
    在 `StandardFormater` 中，会根据 `options_` 选择是否显示时间戳、文件名、函数名：

   ```cpp
   QString StandardFormater::formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
       QStringList parts;
       parts << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
       parts << from_type(type);
       parts << QString("%1:%2 %3()").arg(context.file).arg(context.line).arg(context.function);
       parts << msg;
       return QString("[%1]").arg(parts.join("] ["));
   }
   ```

3. **ConsoleColorDecorator**

   - 通过组合已有的 `FormativeFactory` 对象，并在返回值前后插入 ANSI 颜色码，从而实现 **装饰器模式**。