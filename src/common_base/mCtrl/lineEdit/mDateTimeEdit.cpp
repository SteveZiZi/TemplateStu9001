#include "mDateTimeEdit.h"

#include <MLineEdit>
#include <QKeyEvent>

#include "debug.h"


MDateTimeEdit::MDateTimeEdit(QWidget* parent)
: QDateTimeEdit(parent)
{
    setReadOnly(true);
    setDisplayFormat(SHOW_YEAR, SHOW_SECOND);
}

MDateTimeEdit::MDateTimeEdit(QDateTime& dateTime, ShowFlag start, ShowFlag end, QWidget* parent)
: QDateTimeEdit(dateTime, parent)
{
    setReadOnly(true);
    setDisplayFormat(start, end);
}

MDateTimeEdit::MDateTimeEdit(QDateTime& dateTime, QWidget* parent)
: QDateTimeEdit(dateTime, parent)
{
    setReadOnly(true);
    setDisplayFormat(SHOW_YEAR, SHOW_SECOND);
}

MDateTimeEdit::~MDateTimeEdit()
{

}

void MDateTimeEdit::setDisplayFormat(ShowFlag start, ShowFlag end)
{
    Q_ASSERT(start <= end);

    m_firstSection = start;
    m_lastSection = end;

    QString string("");
    if (m_firstSection <= SHOW_YEAR && m_lastSection >= SHOW_YEAR) {
        string.append("yyyy");
        if (m_lastSection > SHOW_YEAR) 
            string += "-";
    }
    if (m_firstSection <= SHOW_MONTH && m_lastSection >= SHOW_MONTH) {
        string.append("MM");
        if (m_lastSection > SHOW_MONTH) 
            string += "-";
    }
    if (m_firstSection <= SHOW_DAY && m_lastSection >= SHOW_DAY) {
        string.append("dd");
        if (m_lastSection > SHOW_DAY) 
            string += " ";
    }
    if (m_firstSection <= SHOW_HOUR && m_lastSection >= SHOW_HOUR) {
        string.append("hh");
        if (m_lastSection > SHOW_HOUR) 
            string += ":";
    }
    if (m_firstSection <= SHOW_MINUTE && m_lastSection >= SHOW_MINUTE) {
        string.append("mm");
        if (m_lastSection > SHOW_MINUTE) 
            string += ":";
    }
    if (m_firstSection <= SHOW_SECOND && m_lastSection >= SHOW_SECOND) {
        string.append("ss");
    }

    QDateTimeEdit::setDisplayFormat(string);
}

MDateTimeEdit::ShowFlag MDateTimeEdit::sectionToShowFlag(Section section)
{
    ShowFlag flag = m_firstSection;
    switch (section) {
        case YearSection:
            flag = SHOW_YEAR;
            break;
        case MonthSection:
            flag = SHOW_MONTH; 
            break;
        case DaySection:
            flag = SHOW_DAY;
            break;
        case HourSection:
            flag = SHOW_HOUR;
            break;
        case MinuteSection:
            flag = SHOW_MINUTE;
            break;
        case SecondSection:
            flag = SHOW_SECOND;
            break;
        default:
            Q_ASSERT(false);
            break;
    }
    return flag;
}

QDateTimeEdit::Section MDateTimeEdit::showFlagToSection(ShowFlag flag)
{
    Section section;
    switch (flag) {
        case SHOW_YEAR:
            section = YearSection;
            break;
        case SHOW_MONTH:
            section = MonthSection; 
            break;
        case SHOW_DAY:
            section = DaySection;
            break;
        case SHOW_HOUR:
            section = HourSection;
            break;
        case SHOW_MINUTE:
            section = MinuteSection;
            break;
        case SHOW_SECOND:
            section = SecondSection;
            break;
        default:
            Q_ASSERT(false);
            break;
    }
    return section;
}


bool MDateTimeEdit::isLastSection(Section section)
{
    return (m_lastSection == sectionToShowFlag(section));
}

bool MDateTimeEdit::isFirstSection(Section section)
{
    return (m_firstSection == sectionToShowFlag(section));
}

void MDateTimeEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MDateTimeEdit::keyPressEvent " << hex << event->key();

    if (isReadOnly())
    {
        switch(event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            setReadOnly(false);
            setSelectedSection(showFlagToSection(m_firstSection));
            emit startEdit();
            break;
        case Qt::Key_Escape:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_F7:
            event->ignore();
            break;
        default:
            event->accept();
            break;
        }
    }
    else {
        switch(event->key())
        {
        case Qt::Key_Left:
            if (!isFirstSection(currentSection())) {
                focusNextPrevChild(false);
            } 
            else {
                setSelectedSection(showFlagToSection(m_lastSection));
            }
            break;
        case Qt::Key_Right:
            if (!isLastSection(currentSection())) {
                focusNextPrevChild(true);
            }
            else {
                setSelectedSection(showFlagToSection(m_firstSection));
            }
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (!isReadOnly()) {
                setReadOnly(true);
                selectAll();
                emit finishEdit(dateTime());
            }
            else 
                event->ignore();
            break;
        case Qt::Key_Escape:
            if (!isReadOnly()) {
                setReadOnly(true);
                selectAll();
                emit cancelEdit();
            }
            else 
                event->ignore();
            break;
        default:
            QDateTimeEdit::keyPressEvent(event);
            break;
        }
    }
}


void MDateTimeEdit::focusInEvent(QFocusEvent *event)
{
    if (isReadOnly()) {
        selectAll();
    }
    else {
        QDateTimeEdit::focusInEvent(event);
    }
}

void MDateTimeEdit::focusOutEvent(QFocusEvent *event)
{
    QDateTimeEdit::focusOutEvent(event);
}


void MDateTimeEdit::setDateTime(const QDateTime &dateTime)
{
    QDateTimeEdit::setDateTime(dateTime);
    emit dateTimeChanged(dateTime);
}