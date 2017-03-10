#pragma once

#include "../driver/module.h"


#define MAX_HARMONIC_ORDER      31
struct HarmonicParam {
    float vol[MAX_HARMONIC_ORDER+1];  // 0��1��Ч  2~31��Ӧг��
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
    //û���ҵ��Ĵ�����λ��  ��ʱ�������ֵ
    HarmonicParam m_param;
    bool m_bInit;
};

