#pragma once


#include "../baseDialog.h"
#include <wireTypeSettings>

class QTableWidget;
class QTableWidgetItem;

class CWireTypesParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CWireTypesParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CWireTypesParamDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    QTableWidget* createTableWidget(QString objectName);
    //更新设置到界面
    void updateSettings();

private:
    QTableWidget* tableWidget;

    CWireTypeSettings* m_dev;
    WIRE_LINK_STYLE_ENUM m_wireType;
    bool    m_bModify;
};