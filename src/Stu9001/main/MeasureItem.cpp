#include "MeasureItem.h"

#include "debug.h"

CMeasureItem::CMeasureItem(QWidget* parent, QString caption, QString value, QString unit)
: QGroupBox(parent)
{
    this->setFixedHeight(35);
    this->setFixedWidth(144);

    int x = 10;
    int y = 0;
    int h = 35;
    int w1 = 40, w2 = 60, w3 = 20;

    label_caption = new QLabel(this);
    label_caption->setObjectName("label_caption");
    label_caption->setGeometry(x, y, w1, h);
    label_caption->setText(caption);

    x += w1+1;
    label_value = new QLabel(this);
    label_value->setObjectName("label_value");
    label_value->setGeometry(x, y, w2, h);
    label_value->setText(value);
    label_value->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    x += w2+1;
    label_unit = new QLabel(this);
    label_unit->setObjectName("label_unit");
    label_unit->setGeometry(x, y, w3, h);
    label_unit->setText(unit);
}

CMeasureItem::~CMeasureItem()
{
    if (label_caption) {
        delete label_caption;
        label_caption = NULL;
    }

    if (label_value) {
        delete label_value;
        label_value = NULL;
    }

    if (label_unit) {
        delete label_unit;
        label_unit = NULL;
    }
}