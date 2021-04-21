#if !defined(AIRCONDITIONERCONTROLLER_H)
#define AIRCONDITIONERCONTROLLER_H

#include <string>
#include "Queue.hpp"

class AirConditionerController
{
public:
    typedef enum
    {
        START,
        HOLD,
        NONE
    } Button;

    typedef struct
    {
        uint8_t id;
        char datetime[20];
        char message[20];
    } log_t;

    AirConditionerController();
    ~AirConditionerController();

    void Loop();

protected:
    virtual Button ReadButton() = 0;
    virtual void StartAC() = 0;
    virtual void StopAC() = 0;
    virtual void LedOn() = 0;
    virtual void LedOff() = 0;
    virtual void LedBlink(int times) = 0;
    virtual void SendSerial(void *data, size_t size) = 0;
    virtual void SendBluetooth(void *data, size_t size) = 0;
    virtual std::string GetDateTimeStr() = 0;
    virtual uint Millis() = 0;
    virtual void DelayMs(uint) = 0;
    virtual bool IsRoomClosed() = 0;
    virtual bool IsBluetoothConnected() = 0;

private:
    uint8_t _id;
    bool _running;
    bool _room_closed;

    Queue<log_t> _logs;

    void Log(std::string);
    void SendLog();
};

#endif // AIRCONDITIONERCONTROLLER_H
