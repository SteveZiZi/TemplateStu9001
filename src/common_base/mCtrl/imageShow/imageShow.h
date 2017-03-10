/**
 * \file
 *      imageShow.h
 *
 * \brief
 *      Í¼Æ¬ÏÔÊ¾¿Ø¼þÍ·ÎÄ¼þ
 *
 *  \note
 *
 *
 * \author
 *      yangyuchao      2015/8/14
 */

#pragma once

#include <QtGui/QLabel>
#include <QtGui/QBrush>

#include <QList>
#include <QTimer>

class CImageShow : public QLabel
{
    Q_OBJECT
public:
	CImageShow(QWidget* parent = 0);
	virtual ~CImageShow();

public:
    void insertImage(QString fileName) {m_vectImage.push_back(new QBrush(QImage(fileName)));}
    void showImage(int item) { 
        if (item < count())  {
            m_item = item;
            repaint();
        }
    }
    int item() { return m_item; }
    int count() {return m_vectImage.count();}
    int nextItem() {
        int item = m_item;
        item++;
        if (item == count())
            item = 0;
        return item;
    }
    int preItem() {
        int item = m_item;
        item--;
        if (item < 0) 
            item = count()-1;
        return item;
    }

    void loopPlay(int interval) {
        if (!m_timer)  {
            m_timer = new QTimer(this);
            connect(m_timer, SIGNAL(timeout()), this, SLOT(tick()));
        }
        if (m_timer->isActive()) {
            m_timer->stop();
        }
        m_timer->start(interval);
    }
    void stopPlay() {
        if (m_timer && m_timer->isActive()) {
            m_timer->stop();
        }
    }
    bool isPlay(void) {
        if (m_timer && m_timer->isActive()) 
            return true;
        return false;
    }


private slots:
    void tick() {
        showImage(nextItem());
    }

private:
    void clear() {
        for(ImageList::Iterator it = m_vectImage.begin(); it != m_vectImage.end(); it++)
            if (*it) delete (*it);
        m_vectImage.clear();
    }

    QBrush* currentBrush() {
        return m_vectImage[m_item];
    }

protected:
    virtual void paintEvent(QPaintEvent * event);

private:
    typedef QList<QBrush*> ImageList;

    int         m_item;            ///< µ±Ç°×´Ì¬
    ImageList   m_vectImage;       ///< ×´Ì¬Í¼Æ¬Ó³Éä

    QTimer*     m_timer;
};


