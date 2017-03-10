#pragma once


#include "../baseDialog.h"
#include <harmonicsParam>

class QLabel;
class MComboBox;
class MTableWidget;
class QTableWidgetItem;

class CDirKeyInputForData;

class CHarnoicsParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CHarnoicsParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CHarnoicsParamDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

public slots:
    // 0 电流  1 电压
    void changeTableType(int type);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

protected slots:
    void tableWidget1Changed(QTableWidgetItem *item);
    void tableWidget2Changed(QTableWidgetItem *item);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    MTableWidget* createTableWidget(QString objectName, int item);
    //更新设置到界面
    void updateSettings(int type);
    void changeTableCaption(int type);

    void tableWidgetChanged(int order, QTableWidgetItem* item);

private:
    QLabel* label_harmonics;
    MComboBox* comboBox_harnoics;
    MTableWidget* harnoicsTable1;
    MTableWidget* harnoicsTable2;
    int m_currentRow;

    CDirKeyInputForData* m_dirKeyInputForData;

    CHarmonicParam* m_dev;
    HarmonicParam m_param;
    bool    m_bModify;
};