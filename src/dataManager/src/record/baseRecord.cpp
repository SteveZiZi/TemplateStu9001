#include "baseRecord.h"


CBaseRecorder::CBaseRecorder(QObject *parent)
: QThread(parent)
, m_bExitThread(false)
{

}

CBaseRecorder::~CBaseRecorder()
{

}
