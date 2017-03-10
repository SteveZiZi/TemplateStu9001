#pragma once

#include "dirKeyInput.h"

class CDirKeyInputForData : public CDirKeyInput
{
public:
    CDirKeyInputForData(qint32 maxTextLength = 6);
    virtual ~CDirKeyInputForData();

protected:
    virtual void  moveLeft();
    virtual void  moveRight();
};