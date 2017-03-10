#include "mTreeWidget.h"

#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QHeaderView>
#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>

#include "debug.h"

MTreeWidget::MTreeWidget(QWidget *parent /* = 0 */)
:QTreeWidget(parent)
, m_editMode(false)
{

}

MTreeWidget::~MTreeWidget()
{

}


void MTreeWidget::paintEvent(QPaintEvent *event)
{
    QTreeWidget::paintEvent(event);
}


void MTreeWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QTreeWidgetItem* item = this->currentItem();

    qDebug() << "MTreeWidget::keyPressEvent" << hex << event->key() << "m_editMode=" << m_editMode;

    if (m_editMode) {
        event->ignore();
    }
    else {
        switch(key) 
        {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            //有子菜单，展开子菜单，
            //没有子菜单，可勾选，则勾选取反，否则进入编辑模式
            if (!item->parent()) {
                if (item->childCount() != 0 && !item->isExpanded()) {
                    item->setExpanded(true);
                    setCurrentItem(item->child(0));
                }
            }
            else {
                if (item->flags()&Qt::ItemIsUserCheckable) {
                    if (item->checkState(1) == Qt::Checked)
                        item->setCheckState(1, Qt::Unchecked);
                    else
                        item->setCheckState(1, Qt::Checked);
                }
                else {
                    editItem(item, 1);
                    m_editMode = true;
                }
            }
            break;
        case Qt::Key_Escape:
            if (item->parent()) {
                setCurrentItem(item->parent());
                currentItem()->setExpanded(false);
            }
            else 
                event->ignore();
            break;
        case Qt::Key_Left:
        case Qt::Key_Right:
            if (!item->parent()) {
                event->ignore();
            }
            break;
        case Qt::Key_Up:
            if (item->parent()) {
                QTreeWidgetItem* parent = item->parent();
                if (parent->child(0) != item) {
                    QTreeWidget::keyPressEvent(event);
                }
            }
            else {
                if (topLevelItem(0) == item) {
                    setCurrentItem(topLevelItem(topLevelItemCount()-1));
                }
                else
                    QTreeWidget::keyPressEvent(event);
            }
            break;
        case Qt::Key_Down:
            if (item->parent()) {
                QTreeWidgetItem* parent = item->parent();
                if (parent->child(parent->childCount()-1) != item) {
                    QTreeWidget::keyPressEvent(event);
                }
            }
            else {
                if (topLevelItem(topLevelItemCount()-1) == item) {
                    setCurrentItem(topLevelItem(0));
                }
                else
                    QTreeWidget::keyPressEvent(event);
            }
            break;
        default:
            event->ignore();
            break;
        }
    }
}


void MTreeWidget::focusInEvent(QFocusEvent *event)
{
    if (m_editMode) {
        m_editMode = false;
    }
    QTreeWidget::focusInEvent(event);
}
