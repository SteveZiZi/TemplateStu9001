#pragma once

#include <QtGlobal>
class QDateTime;

QString stu_getStyleSheetFromFile(QString fileName);

bool stu_setSystemTime(const QDateTime* dateTime);
bool stu_getSystemTime(QDateTime* dateTime);