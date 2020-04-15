#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define CONFIG_QMI_REPORT_PARAMS              "/home/weixw/QmiReportParamsFlag.conf"
#define CONFIG_SIGNAL_REPORT_REPEAT_NUMBER    "/home/weixw/SignalReportRpNum.conf"
#define CONFIG_SIGNAL_REPORT_AVGPRD           "/home/weixw/SignalReportAvgPrd.conf"
#define u32 unsigned int

using namespace std;

struct SignalReportCfg
{
    u32 rptRate;
    u32 avgPrd;
};

void readConfiguration(const char* confFile , const u32 defaultConfValue, u32 &confValue)
{
    cout << "config file is " << confFile << endl;
    std::ifstream l_readConfFile(confFile);
    
    if(l_readConfFile.is_open())
    {
        l_readConfFile>>confValue;
        cout << "In conf file, the value is: " << confValue << endl;
    }
    else
    {
        std::ofstream l_writeConfFile(confFile);
        l_writeConfFile<<defaultConfValue;
        confValue = defaultConfValue;
        cout<< "Set the value as default: " << confValue << endl;
    }
}

int main()
{
    SignalReportCfg defaultSignalReport = {1,5};
    u32 defaultSignalReportRpTime = 3;
    u32 defaultCfgQmiReport = true;
    u32 mConfigQmiReportParams;
    u32 mSignalReportRpNum;
    SignalReportCfg mSignalReportCfg;

    mSignalReportCfg.rptRate = defaultSignalReport.rptRate;
    
    readConfiguration(CONFIG_QMI_REPORT_PARAMS, defaultCfgQmiReport, mConfigQmiReportParams);

    readConfiguration(CONFIG_SIGNAL_REPORT_REPEAT_NUMBER,defaultSignalReportRpTime,mSignalReportRpNum);

    readConfiguration(CONFIG_SIGNAL_REPORT_AVGPRD,defaultSignalReport.avgPrd,mSignalReportCfg.avgPrd);
    
}


