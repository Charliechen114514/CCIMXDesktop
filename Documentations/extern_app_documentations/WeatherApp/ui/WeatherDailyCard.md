# **WeatherDailyCard**

**头文件**: `WeatherDailyCard.h`  
**继承关系**: QWidget  
**功能**: 单日天气信息展示卡片  

#### **核心方法**

| 方法                | 参数                                    | 说明                         |
| ------------------- | --------------------------------------- | ---------------------------- |
| `bind_daily_info`   | `const AppWeatherResult::DailyWeather&` | 绑定每日天气数据并更新UI     |
| `iconPolicy` (私有) | `const QString&`                        | 根据天气现象文本设置对应图标 |

#### **UI特性**

- 自动解析`DailyWeather`结构体中的日期、温度、风力等字段
- 支持白天/夜间天气图标动态切换

**使用示例**:

```cpp
AppWeatherResult::DailyWeather data;
// ...填充数据...
auto card = new WeatherDailyCard;
card->bind_daily_info(data);
```
