# 构建热插拔式 Qt 插件系统 —— 基于 QPluginLoader 的控件平台封装实践——详解Desktop中如何抽象PluginServer的

> Documentation: v1.0.0 Specified for Version v2.2.1，First Release in 2025/8/1
>
> Documenation belongs to Projects: [Charliechen114514/CCIMXDesktop: This is a Simple Desktop with Common Utilities for Embedded Device System using Qt6](https://github.com/Charliechen114514/CCIMXDesktop)

## 前言

​	不会有人不喜欢插件的，在这里，我们才能对我们的程序实现一定程度的热更新，实现我们用户期望这个系统表现的我们自己定义的功能。这就是插件的作用——**插件（plugins）** 是一种非常重要的设计模式。它允许我们动态地加载和卸载功能模块，而无需重新编译整个应用程序。Qt 框架提供了强大的插件机制，其中 **`QPluginLoader`** 是实现这一机制的核心类。

### 什么是 QPluginLoader？

​	QPluginLoader本质上封装了跨平台层次的DLL动态加载和调用，它能够以一种安全、跨平台的方式加载包含特定接口的共享库，并使应用程序能够调用这些插件中的功能。

1. **加载共享库：** `QPluginLoader` 能够从磁盘上加载一个 `.so` (Linux)、`.dll` (Windows) 或 `.dylib` (macOS) 文件。
2. **实例化插件：** 一旦加载了共享库，`QPluginLoader` 能够找到并实例化该库中特定的插件对象。
3. **提供接口：** 它提供了一种统一的方式来访问插件提供的功能，这些功能通常通过一个预定义的接口类来定义。
4. **管理生命周期：** `QPluginLoader` 负责管理插件的生命周期，包括加载、卸载以及在应用程序关闭时正确地清理资源。

### 如何使用QPluginLoader？

​	工程师们都比较关心这个如何使用，这里简单的说明一下流程。

1. 定义插件接口

首先，你需要定义一个**插件接口类（interface class）**。这个接口类是一个抽象基类，它定义了所有插件必须实现的纯虚函数。

```c++
// MyPluginInterface.h
#include <QObject>

class MyPluginInterface
{
public:
    virtual ~MyPluginInterface() = default;

    // 纯虚函数，所有插件必须实现
    virtual QString pluginName() const = 0;
    virtual void doSomething() = 0;
};

// 确保 QPluginLoader 能够识别此接口
// 注意，这里是MOC扫描，不要使用宏定义，他是无法展开的！你只能填写最纯正的字面量
Q_DECLARE_INTERFACE(MyPluginInterface, "com.yourcompany.MyPluginInterface/1.0")
```

**`Q_DECLARE_INTERFACE` 宏用于将接口与一个唯一的字符串标识符关联起来，`QPluginLoader` 将使用这个标识符来查找插件。**

#### 基于这个接口实现我们的插件

```
// MyPlugin.h
#include "MyPluginInterface.h"
#include <QObject>

class MyPlugin : public QObject, public MyPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.yourcompany.MyPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(MyPluginInterface)

public:
    // 实现接口中的纯虚函数
    QString pluginName() const override { return "My Awesome Plugin"; }
    void doSomething() override { /* 具体实现 */ }
};
```

- `Q_PLUGIN_METADATA` 宏告诉 Qt 这是一个插件，并指定其元数据文件（`plugin.json`）。`IID` 必须与接口中的标识符匹配。
- `Q_INTERFACES` 宏声明该类实现了 `MyPluginInterface` 接口。

#### 3. 使用 QPluginLoader 加载插件

```cpp
// main.cpp
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include "MyPluginInterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // 假设插件文件名为 myplugin.dll
    QString pluginPath = QDir::currentPath() + "/plugins/myplugin.dll";
    
    QPluginLoader loader(pluginPath);
    
    // 尝试加载插件
    if (loader.load()) {
        // 加载成功，获取插件实例
        QObject* pluginObject = loader.instance();
        if (pluginObject) {
            // 将 QObject 转换为插件接口类型
            MyPluginInterface* plugin = qobject_cast<MyPluginInterface*>(pluginObject);
            if (plugin) {
                // 调用插件功能
                qDebug() << "Loaded plugin:" << plugin->pluginName();
                plugin->doSomething();
            } else {
                qWarning("Could not cast plugin instance to MyPluginInterface.");
            }
        } else {
            qWarning("Could not get plugin instance.");
        }
        
        // 插件使用完毕后，可以卸载
        loader.unload();
    } else {
        qWarning("Failed to load plugin: %s", qPrintable(loader.errorString()));
    }

    return app.exec();
}
```

- `QPluginLoader::load()` 方法会尝试加载共享库并验证其是否包含有效的插件。
- `QPluginLoader::instance()` 返回一个 `QObject*` 类型的指针，它指向插件对象。
- `qobject_cast` 用于将 `QObject*` 安全地转换为我们需要的接口类型。
- `QPluginLoader::unload()` 方法用于卸载插件。

## 下面看看笔者在CardWidget上的封装

​	我们这里就来一个现场的例子，我们现在需要让HOME界面的卡片组自动扫描加载用户自己定义的应用程序安装和加载我们的插件。请看下面

```cpp
#pragma once
#include <QtPlugin>
class QWidget;

/**
 * @brief 插件接口类，所有插件应实现此接口
 */
struct DesktopPluginWidgetBase {
    virtual ~DesktopPluginWidgetBase() = default;

    /**
     * @brief 插件控件创建接口
     * @param parent 控件的父窗口
     * @return 插件控件指针
     */
    virtual QWidget* factorize_widget(QWidget* parent) = 0;
};

// 注册接口类型（供 Qt 元对象系统识别）
Q_DECLARE_INTERFACE(DesktopPluginWidgetBase,
                    "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0")

```

​	如你所见，这个就是我们的DesktopPluginWidgetBase，他只做一个事情，就是吐出来DLL内部针对DesktopPluginWidgetBase的子类重载的Widget是啥样的。

​	现在，我们需要做的就是将我们的DesktopPluginWidgetBase派生我们更加具体的类WeatherCard_Plugins

```cpp
// WeatherCard.h

#include "DesktopPluginWidgetBase.h"
#include <QObject>
#include <QWidget>
#include <QtPlugin>

class WeatherCard : public QWidget {
    Q_OBJECT
public:
    explicit WeatherCard(QWidget* parent = nullptr);
    ~WeatherCard();
};

// 插件工厂
class WeatherCard_Plugins : public QObject, public DesktopPluginWidgetBase {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0"
                      FILE "WeatherCard_plugin.json")
    Q_INTERFACES(DesktopPluginWidgetBase)

public:
    QWidget* factorize_widget(QWidget* parent = nullptr) override {
        return new WeatherCard(parent);
    }
};
```

​	你可以看到，这里我们就重写了我们的DesktopPluginWidgetBase，让他吐出来我们想要加载的QWidget。之后就是封装这一套流程退居后台，这就是DesktopWidgetPluginServer的由来

##  架构总览

```
+------------------------------+
| DesktopWidgetPluginServer   |      👈 插件管理总控器
|------------------------------|
| + 插件动态扫描 & 监控        |
| + 插件加载 / 卸载            |
| + 插件控件创建               |
| + 插件错误事件信号           |
+-------------+----------------+
              |
              v
        QPluginLoader
              |
              v
  +-----------------------------+
  | 插件接口 DesktopPluginWidgetBase |
  +-----------------------------+
              ^
              |
   +--------------------------+
   | 插件实现类 WeatherCard   |
   +--------------------------+
```

------

## 📎 一、插件接口定义

插件需实现如下接口，并返回一个 `QWidget*`：

```cpp
struct DesktopPluginWidgetBase {
    virtual ~DesktopPluginWidgetBase() = default;
    virtual QWidget* factorize_widget(QWidget* parentWidget) = 0;
};

Q_DECLARE_INTERFACE(DesktopPluginWidgetBase,
    "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0")
```

------

## 🔌 二、插件加载封装：`DesktopWidgetPluginServer`

### 🌟 功能亮点

- 📦 扫描目录自动加载插件
- 🔥 文件监控实现热插拔（通过 `FileMonitor`）
- 🧠 接口识别与类型安全转换（`qobject_cast`）
- ⚠️ 插件错误回调事件（信号通知 UI 层）
- 🧼 插件卸载自动释放资源

------

## 🧱 三、关键代码详解

### 1. 插件加载函数：`insertPlugin`

```cpp
void DesktopWidgetPluginServer::insertPlugin(const QString& pluginName, const QString& plugin_path);
```

- 校验插件是否已存在；
- 使用 `QPluginLoader` 加载 `.dll/.so` 文件；
- 调用 `loader->instance()` 获取 `QObject*`；
- 使用 `qobject_cast<DesktopPluginWidgetBase*>` 进行接口转换；
- 加入 `plugin_map` 管理。

### 2. 插件热更新：文件监控 `FileMonitor`

```cpp
connect(hot_loaded, &FileMonitor::newFiles, this, [&](...) {
    insertPlugin(...);
});
connect(hot_loaded, &FileMonitor::deletedFiles, this, [&](...) {
    unloadPlugin(...);
});
```

- `FileMonitor` 为你封装的一个目录监控器，监视插件新增/删除事件；
- 自动调用加载与卸载流程，真正实现“热插拔”。

### 3. 卸载插件：`unloadPlugin`

```cpp
bool DesktopWidgetPluginServer::unloadPlugin(const QString& plugin_name);
```

- 调用 `loader->unload()` 卸载动态库；
- 清理资源（调用 `deleteLater()` 延迟删除 Qt 对象）；
- 移除映射表中的记录。

### 4. 插件实例化控件：`queryWidget`

```cpp
QWidget* DesktopWidgetPluginServer::queryWidget(
    const QString& pluginName, QWidget* expected_parent);
```

- 基于插件名称定位到 `QPluginLoader`；
- 创建插件实例并转换为接口指针；
- 调用 `factorize_widget()` 返回控件并挂载。

------

## 🧪 四、使用示例

### 加载所有插件：

```cpp
DesktopWidgetPluginServer* server = new DesktopWidgetPluginServer("plugins/", this);
server->scanTargetDirent();  // 扫描 plugins 目录
```

### 添加插件控件到主界面：

```cpp
QWidget* pluginWidget = server->queryWidget("WeatherCard", this);
if (pluginWidget) {
    layout->addWidget(pluginWidget);
}
```

------

## 🧰 五、插件开发说明

每个插件需实现 `DesktopPluginWidgetBase` 接口并使用如下宏：

```cpp
class MyPlugin : public QObject, public DesktopPluginWidgetBase {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0"
                      FILE "my_plugin.json")
    Q_INTERFACES(DesktopPluginWidgetBase)

public:
    QWidget* factorize_widget(QWidget* parent) override {
        return new MyWidget(parent);
    }
};
```

### 插件元信息 JSON 示例：

```json
{
  "name": "Weather Plugin",
  "version": "1.0",
  "description": "A card displaying weather info"
}
```

------

## 🧼 六、清理与销毁流程

- 插件卸载调用 `QPluginLoader::unload()`，立即释放库内全局变量；
- 所有插件在析构函数 `~DesktopWidgetPluginServer()` 中集中销毁。

------

