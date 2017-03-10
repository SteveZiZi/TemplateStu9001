#pragma once

#include "../driver/module.h"


#define MAX_HARMONIC_ORDER      31
struct HarmonicParam {
    float vol[MAX_HARMONIC_ORDER+1];  // 0、1无效  2~31对应谐波
    float cur[MAX_HARMONIC_ORDER+1];
};

class CHarmonicParam : public QObject
{
    Q_OBJECT

public:
    static CHarmonicParam* getInstance();

public:
    void harmonicParam(HarmonicParam* param);
    void setHarmonicParam(const HarmonicParam& param);

signals:
    void settingsChanged(const HarmonicParam&);

protected:
    CHarmonicParam(QObject* parent = 0);
    virtual ~CHarmonicParam(void);

private:
    void load(const QString& fileName);
    void save(const QString& fileName);

private:
    //没有找到寄存器的位置  暂时保存界面值
    HarmonicParam m_param;
    bool m_bInit;
};

