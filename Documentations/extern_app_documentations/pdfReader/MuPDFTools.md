# MuPDF Tools

​	MuPDF Tools下的都是辅助MuPDF的操作接口类，这些类是那些想要深度优化和深度开发笔者demo的朋友需要关心和参考的。

## 类名：`CCPdfNavigationPolicy`

`CCPdfNavigationPolicy` 是一个策略类，用于处理 PDF 页面跳转过程中的异常情况。它不直接参与页面显示或渲染，但作为“跳转控制”的后备机制存在，当正常跳转操作失败时，它提供一种“补救跳转”的策略。

#### 一、设计目的

在实际的 PDF 阅读操作中，用户可能会跳转到一个不存在的页码，比如页数越界或当前文档未加载时。为了解决这类非正常情况，`CCPdfNavigationPolicy` 提供一个接口式的策略类，允许用户通过注册函数的方式来自定义这些跳转失败后的处理行为。

该策略不强制某种固定的跳转方式，而是通过回调机制，交由外部开发者决定当异常发生时如何响应。

#### 二、核心结构 Indicator

类中定义了一个 `Indicator` 结构体，用于描述页面跳转的目标页及是否必须遵循该跳转。

- `int new_page` 表示在发生异常时建议跳转到的页码，比如跳转越界时可能推荐跳到第一页或最后一页。
- `bool req_follow_indicator` 表示此建议是否为“必须执行”。如果为 `true`，说明系统应当强制按此页码跳转；如果为 `false`，系统可以选择无动作或保留原页。

这个结构类似于一个由策略函数返回的“导航提示器”。

#### 三、异常策略函数 PdfBrowseExceptionFunctor

这是一个函数指针类型，定义了页面跳转异常处理的标准格式。其参数说明如下：

- `QWidget* invoker` 表示谁触发了跳转操作，例如 PDF 浏览器窗口或工具栏控件。
- `CCPdfDocument* invokee_document` 表示当前绑定的文档对象，即目标跳转作用的载体。
- `const CCPdfDocument::PageNavigationError` 是错误类型，用于描述发生了哪种异常情况，如越界、无效页面等。

函数返回一个 `Indicator` 结构体，告诉系统下一步该如何响应此次失败的跳转。

#### 四、成员变量

- `PdfBrowseExceptionFunctor page_navigate_functor` 是该策略类的核心成员。它用于存储开发者自定义的异常处理函数。一旦跳转错误发生，系统就可以通过调用该函数得到相应的“补救建议”。

#### 五、使用方式建议

- 开发者可以在应用启动时或特定模块初始化时设置 `page_navigate_functor`，将其指向一个自定义函数，例如“跳转失败时默认回第一页”或“弹窗提示后停留原页”。
- 该策略类本身并不提供默认行为，因此需要在外部进行设置。
- 由于该类本身不依赖 QObject，也无信号槽，因此它可以轻量使用，不引入 Qt 对象模型的开销。

## mupdf tools.h工具箱

该头文件定义了一组围绕 PDF 文档的轻量级辅助工具，主要目的是为上层组件（如文档加载器、章节解析器、图像渲染器等）提供简单、明确的接口。这些接口大多基于 MuPDF 提供的底层功能，但被重新封装，以方便 Qt 程序使用和维护。

#### 一、结构体：`CCPdfMetaInfo`

这是一个用于表示 PDF 元信息的结构体，用于描述如作者、标题、主题、关键词、创建者等基本信息。

它内部使用了 Qt 的 Q_GADGET 宏，使得 `Field` 枚举可用于 Qt 元对象系统，例如用于 QML 或 QVariant 类型的处理。

字段包括作者（author）、标题（title）、主题（subject）、关键词（keywords）、创建者（creator）、生成器（producer）、创建时间和修改时间。每个字段对应 MuPDF 支持的元信息关键字，并用 QString 类型存储。

该结构体主要用于元信息批量获取，并且通常配合 `request_meta` 使用。

#### 二、结构体：`CCPdfImageRequest`

这个结构体定义了一次图像渲染请求，包含以下三个信息：

- `CCPdfDocument* request_document`：请求渲染的文档指针。
- `int request_page`：请求渲染的页码。
- `float zoom`：缩放倍率，用于控制图像清晰度和渲染大小。

它被用于 PDF 渲染请求，例如 `CCPdfViewer` 需要显示某一页时，构造此结构体作为参数传递给渲染函数。

#### 三、结构体：`CCPdfChapterNode`

该结构体用于表示 PDF 文档的目录章节树。它本身是递归结构，支持嵌套子章节（childs 字段），同时记录章节标题（chapter_title）与该章节指向的页码（chapter_page）。

这个结构体主要用于章节生成器模块，即 `CCPdfChapterCreator` 中，在章节解析完毕后，会发射携带 `QList<CCPdfChapterNode>` 的信号，用于填充章节树控件。

#### 四、命名空间：`ccpdf_tools`

该命名空间封装了几个通用工具函数，用于处理 MuPDF 提供的元数据、章节信息和页面图像等内容，避免外部直接依赖底层 C API。

具体包含以下函数：

1. `CCPdfMetaInfo request_meta(const CCPdfDocument* document);`
   该函数从指定文档中提取所有元信息，并返回一个包含全部字段的结构体。适合需要完整显示文档元数据的模块调用。
2. `QVariant request_target_meta(const CCPdfDocument* document, const CCPdfMetaInfo::Field field);`
   用于获取指定字段的元信息，返回类型为 QVariant，以兼容多种 Qt 类型系统。适合只关注某一项信息的调用场景。
3. `QImage request_target_page(CCPdfImageRequest* simpleRequest);`
   根据传入的 `CCPdfImageRequest` 渲染指定页码的图像，返回值为一张 `QImage`，该图像可以用于在界面中直接显示。是图像显示模块的关键接口之一。
4. `QList<CCPdfChapterNode> request_chapter_tree(const CCPdfDocument* document);`
   该函数从文档中提取出章节目录信息，并组织成一棵章节树结构。每个节点包含标题、页码和子章节。此函数为章节生成器使用的主要数据来源。