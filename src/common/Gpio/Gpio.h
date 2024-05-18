#ifndef INCLUDED_GPIO
#define INCLUDED_GPIO

#include <string>

class Gpio
{
private:
    static constexpr char* UDEV  = const_cast<char*>("/dev/serial0");

public:
    Gpio();
    ~Gpio();

    int init();
    void chModeOutput(int pinNo);
    void chModeInput(int pinNo);
    void setHigh(int pinNo);
    void setLow(int pinNo);

    int openSerialDevice(int baudRate);
    int serialRead(char *bytes, int readSize);
    int serialRead1Byte(char &data);
    void serialWrite(char *bytes, int size);

private:
    bool isDevelop;
    int serialHandle;
};

#endif
