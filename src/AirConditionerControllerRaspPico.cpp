#include "AirConditionerControllerRaspPico.hpp"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/rtc.h"
#include "hardware/uart.h"
#include "pico/util/datetime.h"

AirConditionerControllerRaspPico::AirConditionerControllerRaspPico()
{
    // Inicialização dos Pinos
    stdio_init_all();

    gpio_init(AC_PIN);
    gpio_set_dir(AC_PIN, GPIO_OUT);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(START_BUTTON_PIN);
    gpio_set_dir(START_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(START_BUTTON_PIN);

    gpio_init(DOOR1_PIN);
    gpio_set_dir(DOOR1_PIN, GPIO_IN);
    gpio_pull_up(DOOR1_PIN);

    gpio_init(WINDOW1_PIN);
    gpio_set_dir(WINDOW1_PIN, GPIO_IN);
    gpio_pull_up(WINDOW1_PIN);

    // Inicialização da UART
    uart_init(uart0, 9600);
    gpio_set_function(0, GPIO_FUNC_UART); // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(1, GPIO_FUNC_UART);

    // Inicialização do RTC
    // Start on Friday 5th of June 2020 15:45:00
    datetime_t t = {
        .year = 2020,
        .month = 06,
        .day = 05,
        .dotw = 5, // 0 is Sunday, so 5 is Friday
        .hour = 15,
        .min = 45,
        .sec = 00};

    rtc_init();
    rtc_set_datetime(&t);

    // Inicialização do Bluetooth
    // (A ser implementado)
}

AirConditionerControllerRaspPico::~AirConditionerControllerRaspPico()
{
}

AirConditionerControllerRaspPico::Button AirConditionerControllerRaspPico::ReadButton()
{
    sleep_ms(100);

    if (!gpio_get(START_BUTTON_PIN))
    {
        auto start_millis = Millis();
        while (!gpio_get(START_BUTTON_PIN))
        {
            sleep_ms(100);
        }

        if (Millis() - start_millis > 2000)
        {
            return AirConditionerControllerRaspPico::Button::HOLD;
        }
        else
        {
            return AirConditionerControllerRaspPico::Button::START;
        }
    }

    else
    {

        return AirConditionerControllerRaspPico::Button::NONE;
    }
}

void AirConditionerControllerRaspPico::StartAC()
{
    gpio_put(AC_PIN, 1);
}

void AirConditionerControllerRaspPico::StopAC()
{
    gpio_put(AC_PIN, 0);
}

void AirConditionerControllerRaspPico::LedOn()
{
    gpio_put(LED_PIN, 1);
}

void AirConditionerControllerRaspPico::LedOff()
{
    gpio_put(LED_PIN, 0);
}

void AirConditionerControllerRaspPico::LedBlink(int times)
{
    for (auto i = 0; i < times; i++)
    {
        gpio_put(LED_PIN, 1);
        DelayMs(100);
        gpio_put(LED_PIN, 0);
        DelayMs(200);
    }
}

void AirConditionerControllerRaspPico::SendSerial(void *data, size_t size)
{
    uart_write_blocking(uart0, static_cast<uint8_t *>(data), size);
}

void AirConditionerControllerRaspPico::SendBluetooth(void *data, size_t size)
{
    // Enviar dados por bluetooth para um smartphone
}

std::string AirConditionerControllerRaspPico::GetDateTimeStr()
{
    datetime_t t = {0};
    rtc_get_datetime(&t);

    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];

    snprintf(datetime_str,
             sizeof(datetime_buf),
             "%d/%02d/%02d-%02d:%02d:%02d",
             t.year,
             t.month,
             t.day,
             t.hour,
             t.min,
             t.sec);

    return std::string(datetime_str);
}

uint AirConditionerControllerRaspPico::Millis()
{
    return static_cast<uint>(to_ms_since_boot(get_absolute_time()));
}

void AirConditionerControllerRaspPico::DelayMs(uint time)
{
    sleep_ms(time);
}

bool AirConditionerControllerRaspPico::IsRoomClosed()
{
    // sensor retorna '0' quando a porta/janela estiver aberta
    return gpio_get(DOOR1_PIN) && gpio_get(WINDOW1_PIN);
}

bool AirConditionerControllerRaspPico::IsBluetoothConnected()
{
    // Verifica se há algum dispositivo Bluetooth conectado
    return false;
}
