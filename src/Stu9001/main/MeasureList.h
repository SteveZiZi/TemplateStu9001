#pragma once

#include <QtGui/QGroupBox>

class CMeasureItem;
class QTimer;

class CMeasureShowData;
class CTempHumShowData;
class CWireTypeSettings;

class CMeasureList : public QGroupBox
{
    Q_OBJECT

public:
    CMeasureList(QWidget* parent = 0);
    virtual ~CMeasureList();

    void create(void);

    void startRefreshTask(quint32 ms);
    void stopRefreshTask();

public slots:
    void updateMeasure();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void destroy(void);

private:
    typedef QList<CMeasureItem*> MeasureList;
    
    MeasureList m_measureList;
    QTimer* m_timer;

    CMeasureShowData* m_measureDev;
    CTempHumShowData* m_tempHumDev;
    CWireTypeSettings* m_wireTypeDev;
};