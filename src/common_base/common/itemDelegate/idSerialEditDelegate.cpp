#include "idSerialEditDelegate.h"

#include <QPainter>

#include "debug.h"

static QString replaceNewLine(QString text)
{
    const QChar nl = QLatin1Char('\n');
    for (int i = 0; i < text.count(); ++i)
        if (text.at(i) == nl)
            text[i] = QChar::LineSeparator;
    return text;
}

IDSerialEditDelegate::IDSerialEditDelegate(QObject *parent)
: MLineEditDelegate(parent)
{

}


void IDSerialEditDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());

    QStyleOptionViewItemV4 opt = setOptions(index, option);

    const QStyleOptionViewItemV2 *v2 = qstyleoption_cast<const QStyleOptionViewItemV2 *>(&option);
    opt.features = v2 ? v2->features
        : QStyleOptionViewItemV2::ViewItemFeatures(QStyleOptionViewItemV2::None);
    const QStyleOptionViewItemV3 *v3 = qstyleoption_cast<const QStyleOptionViewItemV3 *>(&option);
    opt.locale = v3 ? v3->locale : QLocale();
    opt.widget = v3 ? v3->widget : 0;

    opt.rect.adjust(7, 3, -7, -3);

    // prepare
    painter->save();
    if (this->hasClipping())
        painter->setClipRect(opt.rect);


    QString text;
    QVariant value = index.data(Qt::DisplayRole);
    if (value.isValid() && !value.isNull()) {
        text = replaceNewLine(value.toString());
    }

    opt.displayAlignment = Qt::AlignCenter;
    opt.palette.setColor(QPalette::Inactive, QPalette::Background, Qt::white);
    opt.palette.setColor(QPalette::All, QPalette::Text, Qt::black);

    drawBackground(painter, opt, index);
    drawDisplay(painter, opt, opt.rect, text);
    drawFocus(painter, opt, opt.rect);

    // done
    painter->restore();
}


void IDSerialEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    QRect rect(option.rect);
    rect.adjust(7, 3, -7, -3);

    editor->setGeometry(rect);
}


void IDSerialEditDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
        QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
            ? QPalette::Normal : QPalette::Disabled;
        if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
            cg = QPalette::Inactive;

        painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Highlight));
    } else {
        painter->fillRect(option.rect, option.palette.brush(QPalette::Inactive, QPalette::Background));
    }
}