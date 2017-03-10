#include "mLineEditDelegate.h"

#include <mLineEdit>
#include <dirKeyInput>

#include "debug.h"

MLineEditDelegate::MLineEditDelegate(QObject *parent)
: QItemDelegate()
, m_dirKeyInput(NULL)
{

}

QWidget *MLineEditDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    MLineEdit *editor = new MLineEdit(parent, false);
    editor->setObjectName("mLineEdit_Delegate");
    editor->setDirKeyInput(m_dirKeyInput);
    editor->setAlignment(Qt::AlignCenter);

    return editor;
}

void MLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    MLineEdit *lineEdit = static_cast<MLineEdit*>(editor);
    lineEdit->setText(value);
}

void MLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    MLineEdit *lineEdit = static_cast<MLineEdit*>(editor);
    model->setData(index, lineEdit->text());
}

void MLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
