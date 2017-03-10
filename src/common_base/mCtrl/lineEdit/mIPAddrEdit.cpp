#include "mIPAddrEdit.h"

#include <QtGui/QKeyEvent>
#include <dirKeyInput>

#include "debug.h"

MIPAddrEdit::MIPAddrEdit(const QString& text, QWidget* parent/* =0 */)
: MLineEdit(text, parent)
{
}

MIPAddrEdit::MIPAddrEdit(QWidget* parent/* =0 */)
: MLineEdit(parent)
{
}

MIPAddrEdit::~MIPAddrEdit()
{

}

void MIPAddrEdit::startEdit()
{
    setText(stringToWholeIp(text()));
    MLineEdit::startEdit();
}


void MIPAddrEdit::endEdit(void)
{
    setText(wholeIpToString(text()));
    MLineEdit::endEdit();
}


QString MIPAddrEdit::stringToWholeIp(const QString& string)
{
    int ip[4] = {0, 0, 0, 0};

    QStringList ipAddr = string.split('.');
    for(int i = 0; i < ipAddr.size(); i++) {
        ip[i] = ipAddr.at(i).trimmed().toInt();
    }

    QChar fill('0');

    return QString("%1.%2.%3.%4").arg(ip[0], 3, 10, fill) \
                                 .arg(ip[1], 3, 10, fill) \
                                 .arg(ip[2], 3, 10, fill) \
                                 .arg(ip[3], 3, 10, fill);
}

QString MIPAddrEdit::wholeIpToString(const QString& string)
{
    int ip[4] = {0, 0, 0, 0};

    QStringList ipAddr = string.split('.');
    for(int i = 0; i < ipAddr.size(); i++) {
        ip[i] = ipAddr.at(i).trimmed().toInt();
    }

    return QString("%1.%2.%3.%4").arg(ip[0]) \
                                 .arg(ip[1]) \
                                 .arg(ip[2]) \
                                 .arg(ip[3]);
}

