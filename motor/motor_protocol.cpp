#include "motor_protocol.h"

MotorProtocol::MotorProtocol()
{

}

void MotorProtocol::setQComboBoxCommand(QComboBox *combobox)
{
    this->m_QComboBoxCommand = combobox;
}

void MotorProtocol::setQComboBoxOption(QComboBox *combobox)
{
    this->m_QComboBoxOption = combobox;
}

void MotorProtocol::setQComboBoxData(QComboBox *combobox)
{
    this->m_QComboBoxData = combobox;
}

void MotorProtocol::setQLineEditData(QLineEdit *lineedit)
{
    this->m_QLineEditData = lineedit;
}

/*
    FFC_A_FACTOR	= 0x4000,
    FFC_B_FACTOR	= 0x4001
*/

void MotorProtocol::initUI()
{
    if(this->m_QComboBoxCommand != nullptr){
        foreach(const QString &str,m_MapCommand.keys()){
            m_QComboBoxCommand->addItem(str,m_MapCommand.value(str));
        }
    }
}

void MotorProtocol::initMap()
{
    m_MapCommand.insert("M_STOP",0x0001);
    m_MapCommand.insert("M_RUN_RPM",0x0002);
    m_MapCommand.insert("M_RUN_POS",0x0003);
    m_MapCommand.insert("M_STARTUP",0x0004);
    m_MapCommand.insert("M_SYS_RESET",0x000F);

    m_MapCommand.insert("PID_CUR_KP",0x1000);
    m_MapCommand.insert("PID_CUR_KPDIV",0x1001);
    m_MapCommand.insert("PID_CUR_KI",0x1002);
    m_MapCommand.insert("PID_CUR_KIDIV",0x1003);

    m_MapCommand.insert("PID_SPD_KP",0x2000);
    m_MapCommand.insert("PID_SPD_KPDIV",0x2001);
    m_MapCommand.insert("PID_SPD_KI",0x2002);
    m_MapCommand.insert("PID_SPD_KIDIV",0x2003);
    //pid of position loop
    m_MapCommand.insert("PID_POS_KP",0x3000);
    m_MapCommand.insert("PID_POS_KPDIV",0x3001);
    m_MapCommand.insert("PID_POS_KI",0x3002);
    m_MapCommand.insert("PID_POS_KIDIV",0x3003);
    m_MapCommand.insert("PID_POS_UP_LIM",0x3003);
    m_MapCommand.insert("PID_POS_LOW_LIM",0x3004);

    m_MapCommand.insert("FFC_A_FACTOR",0x4000);
    m_MapCommand.insert("FFC_B_FACTOR",0x4001);

    //init run cmd option

}

void MotorProtocol::initConnect()
{

}

void MotorProtocol::init()
{
    this->initMap();
    this->initUI();
    this->initConnect();
}

void MotorProtocol::initQComboBoxOption(int val)
{
    if(m_QComboBoxOption != nullptr && !m_MapOption.isEmpty()){
        m_MapOption.clear();
        m_QComboBoxOption->clear();
    }
    switch(val){
    case M_STOP:
        m_MapOption.insert("NO_OPTION",0x0000);
        break;
    case M_RUN_RPM:
        m_MapOption.insert("DIR_FORWARD",0x01);
        m_MapOption.insert("DIR_BACK",0x02);
        break;
    case M_RUN_POS:
        m_MapOption.insert("DIR_FORWARD",0x01);
        m_MapOption.insert("DIR_BACK",0x02);
        break;
    case M_STARTUP:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_CUR_KP:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_CUR_KPDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_CUR_KI:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_CUR_KIDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_SPD_KP:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_SPD_KPDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_SPD_KI:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_SPD_KIDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_POS_KP:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_POS_KPDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_POS_KI:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_POS_KIDIV:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case PID_POS_LOW_LIM:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case FFC_A_FACTOR:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    case FFC_B_FACTOR:
        m_MapOption.insert("NO_OPTION",0x00);
        break;
    default:
        m_MapOption.insert("NO_OPTION",0x00);
    }
    if(m_QComboBoxOption != nullptr && !m_MapOption.isEmpty()){
        foreach(const QString &str,m_MapOption.keys()){
            m_QComboBoxOption->addItem(str,m_MapOption.value(str));
        }
    }
}

void MotorProtocol::setQLineEditDataValue(int32_t val)
{
    this->m_unionComboxData.data = val;
}

QByteArray MotorProtocol::getMotorSendData()
{
    QByteArray qByteArray;
    qByteArray.insert(0,this->m_head);
    if(m_QComboBoxCommand == nullptr){
        qDebug() << "m_QComboBoxCommand is nullptr: " << __func__ << ";Line:"<< __LINE__;
    }
    if(m_QLineEditData == nullptr){
        qDebug() << "m_QLineEditData is nullptr: " << __func__ << ";Line:"<< __LINE__;
    }
    m_unionComboxCommand.data = this->m_MapCommand.value(m_QComboBoxCommand->currentText());
    m_unionComboxData.data = this->m_QLineEditData->text().toInt();
    qByteArray.insert(1, m_unionComboxCommand.data_n[0]);
    qByteArray.insert(2, m_unionComboxCommand.data_n[1]);
    qByteArray.insert(3, this->m_MapOption.value(m_QComboBoxOption->currentText()) );
    qByteArray.insert(4, m_unionComboxData.data_n[0]);
    qByteArray.insert(5, m_unionComboxData.data_n[1]);
    qByteArray.insert(6, m_unionComboxData.data_n[2]);
    qByteArray.insert(7, m_unionComboxData.data_n[3]);
    qByteArray.insert(8,this->m_tail);
    return qByteArray;
}

void MotorProtocol::initQComboBoxOption(const QString &str)
{
    initQComboBoxOption(this->m_MapCommand.value(str));
}
