# 模块名称 LocalWeatherCard 与 LocalWeatherLightFetcher

## 功能概述

 LocalWeatherLightFetcher 是一个抽象接口，用于定制化获取本地天气信息的轻量级方式；LocalWeatherCard 则基于 AppCardWidget，为界面提供一个本地天气卡片组件，能够在预启动阶段调用天气信息获取器，并在卡片渲染后执行后处理工作。

## LocalWeatherLightFetcher 说明

 LocalWeatherLightFetcher 提供两个纯虚函数，fetch_local_tempature 用于返回本地温度值，其返回类型为浮点数；makeup_toast_message 用于生成用于 DesktopToast 弹出提示的天气信息文本，其返回类型为字符串。构造函数为默认构造，且通过 Q_DISABLE_COPY 禁止拷贝操作，以保证接口实现者不会无意中复制状态。

## LocalWeatherCard 说明

 LocalWeatherCard 继承自 AppCardWidget，并通过 explicit 构造函数要求传入一个 DesktopToast 对象以及可选的父 QWidget 指针，从而确保卡片能够在内部借助 DesktopToast 显示消息提示。类自身通过 Q_DISABLE_COPY 禁止拷贝，以维护内部状态一致性。卡片内部持有一个指向 LocalWeatherLightFetcher 的指针 localFetcher，默认为空。

## 构造函数与成员

 LocalWeatherCard 的构造函数接受两个参数：toast 用于向用户弹出信息，parent 为父级窗口指针。用户在创建卡片实例后，需要通过类内部机制为 localFetcher 赋值为具体的 LocalWeatherLightFetcher 实现，从而使 invoke_preLaunch_work 可以在卡片启动前调用天气获取逻辑，并在获取完温度后通过 DesktopToast 显示相应提示。

## 方法说明

 invoke_preLaunch_work 用于触发预启动工作，它会检查 localFetcher 是否已设置，若已设置则先调用 fetch_local_tempature 获取温度值，接着调用 makeup_toast_message 生成提示文本，最后通过传入的 DesktopToast 对象将提示信息展示给用户。postAppCardWidget 为受保护方法，用于卡片渲染完成后的后处理工作，可在子类中重载以实现定制化效果。

## 使用示例

 在程序初始化时，首先定义一个继承自 LocalWeatherLightFetcher 的类，重载 fetch_local_tempature 和 makeup_toast_message，并在构造 LocalWeatherCard 时通过指针成员 localFetcher 进行注入；然后调用 invoke_preLaunch_work 即可在卡片显示前弹出当前本地天气信息，完成卡片的动态数据填充与提示。