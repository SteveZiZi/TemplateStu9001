#pragma once

#include <QDateTimeEdit>

class MDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT

public:
    enum ShowFlag {
        SHOW_YEAR,
        SHOW_MONTH,
        SHOW_DAY,
        SHOW_HOUR,
        SHOW_MINUTE,
        SHOW_SECOND
    };

    MDateTimeEdit(QWidget* parent = 0);
    MDateTimeEdit(QDateTime& dateTime, ShowFlag start, ShowFlag end, QWidget* parent = 0);
    MDateTimeEdit(QDateTime& dateTime, QWidget* parent = 0);
    virtual ~MDateTimeEdit();

public:
    void setDisplayFormat(ShowFlag start, ShowFlag end);

signals:
    void startEdit(void);
    void cancelEdit(void);
    void finishEdit(const QDateTime &dateTime);

public Q_SLOTS:
    void setDateTime(const QDateTime &dateTime);


protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    ShowFlag sectionToShowFlag(Section section);
    Section  showFlagToSection(ShowFlag flag);
    bool isLastSection(Section section);
    bool isFirstSection(Section section);


private:
    ShowFlag  m_firstSection;       //从哪个段开始显示
    ShowFlag  m_lastSection;        //显示到哪个段
};