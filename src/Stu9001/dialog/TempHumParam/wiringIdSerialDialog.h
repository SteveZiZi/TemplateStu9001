#pragma once


#include "../baseDialog.h"
#include <wiringIdSerial>


class MTableWidget;
class CDirKeyInput;
class QTableWidgetItem;

class CWiringIdSerialDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    enum {REPORT_ROWS = 6};

    CWiringIdSerialDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CWiringIdSerialDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

protected slots:
    void contactIdChanged(QTableWidgetItem *item);
    void busbarIdChanged(QTableWidgetItem *item);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    MTableWidget* createTableWidget(QString objectName, int item);
    //更新设置到界面
    void updateSettings();
    void tableWidgetChanged(quint8 order, QTableWidgetItem* item);

private:
    MTableWidget* tableWidget_contact;
    MTableWidget* tableWidget_busbar;
    CDirKeyInput* m_dirKeyInput;

    WIRING_ID_SERIAL m_idSerial;
    bool    m_bModify;
};