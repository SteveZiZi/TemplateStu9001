#pragma once


#include "../baseDialog.h"
#include <wiringTempThreshold>

class QLabel;
class MDataEdit;
class CDirKeyInput;

class CWiringMeasureTempParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    enum {REPORT_ROWS = 6};

    CWiringMeasureTempParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CWiringMeasureTempParamDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

protected:
    virtual void paintEvent(QPaintEvent *event);

    private slots:
        //LineEdit changed
        void modifySettings(const QVariant& var);

private:
    //override from CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    //更新设置到界面
    void updateSettings(void);

private:
    QLabel* m_label[REPORT_ROWS];
    MDataEdit* m_lineEdit[REPORT_ROWS];

    CDirKeyInput* m_dirKeyInput;

    WIRING_TEMP_THRESHOLD m_threshold;
    bool    m_bModify;
};