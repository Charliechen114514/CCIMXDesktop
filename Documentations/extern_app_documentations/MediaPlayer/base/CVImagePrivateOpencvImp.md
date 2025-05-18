# CVImageOpencvImpl

继承自 CVImageImpl，基于 OpenCV 实现的图像处理具体类。

成员变量

- cv::Mat raw_image

  存储图像数据的 OpenCV 矩阵对象。

成员函数

- void load_from_file(const char* filename) override

  从指定文件加载图像数据，重写自基类接口。

- void assigned(const CVImageImpl* impl, bool req_copy) override

  根据另一个实现对象赋值图像数据，支持是否深拷贝，重写自基类接口。

- void pass_copy(const CVImageImpl* copied) override

  接收一个已复制的图像实现对象，重写自基类接口。

- bool image_valid() override

  判断当前图像数据是否有效（非空），重写自基类接口。