#pragma once

#include "mLineEdit.h"


class MIPAddrEdit : public MLineEdit
{
    Q_OBJECT

public:
    explicit MIPAddrEdit(QWidget* parent = 0);
    explicit MIPAddrEdit(const QString &, QWidget* parent=0);
    virtual ~MIPAddrEdit();

protected:
    //override MLineEdit
    virtual void startEdit(void);
    virtual void endEdit(void);

private:
    QString stringToWholeIp(const QString& string);
    QString wholeIpToString(const QString& string);
};