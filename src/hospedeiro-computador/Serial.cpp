// C library headers
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#include "../List.hpp"

typedef struct
{
    uint8_t id;
    char datetime[20];
    char message[20];
} log_t;

ostream &operator<<(ostream &os, const log_t &log)
{
    os << "id: " << unsigned(log.id) << ", datetime:" << log.datetime << ", message:" << log.message;
    return os;
}

int main()
{
    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    int serial_port = open("/dev/ttyACM0", O_RDWR);

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    tty.c_cflag &= ~PARENB;        // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB;        // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE;         // Clear all bits that set the data size
    tty.c_cflag |= CS8;            // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;       // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;                                                        // Disable echo
    tty.c_lflag &= ~ECHOE;                                                       // Disable erasure
    tty.c_lflag &= ~ECHONL;                                                      // Disable new-line echo
    tty.c_lflag &= ~ISIG;                                                        // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    List<log_t> list;

    while (true)
    {
        cout << "\n\n\n"
             << endl;
        cout << "Escolha uma opção e digite o número correspondente:" << endl;
        cout << "1 - Ler dados do dispositivo" << endl;
        cout << "2 - Listar todos os dados" << endl;

        char choice = '0';
        cin >> choice;

        if (choice == '1')
        {
            cout << "Lendo dados (execute o envio dos dados no dispositivo)" << endl;
            bool reading_values = true;
            bool value_read = false;
            while (reading_values)
            {
                log_t log = {0};
                int num_bytes = read(serial_port, static_cast<void *>(&log), sizeof(log));

                if (num_bytes < 0)
                {
                    printf("Error reading: %s", strerror(errno));
                    return 1;
                }
                else if (num_bytes > 0)
                {
                    list.insertAfterLast(log);
                    value_read = true;
                }
                else if (num_bytes == 0 && value_read == true)
                {
                    reading_values = false;
                    cout << "Dados adicionados" << endl;
                }
                usleep(100000);
            }
        }
        else if (choice == '2')
        {
            cout << "Listando todos os valores armazenados:" << endl;
            list.listAll();
        }
    }

    close(serial_port);
    return 0;
}
