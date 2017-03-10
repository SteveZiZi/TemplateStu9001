#include "AbstractMenu.h"

#include "debug.h"

CAbstractMenuContent::CAbstractMenuContent(CAbstractMenu* pMenu)
: m_pMenu(pMenu)
{

}

CAbstractMenuContent::~CAbstractMenuContent()
{

}


CAbstractMenu::CAbstractMenu(CAbstractMenu* parent/* = NULL*/)
: m_pParentObj(parent)
{

}

CAbstractMenu::~CAbstractMenu()
{

}
