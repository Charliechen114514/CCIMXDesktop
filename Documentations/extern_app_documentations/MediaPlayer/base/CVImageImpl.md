# Class CVImageImpl

定义图像实现的抽象接口类，提供纯虚函数以供派生类实现具体图像处理逻辑。

纯虚函数

- void load_from_file(const char* filename)

  从指定文件路径加载图像数据。参数 filename 为 C 风格字符串路径。

- void assigned(const CVImageImpl* impl, bool req_copy)

  赋值操作，基于另一个实现对象进行数据赋值。参数 impl 为源对象指针，req_copy 指示是否进行深拷贝。

- void pass_copy(const CVImageImpl* copied)

  传递复制的实现对象，用于内部复制管理。

- bool image_valid()

  检查当前实现中的图像数据是否有效，返回布尔值。

- virtual ~CVImageImpl()

  虚析构函数，确保派生类资源正确释放。

Class CVImageImplFactory

用于创建 CVImageImpl 的具体实现实例的工厂类。

静态函数

- static CVImageImpl* target_impl()

  创建并返回具体的 CVImageImpl 派生类实例指针，已正确分配具体实现。