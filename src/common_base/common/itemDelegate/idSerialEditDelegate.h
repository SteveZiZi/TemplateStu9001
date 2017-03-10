#pragma once

#include "mLineEditDelegate.h"

class IDSerialEditDelegate : public MLineEditDelegate
{
public:
    IDSerialEditDelegate(QObject *parent = 0);

    //override from QItemDelegate
    virtual void paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void drawBorder(QPainter *painter, QColor& clr, QRect& rect) const;
};
