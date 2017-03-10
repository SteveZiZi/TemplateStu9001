#pragma once

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

class CMeasureItem : public QGroupBox
{
    Q_OBJECT

public:
    CMeasureItem(QWidget* parent = 0, QString caption = "", QString value = "", QString unit = "");
    virtual ~CMeasureItem();

    void setCaption(const QString& caption) {label_caption->setText(caption);}
    void setValue(const QString& val) {label_value->setText(val);}
    void setUnit(const QString& unit) {label_unit->setText(unit);}

private:
    QLabel* label_caption;
    QLabel* label_value;
    QLabel* label_unit;
};