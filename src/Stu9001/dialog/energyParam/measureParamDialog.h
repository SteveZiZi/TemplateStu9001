#pragma once


#include "../baseDialog.h"
#include <MeasureParam>

class QLabel;
class MDataEdit;
class CDirKeyInput;
class MComboBox;

class CMeasureParamDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CMeasureParamDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CMeasureParamDlg();


    virtual void _ShowContent(int style, quint32 data);
    virtual void _LeaveContent();
    virtual void _HideContent();

private slots:
    void modifyPrimaryPT(const QVariant& var);
    void modifyPrimaryCT(const QVariant& var);
    void modifyRatedVol(const QVariant& var);
    void modifyRatedCur(const QVariant& var);

    void modifyVolGrade(int index);
    void modifyZeroSquence(int index);
    void modifyCTSample(int index);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

    void updateParam(void);

private:
    QLabel* label_primaryPT;
    MDataEdit* lineEdit_primaryPT;
    QLabel* label_primaryCT;
    MDataEdit* lineEdit_primaryCT;

    QLabel* label_CTSample;
    MComboBox* comboBox_CTSample;

    QLabel* label_RatedVol;
    MDataEdit* lineEdit_RatedVol;
    QLabel* label_RatedCur;
    MDataEdit* lineEdit_RatedCur;

    QLabel* label_volGrade;
    MComboBox* comboBox_volGrade;
    QLabel* label_zeroSquence;
    MComboBox* comboBox_zeroSquence;

    CDirKeyInput* m_dirKeyInput;

    CMeasureParam* m_dev;
    MeasureParam m_param;
    bool        m_bModify;
};