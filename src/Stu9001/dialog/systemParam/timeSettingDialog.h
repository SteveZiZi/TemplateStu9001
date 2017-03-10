#pragma once


#include "../baseDialog.h"

#include <QDateTime>

class QLabel;
class MDateTimeEdit;
class QTimer;

class CTimeSettingDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CTimeSettingDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CTimeSettingDlg();


    //override fro CBaseDialog
    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();


protected slots:
    void updateTime(void);

    void enterEditMode(void);
    void cancelEditMode(void);
    void finishEditTime(const QDateTime &date);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();


private:
    QLabel *label_time;
    MDateTimeEdit *m_dateTimeEdit;
    QTimer* m_tickTimer;
};