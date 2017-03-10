#pragma once

#include <QtGui/QGroupBox>

class MPushButton;
class MTableWidget;

class CbarrowOperator : public QGroupBox
{
    Q_OBJECT
        
public:
    CbarrowOperator(QWidget *parent = 0);
    ~CbarrowOperator();

signals:
    void tele_in(void);
    void tele_out(void);
    void stop(void);
    void reset(void);

private slots:
    void teleInClick(void);
    void teleOutClick(void);
    void stopClick(void);
    void resetClick(void);
    void allowOperate(bool allow);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *event);

private:
    void createBtn();
    MTableWidget* createTableWidget(QString objectName);

private:
    MPushButton* m_pushButton[4];
    MTableWidget* m_tableWidget;
    int m_item;
    bool m_bAllowOper;
};