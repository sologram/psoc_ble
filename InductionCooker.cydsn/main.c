/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#include "cooker.h"

#include <stdio.h>
#include <stdlib.h>

int _write(int file, char *ptr, int len)
{
    int i;
    file = file;
    for (i = 0; i < len; i++)
    {
        UART_DEB_UartPutChar(*ptr++);
    }
    return len;
}


void StackEventHandler( uint32 eventCode, void *eventParam );


CYBLE_GATT_HANDLE_VALUE_PAIR_T      cmdHandle;


void Sensor_Notify() {
    
        CYBLE_GATT_HANDLE_VALUE_PAIR_T powerHandle;
        sensorData[0] = StatusBuffer[1];
        sensorData[1] = StatusBuffer[2];
        sensorData[2] = StatusBuffer[4];
        
        powerHandle.attrHandle = CYBLE_INDUCTION_SERVICE_SENSOR_CHARACTERISTIC_CHAR_HANDLE;
        powerHandle.value.val = sensorData;
        powerHandle.value.len = 3;
        powerHandle.value.actualLen = 3;                
 
        CyBle_GattsNotification(cyBle_connHandle, &powerHandle);
        memset(sensorData, 0, 3);
}

void blink()
{
        Advertising_LED_Write(~Advertising_LED_Read());
}

CY_ISR(SendFrameHandler) {
    blink();
  
    //clear pending

//    cmd_loop();
//    Sensor_Notify();  
    
    Timer_1_GetInterruptSource();
    
}

CY_ISR_PROTO(SendFrameHandler); 

void Initialize() 
{
    CyGlobalIntEnable;   /* Enable global interrupts */    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
        
    CyBle_Start( StackEventHandler );
    I2C_scl_SetDriveMode(I2C_scl_DM_RES_UP);
    I2C_sda_SetDriveMode(I2C_sda_DM_RES_UP);
    I2C_Start();
    UART_DEB_Start();
//    ISR_Frame_StartEx(SendFrameHandler);
//    Timer_1_Start();
//    Timer_1_Enable();

}


int main()
{
    Initialize();
    for(;;)
    {     
//        blink();
         cmd_loop();
         Sensor_Notify();

/*      
        
        int i;
        char byte;
        for (i = 0; i < STATUS_BUF_LEN; i++)
        {
            
            sprintf(&byte, "%c", StatusBuffer[i]);
            UART_DEB_UartPutChar(byte);
        }
*/       
        
        CyBle_ProcessEvents();
    }
}

void StackEventHandler( uint32 eventCode, void *eventParam )
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    switch( eventCode )
    {
        /* Generic events */

        case CYBLE_EVT_HOST_INVALID:
        break;

        case CYBLE_EVT_STACK_ON:
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST ); 
            
        break;

        case CYBLE_EVT_TIMEOUT:
        break;

        case CYBLE_EVT_HARDWARE_ERROR:
        break;

        case CYBLE_EVT_HCI_STATUS:
        break;

        case CYBLE_EVT_STACK_BUSY_STATUS:
        break;

        case CYBLE_EVT_PENDING_FLASH_WRITE:
        break;


        /* GAP events */

        case CYBLE_EVT_GAP_AUTH_REQ:
        break;

        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
        break;

        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
        break;

        case CYBLE_EVT_GAP_AUTH_COMPLETE:
        break;

        case CYBLE_EVT_GAP_AUTH_FAILED:
        break;

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
        break;

        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST); 
        break;

        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
        break;

        case CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:
        break;

        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
        break;


        /* GAP Peripheral events */

        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
        break;


        /* GAP Central events */

        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
        break;

        case CYBLE_EVT_GAPC_SCAN_START_STOP:
        break;


        /* GATT events */

        case CYBLE_EVT_GATT_CONNECT_IND:
        break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
        break;


        /* GATT Client events (CYBLE_EVENT_T) */

        case CYBLE_EVT_GATTC_ERROR_RSP:
        break;

        case CYBLE_EVT_GATTC_XCHNG_MTU_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_INFO_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BLOB_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_MULTI_RSP:
        break;

        case CYBLE_EVT_GATTC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_EXEC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_IND:
        break;


        /* GATT Client events (CYBLE_EVT_T) */

        case CYBLE_EVT_GATTC_INDICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_SRVC_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_CHAR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_DESCR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
        break;


        /* GATT Server events (CYBLE_EVENT_T) */

        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
        break;
        
        case CYBLE_EVT_GATTS_WRITE_REQ:
            /*
            wrReqParam =  (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            
            gpioHandle.attrHandle = CYBLE_TOGGLE_SERVICE_TOGGLE_CHARACTERISTIC_CHAR_HANDLE;
            
            gpioHandle.value.val = wrReqParam->handleValPair.value.val;
            gpioHandle.value.len = wrReqParam->handleValPair.value.len;
            gpioHandle.value.actualLen = wrReqParam->handleValPair.value.actualLen;

            CyBle_GattsWriteAttributeValue(&gpioHandle, FALSE, &cyBle_connHandle, FALSE);
//            Gpio_Toggle(*gpioHandle.value.val);
            CyBle_GattsWriteRsp(cyBle_connHandle);
            */
            
            wrReqParam =  (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            
//            gpioHandle.attrHandle = CYBLE_TOGGLE_SERVICE_TOGGLE_CHARACTERISTIC_CHAR_HANDLE;
            
//            gpioHandle.value.val = wrReqParam->handleValPair.value.val;
//            gpioHandle.value.len = wrReqParam->handleValPair.value.len;
//            gpioHandle.value.actualLen = wrReqParam->handleValPair.value.actualLen;

//            CyBle_GattsWriteAttributeValue(&gpioHandle, FALSE, &cyBle_connHandle, FALSE);
//            Gpio_Toggle(*gpioHandle.value.val);
            
            if (wrReqParam->handleValPair.attrHandle == CYBLE_INDUCTION_SERVICE_POWERCONTROL_CHARACTERISTIC_CHAR_HANDLE) {
//                char byte[2];
                CURRENT_CMD = *(wrReqParam->handleValPair.value.val); 
                if (CURRENT_CMD == SET_POWER) {
                    CMD_PARAM = *(wrReqParam->handleValPair.value.val+1);
                }
                
//                sprintf(&byte, "%x", CMD_PARAM);
//                UART_DEB_UartPutChar(byte[0]);
//                UART_DEB_UartPutChar(byte[1]);
            }
            
            CyBle_GattsWriteRsp(cyBle_connHandle);
            
            
        break;

        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        break;

        case CYBLE_EVT_GATTS_PREP_WRITE_REQ:

            
        break;

        case CYBLE_EVT_GATTS_EXEC_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
        break;

        case CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ:
        break;


        /* GATT Server events (CYBLE_EVT_T) */

        case CYBLE_EVT_GATTS_INDICATION_ENABLED:
        break;

        case CYBLE_EVT_GATTS_INDICATION_DISABLED:
        break;


        /* L2CAP events */

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ:
        break;

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
        break;

        case CYBLE_EVT_L2CAP_COMMAND_REJ:
        break;

        case CYBLE_EVT_L2CAP_CBFC_CONN_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_CONN_CNF:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DISCONN_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DATA_READ:
        break;

        case CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND:
        break;


        /* default catch-all case */

        default:
        break;
    }
}
