#pragma once


#include "../baseDialog.h"
#include <eventReportRecorder>


class CReportFilter;
class MTableWidget;
class QTimer;

struct EventReportItem_t {
    quint32 item;
    QString time;
    QString caption;
    QString style;
    bool hasRecord;
};

class CEventReportDlg : public CBaseDialog
{
    Q_OBJECT
        
public:
    CEventReportDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~CEventReportDlg();

    virtual void _ShowContent(int style, quint32 data);
    virtual void _HideContent();

public slots:
    void detectNewEvent();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void moveToNextWidget();
    void moveToPreWidget();

    MTableWidget* createTableWidget(QString objectName);
    void addNewEvent(EventReportItem_t& eventItem);
    void showNewestEvent();
    void recordConv(int eventNo, const EventRecordItem& report, EventReportItem_t& eventItem);

private:
    CReportFilter* m_filter;
    MTableWidget* m_tableWidget;
    QTimer* m_timer;

    quint32 m_eventNo;
};