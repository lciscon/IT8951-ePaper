#include "../lib/Config/DEV_Config.h"
#include "../lib/Wacom/BasicTypes.h"
#include "example.h"
#include "../lib/GUI/GUI_BMPfile.h"
#include "../lib/GUI/GUI_Paint.h"
#include "../lib/Wacom/WacomI2CHandler.h"

#include <math.h>

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()

#define Enhance false

#define USE_Factory_Test false

#define USE_Normal_Demo true

#define USE_Touch_Panel false

UWORD VCOM = 2050;

const int TABLET_I2C_ADDRESS = 9;

WacomI2CHandler *tabletHandler;

struct DeviceInfo deviceInfo;

struct TabletData tabletData;

IT8951_Dev_Info Dev_Info = {0, 0};
UWORD Panel_Width;
UWORD Panel_Height;
UDOUBLE Init_Target_Memory_Addr;
int epd_mode = 0;	//0: no rotate, no mirror
					//1: no rotate, horizontal mirror, for 10.3inch
					//2: no totate, horizontal mirror, for 5.17inch
					//3: no rotate, no mirror, isColor, for 6inch color
					
void  Handler(int signo){
    
    Debug("\r\nHandler:exit\r\n");
    if(Refresh_Frame_Buf != NULL){
        free(Refresh_Frame_Buf);
        Debug("free Refresh_Frame_Buf\r\n");
        Refresh_Frame_Buf = NULL;
    }
    if(Panel_Frame_Buf != NULL){
        free(Panel_Frame_Buf);
        Debug("free Panel_Frame_Buf\r\n");
        Panel_Frame_Buf = NULL;
    }
    if(Panel_Area_Frame_Buf != NULL){
        free(Panel_Area_Frame_Buf);
        Debug("free Panel_Area_Frame_Buf\r\n");
        Panel_Area_Frame_Buf = NULL;
    }
    if(bmp_src_buf != NULL){
        free(bmp_src_buf);
        Debug("free bmp_src_buf\r\n");
        bmp_src_buf = NULL;
    }
    if(bmp_dst_buf != NULL){
        free(bmp_dst_buf);
        Debug("free bmp_dst_buf\r\n");
        bmp_dst_buf = NULL;
    }
	if(Dev_Info.Panel_W != 0){
		Debug("Going to sleep\r\n");
		//EPD_IT8951_Sleep();
	}
    DEV_Module_Exit();
    exit(0);
}


//-------------------------------------------------------------------------------------------------
// ::paintBrush
//
/**
 * 
 * Paint the brush at a specific point on the screen.
 * 
 */

int paintBrush(double X_Center, double Y_Center, double Radius, bool touchDown) {

    Paint_DrawCircle(X_Center, Y_Center, Radius, 0x50, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    EPD_IT8951_8bp_Refresh(Refresh_Frame_Buf, 0, 0, Panel_Width,  Panel_Height, false, Init_Target_Memory_Addr);

}

//-------------------------------------------------------------------------------------------------
// ::handleTasks
//
/**
 * 
 * Handles all runtime tasks such as polling the tablet and updating the mouse status.
 * 
 */

int handleTasks() {

    int i = 0;

    while(1){
        
        tabletHandler->queryPenData();

        paintBrush(tabletData.transformedX, tabletData.transformedY, 20, tabletData.touchDown);

        if(deviceInfo.refreshRateUS > 0){
            usleep(deviceInfo.refreshRateUS);
        }

    }

    return 0;

}// end of ::HandleTasks


int main(int argc, char *argv[])
{
    //Exception handling:ctrl + c
    signal(SIGINT, Handler);
    int screen = 1;

    if (argc < 2){
        Debug("Please input which screen to control (1-3)\r\n");
        Debug("Example: sudo ./epd 1\r\n");
        exit(1);
    }

    //Init the BCM2835 Device
    if(DEV_Module_Init()!=0){
        return -1;
    }

    sscanf(argv[1],"%d",&screen);

    if (argc > 2) {
        double temp;
        sscanf(argv[2],"%lf",&temp);
        VCOM = (UWORD)(fabs(temp)*1000);
    }

    if (argc > 3) {
	    sscanf(argv[3],"%d",&epd_mode);
    }

    Debug("\r\nDisplay screen:%d\r\n",screen);
    Debug("VCOM value:%d\r\n", VCOM);
    Debug("Display mode:%d\r\n", epd_mode);

    swapSCREEN(screen);   //select the screen IO pins
    Dev_Info = EPD_IT8951_Init(VCOM);           // must reinitalize to work properly after swap I don't think all of the routines in this function are necessary here, it currently takes a few seconds for this funciton to run

    tabletHandler = new WacomI2CHandler(&deviceInfo, &tabletData);
    tabletHandler->init();

    tabletHandler->start(deviceInfo.i2cBusName.c_str(), TABLET_I2C_ADDRESS);

    tabletHandler->queryDeviceInfo();

    //get some important info from Dev_Info structure
    Panel_Width = Dev_Info.Panel_W;
    Panel_Height = Dev_Info.Panel_H;
    Init_Target_Memory_Addr = Dev_Info.Memory_Addr_L | (Dev_Info.Memory_Addr_H << 16);
    char* LUT_Version = (char*)"M841_TFA2812";
    Debug("LUT Mod Version = %s\r\n", LUT_Version);
    A2_Mode = 6;
    Debug("A2 Mode:%d\r\n", A2_Mode);

    //clear the screen
	EPD_IT8951_Clear_Refresh(Dev_Info, Init_Target_Memory_Addr, INIT_Mode);

    //display the background
    Display_BMP_Example(UWORD Panel_Width, Panel_Height, Init_Target_Memory_Addr, BitsPerPixel_4);

    //process the loop
    handleTasks();
    TouchPanel_ePaper_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr);


    //We recommended refresh the panel to white color before storing in the warehouse.
    EPD_IT8951_Clear_Refresh(Dev_Info, Init_Target_Memory_Addr, INIT_Mode);

    tabletHandler->stop();

    //EPD_IT8951_Standby();
    //EPD_IT8951_Sleep();

    //In case RPI is transmitting image in no hold mode, which requires at most 10s
    DEV_Delay_ms(5000);

    DEV_Module_Exit();
    return 0;
}
