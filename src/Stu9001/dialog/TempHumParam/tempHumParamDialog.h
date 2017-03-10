#pragma once


#include "../baseDialog.h"
#include <humidityThreshold>

class QLabel;
class MDataEdit;
class CDirKeyInput;

class CTempHumParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CTempHumParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CTempHumParamDlg();


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
    QLabel* label_tempMax;
    MDataEdit* lineEdit_tempMax;
    QLabel* label_tempMin;
    MDataEdit* lineEdit_tempMin;

    QLabel* label_humMax;
    MDataEdit* lineEdit_humMax;
    QLabel* label_humMin;
    MDataEdit* lineEdit_humMin;

    CDirKeyInput* m_dirKeyInput;

    int m_nItem;

    TEMP_HUMIDITY_THRESHOLD m_threshold[2];
    bool    m_bModify;
};