class SendData{
public:
    SendData();
    ~SendData();
    void clear();
    void create();

public:
    unsigned long timerCnt;

public:
    static constexpr int BUFF_SIZE = 50;
    static constexpr int startByte = 0xBB;
    static constexpr int endByte   = 0x66;
    char buff[BUFF_SIZE];
};
