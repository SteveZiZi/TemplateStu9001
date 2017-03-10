#include "MenuContentMgr.h"
#include <AbstractMenu>

#include "common.h"

#include ".\dialog\systemParam\systemInfoDialog.h"
#include ".\dialog\systemParam\passwordDialog.h"
#include ".\dialog\systemParam\networkSettingDialog.h"
#include ".\dialog\systemParam\timeSettingDialog.h"
#include ".\dialog\systemParam\simulationViewsDialog.h"

#include ".\dialog\energyParam\measureParamDialog.h"
#include ".\dialog\energyParam\harmonicsParamDialog.h"
#include ".\dialog\energyParam\wireTypesParamDialog.h"

#include ".\dialog\TempHumParam\wiringMeasureTempParamDialog.h"
#include ".\dialog\TempHumParam\wiringIdSerialDialog.h"
#include ".\dialog\TempHumParam\tempHumParamDialog.h"

#include ".\dialog\machineCharacteristic\machineCharactristicParamDialog.h"
#include ".\dialog\motorParam\motorParamDialog.h"

#include ".\dialog\dataShow\measureShowDialog.h"
#include ".\dialog\dataShow\sampleShowDialog_cp9000.h"
#include ".\dialog\dataShow\sampleShowDialog_cp6000.h"
#include ".\dialog\dataShow\switchInShowDialog.h"
#include ".\dialog\dataShow\tempHumShowDialog.h"

#include ".\dialog\constValueSettings\constValueModifyDialog_cp9000.h"
#include ".\dialog\constValueSettings\plateCastBackDialog_cp9000.h"
#include ".\dialog\constValueSettings\castbackConstValueSettingsDialog_cp6000.h"

#include ".\dialog\ElecOperator/elecOperatorDialog.h"

#include "./dialog/Trend/wiringMeasureTempTrendDialog.h"
#include "./dialog/Trend/cubicleTempHumTrendDialog.h"
#include "./dialog/Trend/machineCharactristicTrendDialog.h"
#include "./dialog/Trend/harmonicTrendDialog.h"

#include "./dialog/eventReport/eventReportDialog.h"

#include <stu_config>

#include "debug.h"

CMenuContentMgr::CMenuContentMgr()
{
    m_parent = NULL;
}

CMenuContentMgr::~CMenuContentMgr()
{
    RemoveContent();
}


CMenuContentMgr* CMenuContentMgr::GetInstance()
{
    static CMenuContentMgr menuMap;
    return &menuMap;
}

CAbstractMenuContent* CMenuContentMgr::GetMenuContent(quint32 pageID)
{
    CMenuContentMgr* inst = GetInstance();

    mapMenuContent::Iterator it= inst->m_menuContent.find(pageID);
    if (it != inst->m_menuContent.end()) {
        return it.value();
    }

    return inst->CreateContent(pageID);
}

CAbstractMenuContent* CMenuContentMgr::CreateContent(quint32 pageID)
{
    switch(pageID) 
    {
    case STU_SYSTEM_CONFIG_CONTENT:
        return new CSystemInfoDlg(m_parent);
        break;
	case STU_SET_PASSWORD_CONTENT:
		return new CPasswordDlg(m_parent);
		break;
    case STU_NETWORK_SETTINGS_CONTENT:
        return new CNetworkSettingDlg(m_parent);
        break;
    case STU_TIME_SETTINGS_CONTENT:
        return new CTimeSettingDlg(m_parent);
        break;
    case STU_SIMULATION_VIEWS_CONTENT:
        return new CSimulationViewsDlg(m_parent);
        break;

    case STU_MEASURE_PARAM_CONTENT:
        return new CMeasureParamDlg(m_parent);
        break;
    case STU_HARNOICS_PARAM_CONTENT:
        return new CHarnoicsParamDlg(m_parent);
        break;
    case STU_WIRING_TYPES_CONTENT:
        return new CWireTypesParamDlg(m_parent);
        break;

    case STU_WIRING_MEASURE_TEMP_PARAM_CONTENT:
        return new CWiringMeasureTempParamDlg(m_parent);
        break;
    case STU_WIRING_ID_SERIAL_CONTENT:
        return new CWiringIdSerialDlg(m_parent);
        break;
    case STU_TH1_CONTENT:
    case STU_TH2_CONTENT:
        return new CTempHumParamDlg(m_parent);
        break;

    case STU_MACHINE_CHARACTRISTIC_PARAM_CONTENT:
        return new CMachineCharactristicParamDlg(m_parent);
        break;

    case STU_MOTOR_PARAM_CONTENT:
        return new CMotorParamDlg(m_parent);
        break;

    case STU_MEASURE_SHOW_CONTENT:
        return new CMeasureShowDlg(m_parent);
        break;
    case STU_SAMPLE_SHOW_CONTENT:
        if (stu_config::isCP9000())
            return new CCP9000SampleShowDlg(m_parent);
        else
            return new CCP6000SampleShowDlg(m_parent);
        break;
    case  STU_SWITCH_IN_SHOW_CONTENT:
        return new CSwitchInShowDlg(m_parent);
        break;
    case STU_TEMP_HUM_SHOW_CONTENT:
        return new CTempHumShowDlg(m_parent);
        break;

    case STU_CONST_VALUE_MODIFY_CONTENT:
        return new CConstValueModifyDlg(m_parent);
        break;
    case STU_PLATE_CASTBACK_CONTENT:
        return new CPlateCastBackDlg(m_parent);
        break;
    case STU_CASTBACK_CONST_VALUE_CONTENT:
        return new CCastbackConstValueCP6000Dlg(m_parent);
        break;

    case STU_ELEC_OPERATOR_CONTENT:
        return new CElecOperatorDlg(m_parent);
        break;

    case STU_WIRING_MEASURE_TEMP_TREND_CONTENT:
        return new CWiringMeasureTempTrendDlg(m_parent);
        break;
    case STU_CUBICLE_TEMP_HUM_TREND_CONTENT:
        return new CCubicleTempHumTrendDlg(m_parent);
        break;
    case STU_MACHINE_CHARACTRISTIC_TREND_CONTENT:
        return new CMachineCharactristicTrendDlg(m_parent);
        break;
    case STU_HARNOICS_PARAM_TREND_CONTENT:
        return new CHarmonicTrendDlg(m_parent);
        break;

    case STU_EVENT_REPORT_CONTENT:
        return new CEventReportDlg(m_parent);
        break;
		
    default:
        Q_ASSERT(NULL);
        break;
    }

    return NULL;
}

void CMenuContentMgr::RemoveContent()
{
    for(mapMenuContent::Iterator it = m_menuContent.begin(); it != m_menuContent.end(); it++)
    {
        delete it.value();
    }
}

void CMenuContentMgr::SetMainDlg(QWidget* main)
{
    m_parent = main;
}
