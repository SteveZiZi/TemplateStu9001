#pragma once


// #include "src\\DataManager\\driver\\module.h"
// #include "src\\DesignPattern\\Observe\\Observe.h"


bool drv_init(void);
void drv_deinit(void);

void drv_AttachObserverToWiringTemp(DObserver* observer);
void drv_DeattachObserverToWiringTemp(DObserver* observer);
int  drv_GetWiringTempHistoryDataCount();
bool drv_GetWiringTempHsitoryData(int nItem, tm_t* tm, WiringTempData_t* data);
void drv_GetWiringTempLastData(tm_t* tm, WiringTempData_t* data);

int  drv_GetTempHumHistoryDataCount();
bool drv_GetTempHumHistoryData(int nItem, tm_t* tm, TempHumData_t* data);
void drv_GetTempHumLastData(tm_t* tm, TempHumData_t* data);



