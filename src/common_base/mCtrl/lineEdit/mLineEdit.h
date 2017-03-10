#pragma once

#include <QtGui/QLineEdit>


class CDirKeyInput;

class MLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit MLineEdit(QWidget* parent = 0, bool trrigleEdit = true);
    explicit MLineEdit(const QString &text, QWidget* parent=0, bool trrigleEdit = true);
    virtual ~MLineEdit();

    /*
     *  @Warning: dirKeyInput
     */
    void setDirKeyInput(CDirKeyInput* dirKeyInput);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void focusInEvent(QFocusEvent *);

protected:
    virtual void startEdit(void);
    virtual void endEdit(void);
    virtual void cancelEdit(void);
    virtual bool dirInput(int key);

signals:
    void accepted(const QString& text);
    void rejected(const QString& text);

protected:
    CDirKeyInput* m_dirKeyInput;
    QString m_oldText;

    bool m_trrigleEdit;
    bool m_isEditMode;
};