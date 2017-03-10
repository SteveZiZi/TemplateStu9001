#ifndef STU9001_H
#define STU9001_H

#include <QtGui/QDialog>
#include "ui_stu9001.h"

class QListWidgetItem;
class CTopBarMgr;
class CBottomBarMgr;
class CMixImage;
class CMeasureList;

class CNaviMenuMgr;

class Stu9001 : public QDialog, private Ui::Stu9001Class
{
    Q_OBJECT

public:
    Stu9001(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Stu9001();

protected:
    void keyPressEvent(QKeyEvent *);

    void closeEvent(QCloseEvent *);

private:
    CNaviMenuMgr*   m_pNaviMenuMgr;
    CTopBarMgr*     m_pTopBarMgr;
    CBottomBarMgr*  m_pBottomBarMgr;

    CMixImage*      m_pMainImage;
    CMeasureList*   m_pMeasureList;
};

#endif // STU9001_H
