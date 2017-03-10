#pragma once


#include "../baseDialog.h"
#include <motorParam>

class QLabel;
class MDataEdit;
class CDirKeyInput;
class MComboBox;

class CMotorParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    enum {
        REPORT_ROWS = 6,
        LINE_EDIT_NUM   = 3,
        COMBOBOX_NUM    = 3
    };

    CMotorParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CMotorParamDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

private slots:
    //LineEdit changed
    void modifySettings(const QVariant& var);
    //ComboBox changed
    void modifySettings(int index);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();
    //更新设置到界面
    void updateSettings(void);

private:
    QLabel* m_label[10];
    MDataEdit* m_lineEdit[LINE_EDIT_NUM];
    MComboBox* m_comboBox[COMBOBOX_NUM];

    CDirKeyInput* m_dirKeyInput;

    CMotorParam* m_dev;
    MotorParamSettings m_settings;
    bool        m_bModify;
};