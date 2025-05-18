# **WeatherRequest 基类体系**
**架构图**：
```
WeatherRequest (抽象请求基类)
└── AppWeatherRequest (具体实现)

WeatherResult (抽象结果基类)
└── AppWeatherResult (具体实现)
```

---

## **WeatherRequest (抽象基类)**
**头文件**: `MyWeatherRequest.h`  
**继承关系**: QObject  
**职责**: 封装网络请求基础逻辑

#### **核心成员函数**
| 类型     | 声明                                       | 说明                                                    |
| -------- | ------------------------------------------ | ------------------------------------------------------- |
| 纯虚函数 | `virtual QUrlQuery compose_request() = 0`  | 子类必须实现的请求参数组装方法                          |
| 公有方法 | `void async_request(const char* base_url)` | 发起异步网络请求（自动调用`compose_request()`生成参数） |

#### **信号**
| 信号                          | 触发条件                       |
| ----------------------------- | ------------------------------ |
| `errorOccurs(QNetworkReply*)` | 网络请求失败时                 |
| `result_available(QString)`   | 收到有效响应时（原始JSON数据） |

#### **关键成员**
- `QNetworkAccessManager manager`：执行实际网络请求
- `static const char* private_key`：API密钥（编译期定义）

---

## **AppWeatherRequest (具体实现)**
**头文件**: `AppWeatherRequest.h`  
**继承关系**: WeatherRequest  
**功能**: 实现多日天气预报请求

#### **请求参数结构体**
```cpp
struct AppWeatherDetailedRequest {
    unsigned short start;  // 起始天数偏移（0=今天）
    unsigned short days;   // 请求天数（最大7）
    QString city;          // 城市名称/编码
};
```

#### **公有方法**
| 方法                                                         | 说明                                    |
| ------------------------------------------------------------ | --------------------------------------- |
| `void bindAppDetailedRequest(const AppWeatherDetailedRequest&)` | 绑定请求参数                            |
| `QUrlQuery compose_request() override`                       | 生成包含城市、天数等参数的URL查询字符串 |

#### **特性**
- 禁用拷贝构造（`Q_DISABLE_COPY`）
- 内置参数缓存机制（`request`成员）

---

### **WeatherResult (抽象基类)**
**头文件**: `MyWeatherRequest.h`  
**继承关系**: QObject  
**职责**: 定义天气数据解析接口

#### **纯虚函数**
```cpp
virtual void parseJsonString(const QString json) = 0;
```

#### **信号**
| 信号                    | 说明                   |
| ----------------------- | ---------------------- |
| `finish_parse()`        | 数据解析完成           |
| `error_occurs(QString)` | 解析错误时携带错误信息 |

---

### **AppWeatherResult (具体实现)**
**头文件**: `AppWeatherRequest.h`  
**功能**: 解析多日天气预报数据

#### **天气数据结构体**
```cpp
struct DailyWeather {
    QString date;           // 日期（yyyy-MM-dd）
    QString textDay;        // 白天天气现象（如"晴"）
    QString textNight;      // 夜间天气现象
    QString high;           // 最高温度（带单位）
    QString low;            // 最低温度（带单位）
    QString windDirection;  // 风向（如"东北风"）
    QString windScale;      // 风力等级（如"3-4级"）
    QString humidity;       // 湿度百分比
};
```

#### **公有方法**
| 方法                         | 说明                                  |
| ---------------------------- | ------------------------------------- |
| `parseJsonString() override` | 解析JSON数据并填充`daily_weather`列表 |
| `debugPrint() const`         | 调试用控制台打印数据                  |

#### **数据成员**
- `QList<DailyWeather> daily_weather`：解析后的天气数据列表
- `QString cached_city`：当前缓存的城市名称

---

### **典型使用流程**
```cpp
// 1. 创建请求对象
auto request = new AppWeatherRequest;
AppWeatherDetailedRequest params{0, 3, "北京"};
request->bindAppDetailedRequest(params);

// 2. 创建结果处理器
auto result = new AppWeatherResult;
QObject::connect(request, &AppWeatherRequest::result_available, 
                 result, &AppWeatherResult::parseJsonString);

// 3. 发起请求
request->async_request("https://api.weather.com/v3/forecast");
```

## **设计要点**
1. **分离关注点**：请求构造（`WeatherRequest`）与数据解析（`WeatherResult`）解耦
2. **扩展性**：可通过继承实现其他天气API的适配
3. **线程安全**：基于Qt信号槽的跨线程通信机制
