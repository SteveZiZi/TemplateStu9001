#include "stu9001.h"
#include <QtGui/QApplication>
#include <QtGui>

#include <stu_utility>

#include "debug.h"


class NoFocusRectangleStyle: public QCommonStyle
{
public:

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
        QPainter *painter, const QWidget *widget) const
    {
        if (QStyle::PE_FrameFocusRect == element)
        {
            return;
        }
        else
            QCommonStyle::drawPrimitive(element, option, painter, widget);
    }
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new NoFocusRectangleStyle());
    Q_INIT_RESOURCE(stu9001);

    //¼ÓÔØÓïÑÔ°ü
    QTranslator translator;
    bool b = false;
    b = translator.load("stu9001_zh.qm");
    a.installTranslator(&translator);

    qApp->setStyleSheet(stu_getStyleSheetFromFile(":/Stu9001/stu9001.qss"));

    Stu9001 w;
    w.show();
    return a.exec();
}
