#include "driver.h"
#include "ComDriver.h"

static CComDriver s_drv;


bool drv_init(void)
{
    bool rc = s_drv.Init();

//exitCode:
    if (!rc) {
        drv_deinit();
    }
    return rc;
}

void drv_deinit(void)
{
    s_drv.Deinit();
}



void drv_AttachObserverToWiringTemp(DObserver* observer)
{
    s_drv.AttachObserverToWiringTemp(observer);
}

void drv_DeattachObserverToWiringTemp(DObserver* observer)
{
    s_drv.DeattachObserverToWiringTemp(observer);
}

int  drv_GetWiringTempHistoryDataCount()
{
    return s_drv.GetWiringTempHistoryDataCount();
}
bool drv_GetWiringTempHsitoryData(int nItem, tm_t* tm, WiringTempData_t* data)
{
    return s_drv.GetWiringTempHsitoryData(nItem, tm, data);
}
void drv_GetWiringTempLastData(tm_t* tm, WiringTempData_t* data)
{
    s_drv.GetWiringTempLastData(tm, data);
}

int  drv_GetTempHumHistoryDataCount()
{
    return s_drv.GetTempHumHistoryDataCount();
}
bool drv_GetTempHumHistoryData(int nItem, tm_t* tm, TempHumData_t* data)
{
    return s_drv.GetTempHumHistoryData(nItem, tm, data);
}
void drv_GetTempHumLastData(tm_t* tm, TempHumData_t* data)
{
    s_drv.GetTempHumLastData(tm, data);
}

