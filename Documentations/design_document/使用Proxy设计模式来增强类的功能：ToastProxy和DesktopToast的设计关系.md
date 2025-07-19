# 使用代理模式来增强类的功能：ToastProxy和DesktopToast

> Documentation: v1.0.0 Specified for Version v1.12.0，First Release in 2025/7/12
>
> Documenation belongs to Projects: [Charliechen114514/CCIMXDesktop: This is a Simple Desktop with Common Utilities for Embedded Device System using Qt6](https://github.com/Charliechen114514/CCIMXDesktop)

## 前言

​	这个算设计模式的部分，笔者当时正在设计的是如何让我的Desktop支持扩展的从Protocol Json Buffer转换到我的Toast可以识别的Meta Info的问题。这也是笔者写下这篇设计文档的原因——设计文档鸽了一个月（之前一直认为这个项目还没有成型的框架，因此迟迟没有动笔）

## 关于Proxy设计模式

​	笔者很早就学习过设计模式，至少接触过一部分，Proxy，英语好的朋友知道，这是代理的意思。代理大伙都知道代理人，替本人出任做工作的代理人。这里我们说的代理，就是提供一个新的类代理旧的类，当然，如果是完全做一样的事情，我们没必要请出Proxy，对吧。那么，Proxy显然要比原先的类多做一部分工作，在笔者看来，Proxy设计模式是对原对象一次无痛（什么是无痛的？指的是不会改动原有类的任何功能，通过和其他类的协作达到增强原有类可以做的事情）扩展。

​	现在说说笔者遇到的问题，看过笔者DesktopToast源码的朋友就知道，DesktopToast是一个简单的通知栏滑动类，实际上，我们最关心也是他最本职的功能是这个：

```cpp
class DesktopToast : public QWidget {
    Q_OBJECT
public:
	/**
	 * @brief Construct a new Desktop Toast object
	 * 
	 * @param parent 
	 */
	explicit DesktopToast(QWidget* parent = nullptr);
	/**
	 * @brief set_message push the toast display into the
	 * toast display sessions
	 * @param message
	 * @note this will make a queue like display.
	 * so, if the toast is currently animating, it will not display the new
	 * messages immediately, but wait until the current message is finished
	 */
	void set_message(const QString& message);
	... // 下面的工作是私有成员，set message就是告诉我们的 toast显示什么东西，很简单吧！
```

​	非常好，但是现在呢，笔者正在抽象一个服务类，简单的讲，就是监听一个特定的文件夹下的json文件解析满足ToastMetaProtocol要求格式的json文件，一旦监听到新的文件，我们就做解析转换，发送信号交给一个类处理并且做显示，由于我们使用的是Qt，他是按照信号的方式进行传递的，笔者经过权衡考虑，认为设计一个类来作为代表，比堆一大堆函数的串行调用要靠谱（真不敢想后者的可扩展性。。。）

​	经过笔者的一番折腾，现在我们的Server类非常的干净

``` cpp
/**
 * @brief The ToastPostServer class
 * This is a server of toast infomation level
 */
class ToastPostServer : public DesktopServerBase {
    Q_OBJECT
public:
    ToastPostServer(DesktopToast* toast, const QString& monitoring_path, QObject* parent);

private:
	// 这里就是放Toast嘛？显然不行！
    ToastReceiver* receiver;
};
```

​	其中Receiver类也很简单，他将监听到的新的Json file转化成我规定的ToastMetaProtocol对象，在一次信号发射中携带ToastMetaProtocol对象走出去，但是现在问题来了，我们的DesktopToast本身不支持ToastMetaProtocol，而且他是特定于我们桌面系统的一个类，如果我强行修改了DesktopToast类，我之后就没法在其他地方复用了，这咋办呢？我也不想继承，因为我不想对其他冗余的接口占用（虽然也是办法，但是实际上后面我还会增强关于Toast本身的调用，我还要修改一大堆代码防止客户调用父类的Partial的功能乱改一通）。归根揭底，是因为我们在这里是要求DesktopToast类按照一定的顺序和其他相关的类进行协作，本质上不算DesktopProxy对象的工作，我们不能强行算在DesktopToast头上。

​	这就是下面这个类的功能了：

```cpp
#ifndef TOASTPROXY_H
#define TOASTPROXY_H
#include "core/server/toast_file_gen_and_receiver/ToastMetaProtocol.h"
class DesktopToast;
class ToastProxy : public QObject {
public:
    ToastProxy() = delete;
    explicit ToastProxy(DesktopToast* toast, QObject* parent);
public slots:
    void process_toastMeta(const ToastMetaProtocol& protocolMeta);

private:
    DesktopToast* toast;
};

#endif // TOASTPROXY_H
```

​	ToastProxy作为代理对象，增强（延展）了我们的DesktopToast的功能

- 接收上层组件（如 ToastReceiver）传来的 `ToastMetaProtocol` 对象；
- 解析并转化为 `DesktopToast` 可处理的格式；
- 向 `DesktopToast` 发起消息展示；
- 为未来可能新增的中间处理（如日志、过滤、限流等）提供扩展点。

​	这里的一个具体的增强就体现在process_toastMeta，一方面我们的对象可以接受其他对象对我们DesktopToast的通知，而不是直接沟通增加强耦合，而是去隔一层ToastProxy的转化功能发给DesktopToast可以听懂的功能，这样的话，任何的扩展的协作的功能，都可以直接在ToastProxy上加，丝毫不会影响两侧使用这个类做事情和被要求做的事情的类的任何一点行为。这就是代理模式在这里的一次使用。

​	现在有了这个类，我们的调用链看起来就像：

```
ToastPostServer
    |
    v
ToastReceiver  --- (signal: protocolMetaReady) -->  ToastProxy  --- (call) --> DesktopToast
```