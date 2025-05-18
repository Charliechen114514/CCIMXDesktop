# CVTools

提供图像调试辅助功能，主要用于图像的显示管理。

常量

- static constexpr const short WAIT_FOREVER

  定义等待时间常量，值为 0，表示无限等待。

结构体 DisplayParams

用于定义图像显示的参数。

成员变量

- const char* name

  显示窗口的名称，默认为空指针。

- std::pair<int, int> window_size

  窗口尺寸，默认值为宽 640 像素、高 480 像素。

- int waitTime

  等待时间，单位毫秒，默认值为 WAIT_FOREVER 表示无限等待。

函数

- void display(const CVImage& image, const char* name)

  使用默认显示参数显示传入的图像。参数 image 为待显示的 CVImage 对象，name 为窗口标题。

- void display(const CVImage& image, const DisplayParams& params)

  根据指定的显示参数显示图像。参数 image 为待显示的 CVImage 对象，params 包含显示相关设置。