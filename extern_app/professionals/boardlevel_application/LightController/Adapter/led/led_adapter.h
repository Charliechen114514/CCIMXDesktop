/*
    This is a led adapter, which is using in 
    drive the led in upper level way
*/
#ifndef LED_ADAPTER
#define LED_ADAPTER
#include <string>

class LEDParamsPackage
{
public:
    virtual ~LEDParamsPackage() = default;
};

class LEDParamsPackageBlink : public LEDParamsPackage
{
public:
    static constexpr int DEFAULT_ON_TIME = 500;
    static constexpr int DEFAULT_OFF_TIME = 500;
    LEDParamsPackageBlink(int onTime, int offTime):
        onTime(onTime),
        offTime(offTime){}
    int getOnTime() const{return onTime;}
    int getOffTime() const{return offTime;}
    void setOnTime(int time){onTime = time;}
    void setOffTime(int time){offTime = time;}
private:
    int onTime {DEFAULT_ON_TIME};
    int offTime {DEFAULT_OFF_TIME};
};

class LEDParamsPackagePlain : public LEDParamsPackage
{
public:
    LEDParamsPackagePlain(bool isOn):
        isOn(isOn){}
    bool getIsOn() const{return isOn;}
    void setIsOn(bool isOn){this->isOn = isOn;}
private:
    bool isOn{false};
};



class LEDAdapter
{
public:
    enum class Modes{
        Blink,  /* Trighger mode */
        Plain,  /* Normal Control */
        Disabled /* disabled, this state the led is unavailable */
    };
    explicit LEDAdapter(const std::string& ledName);
    ~LEDAdapter() = default;
    /* this means switching to other led */
    void redirectTo(const std::string& ledName);
    /* led written path */
    std::string ledPath() const{return led_path;}
    /* modes are set to define how to control packages */
    inline void setMode(const Modes mode){this->mode = mode;}
    /* get the current mode */
    inline Modes getMode() const{return this->mode;}
    /* bind the package with required parameters */
    bool processByPackage(const LEDParamsPackage* package);

private:
    std::string led_path;
    Modes mode{Modes::Disabled};
    /* make the real write */
    bool write_file(const std::string& fileName, const std::string& content);
};

#endif









