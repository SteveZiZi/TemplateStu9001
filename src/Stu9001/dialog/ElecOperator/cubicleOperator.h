#pragma once

#include <QtGui/QGroupBox>
#include <QPen>

class QLabel;
class MComboBox;

class CCubicleOperator : public QGroupBox
{
    Q_OBJECT
        
public:
    enum {ROWS = 7};
    CCubicleOperator(QWidget *parent = 0);
    ~CCubicleOperator();

    MComboBox* comboBox(int row);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

signals:
    void modeChanged(bool bAutoMode);
    void fanStatusChanged(int item, bool bStart);
    void lampStatusChanged(int item, bool bOn);
    void heaterStatusChanged(int item, bool bStart);
    void gateStatusChanged(bool bOpen);

private slots:
    void modeComboBoxSelChanged(int sel);
    void fan1ComboBoxSelChanged(int sel);
    void fan2ComboBoxSelChanged(int sel);
    void lampComboBoxSelChanged(int sel);
    void heater1ComboBoxSelChanged(int sel);
    void heater2ComboBoxSelChanged(int sel);
    void gateComboBoxSelChanged(int sel);

private:
    void createCtrl();
    void moveToNextWidget();
    void moveToPreWidget();
private:
    QLabel* m_label[ROWS];
    MComboBox* m_comboBox[ROWS];

    QPen m_linearGradientPen;

    QWidget* m_firstEnableWidget;
    QWidget* m_lastEnableWidget;
};