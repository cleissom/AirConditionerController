#if !defined(AIRCONDITIONERCONTROLLERRASPPICO_H)
#define AIRCONDITIONERCONTROLLERRASPPICO_H

#include "AirConditionerController.hpp"

class AirConditionerControllerRaspPico : public AirConditionerController
{
private:
    const uint AC_PIN = 10;
    const uint LED_PIN = 11;

    const uint START_BUTTON_PIN = 6;
    const uint DOOR1_PIN = 7;
    const uint WINDOW1_PIN = 8;

protected:
    Button ReadButton();
    void StartAC();
    void StopAC();
    void LedOn();
    void LedOff();
    void LedBlink(int times);
    void SendSerial(void *data, size_t size);
    void SendBluetooth(void *data, size_t size);
    std::string GetDateTimeStr();
    uint Millis();
    void DelayMs(uint);
    bool IsRoomClosed();
    bool IsBluetoothConnected();

public:
    AirConditionerControllerRaspPico(/* args */);
    ~AirConditionerControllerRaspPico();
};

#endif // AIRCONDITIONERCONTROLLERRASPPICO_H
