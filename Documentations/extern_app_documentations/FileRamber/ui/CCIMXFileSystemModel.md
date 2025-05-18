# `CCIMXFileSystemModel`

**文件位置：** `CCIMXFileSystemModel.h`

**基类：** `QFileSystemModel`

**职责概述：**
 本类是对 Qt 自带的 `QFileSystemModel` 进行的扩展，允许绑定多个外部信息提供器（`FileInfoProvider`），以支持在文件系统模型中动态展示更多自定义数据列，如文件大小、类型、计数、颜色标记等。该类作为中心协调者，统一调度各个信息提供器参与 `data()` 与 `headerData()` 的展示逻辑，实现增强版的文件视图。

------

#### 构造函数

```
explicit CCIMXFileSystemModel(QObject* parent = nullptr);
```

构造函数用于初始化模型，并可指定其父对象。模型初始化时并不绑定任何信息提供器，需手动调用 `bindProviders()` 配置。

------

#### 公有成员函数

```
void bindProviders(QList<FileInfoProvider*>& providers);
```

用于绑定一组 `FileInfoProvider` 提供器，这些提供器将参与后续数据展示与逻辑计算。绑定后，`data()` 和 `headerData()` 方法将自动融合这些提供器的输出。

```
QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
```

重写 `QFileSystemModel` 的 `data()` 方法，提供了增强的数据访问支持。当列索引超出默认文件系统模型的范围时，尝试从已注册的 `FileInfoProvider` 中获取对应列的数据（例如显示文件大小、数量或颜色等）。

```
QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
```

重写表头数据接口，用于为自定义扩展列提供对应的标题文字。若 `section` 位于默认列之后，则交由每个 `FileInfoProvider` 的 `provide_section_name()` 方法返回对应的列标题。

```
cpp


复制编辑
const QList<FileInfoProvider*>& get_providers() const;
```

返回当前已绑定的所有信息提供器，用于外部系统检查或调试。

------

#### 私有成员变量

```
cpp


复制编辑
QList<FileInfoProvider*> providers;
```

存储所有绑定到当前模型的 `FileInfoProvider` 实例列表。这些提供器被视为扩展列的内容源，会依次调用其 `data()` 与 `provide_section_name()` 方法来获取对应内容。

------

#### 应用场景

此类特别适用于那些需要扩展默认文件信息视图的应用场合，例如文件浏览器、文件分类分析器、自定义资源管理器等。其设计配合 `FileInfoProvider` 的策略接口方式，可灵活组合任意信息逻辑，支持异步加载与缓存机制。