#include "AirConditionerController.hpp"
#include <sstream>

AirConditionerController::AirConditionerController()
{
    _id = 5; // Valor aleatório para o ID único do controlador
}

AirConditionerController::~AirConditionerController()
{
}

void AirConditionerController::Loop()
{
    StopAC();
    LedOff();
    _running = false;

    while (true)
    {
        Button btn = ReadButton();

        if (IsRoomClosed())
        {
            LedOff();

            if (!_running && (btn == Button::START))
            {
                LedBlink(1);
                Log("button");
                StartAC();
                _running = true;
            }

            else if (btn == Button::HOLD)
            {
                LedBlink(2);
                SendLog();
            }

            _room_closed = true;
        }
        else
        {
            if (_running || _room_closed)
            {
                LedOn();
                if (_running)
                {
                    Log("stop");
                }
                StopAC();
                _running = false;
                _room_closed = false;
            }
        }
    }
}

void AirConditionerController::Log(std::string str)
{
    log_t log{0};
    log.id = _id;
    std::string datetime_str = GetDateTimeStr();
    datetime_str.copy(log.datetime, datetime_str.size());
    str.copy(log.message, str.size());
    _logs.push(log);
}

void AirConditionerController::SendLog()
{
    while (!_logs.empty())
    {
        log_t log = _logs.pop();

        if (IsBluetoothConnected())
        {
            SendBluetooth(static_cast<void *>(&log), sizeof(log));
        }
        else
        {
            SendSerial(static_cast<void *>(&log), sizeof(log));
        }
    }
}