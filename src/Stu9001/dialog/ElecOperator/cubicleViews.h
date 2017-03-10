#pragma once

#include <QtGui/QGroupBox>

#include <machine>

class CCubicleViews : public QGroupBox
{
    Q_OBJECT
        
public:
    CCubicleViews(QWidget *parent = 0);
    ~CCubicleViews();

    void setBarrowInitStatus(CMachine::STATE_ENUM status);
    void setEarthKnifeInitStatus(CMachine::STATE_ENUM status);

public Q_SLOTS:
    //override from QWidget
    virtual void setVisible(bool visible);

public slots:
    void operate_fun(int item, bool start) {
        Q_ASSERT(m_fan[0]&&m_fan[1]&&item<2); 
        if (start)
            m_fan[item]->loopPlay(20);
        else 
            m_fan[item]->stopPlay();
        m_bFanOn[item] = start;
    }

    void operate_lamp(int item, bool switchOn) {
        Q_ASSERT(m_lamp[0]&&m_lamp[1]&&item<2); 
        m_lamp[item]->showImage(switchOn);
    }

    void operate_heater(int item, bool heat) {
        Q_ASSERT(m_heater[0]&&m_heater[1]&&item<2); 
        m_heater[item]->showImage(heat);
    }

    void barrow_open() {Q_ASSERT(m_barrow); m_barrow->open();}
    void barrow_close() {Q_ASSERT(m_barrow); m_barrow->close();}
    void barrow_stop() {Q_ASSERT(m_barrow); m_barrow->stop();}
    void earthKnife_open() {Q_ASSERT(m_earthKnife); m_earthKnife->open();}
    void earthKnife_close() {Q_ASSERT(m_earthKnife); m_earthKnife->close();}
    void earthKnife_stop() {Q_ASSERT(m_earthKnife); m_earthKnife->stop();}

private:
    CMachine* createBarrow(int x, int y, int w, int h);
    CMachine* createEarthKnife(int x, int y, int w, int h);
    CImageShow* createLamp(int x, int y, int w, int h);
    CImageShow* createFan(int x, int y, int w, int h);
    CImageShow* createHeater(int x, int y, int w, int h);

private:
    CMachine        *m_barrow;
    CMachine        *m_earthKnife;

    CImageShow      *m_lamp[2];
    CImageShow      *m_fan[2];
    CImageShow      *m_heater[2];

    bool            m_bFanOn[2];
};