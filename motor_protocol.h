#ifndef MOTOR_PROTOCOL_H
#define MOTOR_PROTOCOL_H
#include <QComboBox>
#include <QLineEdit>
#include <QMap>
#include <QDebug>
#include <QObject>
enum motor_cmd {

    //basic_cmd
    M_STOP 			= 0x0001,
    M_RUN_RPM 		= 0x0002,
    M_RUN_POS 		= 0x0003,
    M_STARTUP		= 0x0004,
    M_SYS_RESET		= 0x000F,

    //pid of current loop
    PID_CUR_KP 		= 0x1000,
    PID_CUR_KPDIV 	= 0x1001,
    PID_CUR_KI 		= 0x1002,
    PID_CUR_KIDIV 	= 0x1003,

    //pid of speed loop
    PID_SPD_KP 		= 0x2000,
    PID_SPD_KPDIV	= 0x2001,
    PID_SPD_KI 		= 0x2002,
    PID_SPD_KIDIV	= 0x2003,

    //pid of position loop
    PID_POS_KP 		= 0x3000,
    PID_POS_KPDIV 	= 0x3001,
    PID_POS_KI 		= 0x3002,
    PID_POS_KIDIV	= 0x3003,
    PID_POS_UP_LIM	= 0x3003,
    PID_POS_LOW_LIM	= 0x3004,

    FFC_A_FACTOR	= 0x4000,
    FFC_B_FACTOR	= 0x4001
};

enum motor_run_option{
    DIR_FORWARD = 0x01,
    DIR_BACK 	= 0x02,
};

class MotorProtocol{

public:
    MotorProtocol();

    void setQComboBoxCommand(QComboBox *combobox);
    void setQComboBoxOption(QComboBox *combobox);
    void setQComboBoxData(QComboBox *combobox);
    void setQLineEditData(QLineEdit *lineedit);
private:
    const int16_t   m_commandMask = 0xF000;
    const int16_t   m_commandShift = 12;
    const char m_head = '%';
    const char m_tail = '&';
    QComboBox *m_QComboBoxCommand = nullptr;
    QComboBox *m_QComboBoxOption  = nullptr;
    QComboBox *m_QComboBoxData  = nullptr;
    QLineEdit *m_QLineEditData  = nullptr;

    QMap<QString, int16_t>      m_MapCommand;
    QMap<QString, int8_t>       m_MapOption;

    union u_ComboxData{
        int32_t data;
        char data_n[4];
    };

    union u_ComboxCommand{
        int16_t data;
        char data_n[2];
    };

    u_ComboxCommand             m_unionComboxCommand;
    u_ComboxData                m_unionComboxData;

    void initUI();
    void initConnect();
    void initMap();

public:
    void init();
    void initQComboBoxOption(const QString &str);
    void initQComboBoxOption(int val);
    void setQLineEditDataValue(int32_t val);
    QByteArray getMotorSendData();

};


#endif // MOTOR_PROTOCOL_H
