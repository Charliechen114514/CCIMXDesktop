## ✅ 如何开发一个运行在CCIMXDesktop HOME CARD插件

桌面系统支持**动态插件机制**，你可以通过继承 `DesktopPluginWidgetBase` 接口，开发你自己的可视化 Card 插件，并部署到指定目录即可自动加载显示。

------

### 🔧 步骤一：实现插件类

你需要继承提供的接口类 `DesktopPluginWidgetBase`，并实现其纯虚函数。

#### 示例代码：

```cpp
// MyCoolCardPlugin.h
#pragma once
#include "plugin_loader/plugin_base/DesktopPluginWidgetBase.h"
#include <QObject>

class MyCoolCardPlugin : public QObject, public DesktopPluginWidgetBase {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.desktop.Plugin.CoolCard")
    Q_INTERFACES(DesktopPluginWidgetBase)

public:
    QWidget* factorize_widget(QWidget* parent = nullptr) override;
};
// MyCoolCardPlugin.cpp
#include "MyCoolCardPlugin.h"
#include <QLabel>
#include <QVBoxLayout>

QWidget* MyCoolCardPlugin::factorize_widget(QWidget* parent) {
    QWidget* card = new QWidget(parent);
    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->addWidget(new QLabel("✨ Hello from MyCoolCard!", card));
    card->setLayout(layout);
    return card;
}
```

------

### 📁 步骤二：构建为 Qt 插件动态库（.dll / .so / .dylib）

#### 示例:以WeatherCard这个Widget为例子，请参考内建的WeatherCard作为一个项目模板（CMake）：

```cmake
include(../../cmake/plugin_helper.cmake)

add_qt_plugin_with_json(WeatherCard WeatherCard "1.0"
        SOURCES
        ./WeatherCard.h
        ./WeatherCard.cpp
        ./WeatherCard.ui
        ./WeatherRequestEngine.h
        ./WeatherRequestEngine.cpp
        ./WeatherData.h
        ./QueryCached.h
        ./QueryCached.cpp
        ./DesktopPluginWidgetBase.h
)

...其他的部分
```

------

### 📦 步骤三：部署插件

将生成的插件库文件放置到运行目录下的插件目录：

```
${DesktopRoot}/Runtimeplugins/
```

桌面系统会**自动监控该文件夹**，一旦检测到新的插件库文件（扩展名 `.dll` / `.so` / `.dylib`），将：

1. 动态加载插件；
2. 通过 `QPluginLoader` 提取 `DesktopPluginWidgetBase` 实例；
3. 调用 `factorize_widget()` 创建对应的可视控件；
4. 自动挂载到桌面或插件容器上。

------

### ⚠️ 注意事项

- 插件必须使用 `Q_PLUGIN_METADATA` 宏指定唯一的 `IID`。
- 插件库名称推荐与类名一致，避免重名冲突。
- 插件需确保继承并正确实现 `DesktopPluginWidgetBase` 接口。
- 插件运行时依赖 Qt 环境，请确认路径正确或使用 rpath / windeployqt 等方式解决依赖。

------

### ✅ 示例插件结构参考

```bash
MyCoolCardPlugin/
├── CMakeLists.txt
├── MyCoolCardPlugin.h
├── MyCoolCardPlugin.cpp
└── build/
    └── MyCoolCardPlugin.dll  # 将此文件拷贝到 桌面的根文件夹/Runtime/plugins/
```

## ✅ How to Develop a Home Card Plugin for CCIMXDesktop

The desktop system supports a dynamic plugin mechanism. By inheriting the `DesktopPluginWidgetBase` interface, you can develop your own visual card plugin and deploy it to a specified directory for automatic loading and display.

------

### 🔧 Step 1: Implement the Plugin Class

You need to inherit the provided interface class `DesktopPluginWidgetBase` and implement its pure virtual functions.

#### Sample code:

```cpp
// MyCoolCardPlugin.h
#pragma once
#include "plugin_loader/plugin_base/DesktopPluginWidgetBase.h"
#include <QObject>

class MyCoolCardPlugin : public QObject, public DesktopPluginWidgetBase { 
Q_OBJECT 
Q_PLUGIN_METADATA(IID "org.desktop.Plugin.CoolCard") 
Q_INTERFACES(DesktopPluginWidgetBase)

public: 
QWidget* factorize_widget(QWidget* parent = nullptr) override;
};
// MyCoolCardPlugin.cpp
#include "MyCoolCardPlugin.h"
#include <QLabel>
#include <QVBoxLayout>

QWidget* MyCoolCardPlugin::factorize_widget(QWidget* parent) {
QWidget* card = new QWidget(parent);
QVBoxLayout* layout = new QVBoxLayout(card);
layout->addWidget(new QLabel("✨ Hello from MyCoolCard!", card));
card->setLayout(layout);
return card;
}
```

------

### 📁 Step 2: Build as a Qt plugin dynamic library (.dll / .so / .dylib)

#### Example: Using the WeatherCard widget as an example, please refer to the built-in WeatherCard project template (CMake):

```cmake
include(../../cmake/plugin_helper.cmake)

add_qt_plugin_with_json(WeatherCard WeatherCard "1.0"
SOURCES
./WeatherCard.h
./WeatherCard.cpp
./WeatherCard.ui
./WeatherRequestEngine.h
./WeatherRequestEngine.cpp
./WeatherData.h
./QueryCached.h
./QueryCached.cpp
./DesktopPluginWidgetBase.h
)

...Other Sections
```

------

### 📦 Step 3: Deploy the Plugin

Place the generated plugin library file in the plugin directory under the runtime directory:

```
${DesktopRoot}/Runtimeplugins/
```

The desktop system automatically monitors this folder. Upon detecting a new plugin library file (with the extension .dll / .so / .dylib ), it will:

1. Dynamically load the plugin;

2. Extract the DesktopPluginWidgetBase file using QPluginLoader . Example;
3. Call `factorize_widget()` to create the corresponding visual control;
4. Automatically mount it to the desktop or plugin container.

------

### ⚠️ Notes

- Plugins must use the `Q_PLUGIN_METADATA` macro to specify a unique `IID`.
- It is recommended that the plugin library name be consistent with the class name to avoid name conflicts.
- Plugins must ensure that they inherit and correctly implement the `DesktopPluginWidgetBase` interface.
- Plugins rely on the Qt environment at runtime. Please ensure the path is correct or use methods such as `rpath` or `windeployqt` to resolve dependencies.

------

### ✅ Sample plugin structure reference

```bash
MyCoolCardPlugin/
├── CMakeLists.txt
├── MyCoolCardPlugin.h
├── MyCoolCardPlugin.cpp
└── build/
└── MyCoolCardPlugin.dll # Copy this file to the desktop root folder/Runtime/plugins/
```
