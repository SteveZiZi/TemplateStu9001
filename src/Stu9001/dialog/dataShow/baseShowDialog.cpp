#include "baseShowDialog.h"

#include <QTimer>

#include "debug.h"

CBaseShowDialog::CBaseShowDialog(QWidget *parent, Qt::WFlags flags)
: CBaseDialog(parent, flags)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateShowData()));
}

CBaseShowDialog::~CBaseShowDialog()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}


void CBaseShowDialog::_ShowContent(int style, quint32 data)
{
    if (this->isHidden()) {
        this->show();
        updateShowData();
    }
    if (!m_timer->isActive())
        m_timer->start(500);
}

void CBaseShowDialog::_HideContent()
{
    if (this->isVisible()) {
        this->hide();
    }
    if (m_timer->isActive())
        m_timer->stop();
}