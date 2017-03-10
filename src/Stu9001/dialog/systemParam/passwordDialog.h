#pragma once


#include "../baseDialog.h"

class QLabel;
class MLineEdit;
class CDirKeyInput;

class CPasswordDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CPasswordDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CPasswordDlg();

    //override fro CBaseDialog
    virtual void _ShowContent(int style, quint32 data);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //override fro CBaseDialog
    virtual void moveToNextWidget();
    virtual void moveToPreWidget();

private:
    QLabel *label_newPassword;
    QLabel *label_oldPassword;
    QLabel *label_confirmPassword;
    MLineEdit *lineEdit_newPassword;
    MLineEdit *lineEdit_oldPassword;
    MLineEdit *lineEdit_confirmPassword;

    CDirKeyInput* m_dirKeyInput;
};