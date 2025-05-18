------

# `CameraDeviceSelector`

**文件位置：** `CameraDeviceSelector.h`

**基类：** 无

**职责概述：**
 提供静态方法，用于扫描和获取系统中可用摄像设备的信息，包括设备索引列表和设备名称列表。

------

#### 静态常量

```cpp
static constexpr const int MAX_CAMERA_SCAN = 5;
```

定义最大扫描摄像设备数量为5，防止扫描范围过大导致性能问题。

------

#### 构造函数

```cpp
CameraDeviceSelector() = default;
```

默认构造函数，实例化对象无特殊操作。

------

#### 静态公有方法

```cpp
static QList<int> scan_available_cameras(const int& start_index = 0);
```

扫描并返回从 `start_index` 开始的可用摄像头设备索引列表。默认从0开始扫描。

```cpp
static QList<QString> scan_available_camerasnames(const int& start_index = 0);
```

扫描并返回从 `start_index` 开始的可用摄像头设备名称列表。默认从0开始扫描。

------