# Class CVImage

用于封装图像操作的类，底层通过指向 CVImageImpl 的指针实现实际图像数据和操作。支持图像文件加载和图像对象的赋值与复制。

构造与析构

- CVImage()

  默认构造函数，初始化空的图像对象。

- CVImage(const CVImage& image)

  拷贝构造函数，创建当前对象为另一个 CVImage 对象的副本。

- const CVImage& operator=(const CVImage& image)

  赋值操作符，将另一个 CVImage 对象的内容赋值给当前对象。

- ~CVImage()

  析构函数，释放内部资源。

公有成员函数

- void loadFile(const char* filename)

  从指定文件路径加载图像数据。参数 filename 为以 null 结尾的字符串路径。

- void assigned(const CVImage& image, bool load_as_copy = false)

  赋值图像数据。可以选择是浅拷贝还是深拷贝。参数 image 为源图像对象，load_as_copy 为 true 时执行深拷贝，false 时执行浅拷贝。

- bool image_valid() const

  返回当前图像是否有效。若内部图像数据存在且有效，返回 true，否则返回 false。

- CVImageImpl* impl_ptr() const

  获取内部实现指针，允许友元类直接访问底层图像实现。

私有成员变量

- CVImageImpl* private_handle

  指向内部图像实现对象的指针。