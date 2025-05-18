------

# `PhotoSaver`

**文件位置：** `PhotoSaver.h`

**基类：** 无

**职责概述：**
 `PhotoSaver` 类为工具类，提供图像（`QPixmap`）保存功能，包含路径可写检测与单次保存方法。适用于图像快照、截图保存等场景。

------

#### 枚举类型

```cpp
enum class Error {
	SaveSuccess,
	NullImage,
	DirUnsavable,
	ImageSelfSaveFailed
};
```

定义图像保存时可能发生的状态或错误类型：

- `SaveSuccess`：保存成功；
- `NullImage`：传入图像为空；
- `DirUnsavable`：指定目录不可写或不存在；
- `ImageSelfSaveFailed`：调用 QPixmap 自身保存函数失败。

------

#### 构造函数

```cpp
PhotoSaver() = default;
```

默认构造函数。由于该类所有方法均为静态，构造对象一般无实际用途。

------

#### 静态公有函数

```cpp
static bool dirSavable(const QString& dir);
```

检查指定目录 `dir` 是否存在且可写。返回值为 `true` 表示目录合法且具备写入权限，`false` 表示不可保存。

```cpp
static Error saveOnce(const QPixmap& image, const QString& dir, const QString prefix = ".jpg");
```

尝试将 `image` 图像保存至 `dir` 目录中。文件名使用当前时间戳作为前缀，并附加指定后缀（默认为 `.jpg`）。返回 `Error` 类型值以指示保存结果。

------