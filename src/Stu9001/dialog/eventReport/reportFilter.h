#pragma once

#include <QtGui/QGroupBox>

class MCheckBox;
class QLabel;
class MDateTimeEdit;
class MDataEdit;

#include <QDateTime>


class CReportFilter : public QGroupBox
{
    Q_OBJECT
        
public:
    CReportFilter(QWidget *parent = 0);
    ~CReportFilter();

signals:
    void dateTimeChanged(int item, const QDateTime &date);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual bool focusNextPrevChild(bool next);

private:
    void createFilter();
    void destoryFilter();

private slots:
    void changedStartDateTime(const QDateTime &dateTime);
    void changedEndDateTime(const QDateTime &dateTime);

private:
    QLabel* label_time;
    MDateTimeEdit* date_start;
    MDateTimeEdit* date_end;
    MCheckBox* checkBox_warning;
    MCheckBox* checkBox_action;
    MDataEdit* lineEdit_warningCnt;
    MDataEdit* lineEdit_actionCnt;
};