# 🧩 Module Descriptions

![Modules](https://img.shields.io/badge/Modules-6%20Core%20Components-blueviolet)

Here is the module description for developers to refer to if you wish to modify the module for better portability to your embedded device.

## 🔧 `app_wrapper`

![Launcher](https://img.shields.io/badge/Component-System%20Launcher-important)

Application launcher and system bootloader. It initializes the Qt environment, sets global styles, and manages startup and shutdown order.

------

## 🧬 `builtin`

![Builtin](https://img.shields.io/badge/Category-Core%20Utilities-yellowgreen)

Contains core system tools and default utilities embedded in the desktop environment.

- `core/icm20608`
![Sensor](https://img.shields.io/badge/Driver-IMU%20Sensor-blue)
Driver and logic for the **ICM-20608 IMU sensor**, handling real-time data acquisition from the gyroscope and accelerometer, connected via an I2C interface. (Additional note: if you use a different chip, you should also modify and rewrite the internal functions)

- `gadgets`
![UI](https://img.shields.io/badge/Type-UI%20Widgets-9cf)
User-friendly widgets, such as clocks, CPU/network meters, or quick-start tiles for user interaction.

- `page`
![Navigation](https://img.shields.io/badge/Feature-Page%20Routing-ff69b4)
Logical page management for internal UI routing (e.g. switching between home page, app page, etc.).

- `sources/localweather`
![Weather](https://img.shields.io/badge/Data-Weather%20API-green)
Weather information provider for getting or simulating local weather data.

- `sources/netcard`
![Network](https://img.shields.io/badge/Service-Network%20Status-lightgrey)
Used to handle network card information, status display, and possibly provide IP/network diagnostics.

- `ui`
![Theme](https://img.shields.io/badge/Style-UI%20Components-important)
UI components specific to built-in modules, these files support the UI style of the desktop itself.

------

## ⚙️ `core`

![System](https://img.shields.io/badge/Layer-System%20Services-critical)

System-level services and shared base classes, such as global context management, signal buses, or singleton infrastructure. May contain system abstractions used across modules.

------

## 🚀 `extern_app`

![Extensible](https://img.shields.io/badge/Architecture-Pluggable%20Apps-success)

Third-party or user-extensible applications that are integrated into the desktop system, but modularized for easy addition/removal. You need to go to the corresponding document below to read the details. It should be noted that you only need to modify these sub-items in extern_app to run them independently with almost zero cost, and improve and refine them as your own project.

------

## 🧩 `sources`

![Resources](https://img.shields.io/badge/Assets-UI%20Resources-blue)

The Ui resources used by the desktop itself. If you need to replace them with your own resources, just replace them with the same name.

------

## 🎨 `ui`

![Theme](https://img.shields.io/badge/Design-Theme%20System-ff69b4)

Top-level UI template, theme or layout definition. Can be used as the basis for the entire desktop style or skin.
