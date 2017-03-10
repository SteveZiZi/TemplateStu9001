#pragma once

#include <QtGui/QItemDelegate>

class CDirKeyInput;

class MLineEditDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    MLineEditDelegate(QObject *parent = 0);

    //override from QItemDelegate
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    CDirKeyInput* dirKeyInput() {return m_dirKeyInput;}
    void setDirKeyInput(CDirKeyInput* dirKeyInput) {m_dirKeyInput = dirKeyInput;}

private:
    CDirKeyInput* m_dirKeyInput;
};
