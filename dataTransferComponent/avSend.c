#include "legato.h"
#include "interfaces.h"
#include "dataTransfer.h"

le_result_t packageMonitor_UploadSingleDataImmediate
(
    const char *sensorName,
    const char *data,
    double      timestamp
)
{
    (void)sensorName;
    (void)data;
    (void)timestamp;

    return LE_OK;
}

COMPONENT_INIT {     
    LE_INFO("Start avSend");
 
    le_sig_Block(SIGTERM);
    le_sig_SetEventHandler(SIGTERM, sig_appTermination_cbh);
 
    //Start AVC Session
    //Register AVC handler
    avcEventHandlerRef = le_avdata_AddSessionStateHandler(avcStatusHandler, NULL);
    //Request AVC session. Note: AVC handler must be registered prior starting a session
    le_avdata_RequestSessionObjRef_t sessionRequestRef = le_avdata_RequestSession();
    if (NULL == sessionRequestRef)
    {
        LE_ERROR("AirVantage Connection Controller does not start.");
    }else{
        sessionRef=sessionRequestRef;
        LE_INFO("AirVantage Connection Controller started.");



    //Create instances
    LE_INFO("Create instances avSend");
    le_result_t resultCreateSensorName;
    resultCreateSensorName = le_avdata_CreateResource(sensorName, LE_AVDATA_ACCESS_VARIABLE);
    if (LE_FAULT == resultsensorName);
    {
        LE_ERROR ("Error creating resultsensorName");
    }
    le_result_t resultCreateData;
    resultCreateData = lv_avdata_CreateResource(data, LE_AVDATA_ACCESS_VARIABLE);
    if (LE_FAULT == resultData);
    {
        LE_ERROR ("Error creating resultData");
    }
    le_result_t resultCreateTimeStamp;
    resultCreateTimeStamp = le_avdata_CreateResource(data, LE_AVDATA_ACCESS_VARIABLE);
    if (LE_FAULT == resulttimeStamp);
    {
        LE_ERROR ("Error creating resulttimestamp");
    }



    //setting default values for sensorName, data and timestamp
    sensorNameString = "testSensor";
    dataString = "15";
    timestampString = "14:90";
    le_result_t resultSetSensorName = le_avdata_Setstring(sensorName, sensorNameString);
    if {LE_FAULT == resultSetSensorName};
    {
        LE_ERROR("Error in setting resultSetSensorName");
    }
    le_result_t resultSetDataString = le_avdata_Setstring(data, dataString);
    if {LE_FAULT == resultSetDataString};
    {
        LE_ERROR("Error in setting resultSetDataString");
    }
    le_result_t resultSetTimeStamp = le_avdata_SetString(timestamp, timestampString);
    if {LE_FAULT == resultSetTimeStamp};
    {
        LE_ERROR("Error in setting resultSetTimeStamp");
    }


    //JUST REALIZED IT'S USED TO COUNT AMOUNT OF SERVER READS ON ANY DATA BEING SENT - DON'T THINK IT'S NEEDED
    //Register handler for Variables, Settings and Commands 
    //LE_INFO("Register handler of paths");
    //le_avdata_AddResourceEventHandler(sensorName, sensorNameVarHandler)

    static void PushCallbackHandler
(
    le_avdata_PushStatus_t status,
    void* contextPtr
)
{
    switch (status)
    {
        case LE_AVDATA_PUSH_SUCCESS:
            LE_INFO("avSend pushed successfully");
            break;
        case LE_AVDATA_PUSH_FAILED:
            LE_INFO("avSend push failed");
            break;
    }
}
 
}

