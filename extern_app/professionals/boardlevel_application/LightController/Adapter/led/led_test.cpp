#include "led_adapter.h"
#include <iostream>
#include <thread>
int main()
{
    /* test the base control of plain mode */
    LEDAdapter led("red-led");
    LEDParamsPackagePlain plain(true);
    led.setMode(LEDAdapter::Modes::Plain);
    bool res = led.processByPackage(&plain);
    std::cout << "LED set to plain mode with open: " << (res ? "Success" : "Failed") << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    plain.setIsOn(false);
    led.processByPackage(&plain);
    std::cout << "LED set to plain mode with close " << (res ? "Success" : "Failed") << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* test the base control of blink mode */
    LEDParamsPackageBlink blink(300, 300);
    led.setMode(LEDAdapter::Modes::Blink);
    led.processByPackage(&blink);
    std::cout << "LED set to blink mode with on time: " 
              << blink.getOnTime() << " off time: " << blink.getOffTime() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    led.setMode(LEDAdapter::Modes::Plain);
    led.processByPackage(&plain);
    std::cout << "LED set to plain mode, turn off with open: " << (res ? "Success" : "Failed") << std::endl;
    return 0;
}





