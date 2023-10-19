#define SYS_REG_BASE 0x0000

//Address of System Registers
#define I80CPCR (SYS_REG_BASE + 0x04)

//Memory Converter Registers
#define MCSR_BASE_ADDR 0x0200
#define MCSR  (MCSR_BASE_ADDR + 0x0000)
#define LISAR (MCSR_BASE_ADDR + 0x0008)


/*
void EPD_IT8951_SystemRun();
void EPD_IT8951_Standby();
void EPD_IT8951_Sleep();

UWORD EPD_IT8951_ReadReg(UWORD Reg_Address);
void EPD_IT8951_WriteReg(UWORD Reg_Address,UWORD Reg_Value);
UWORD EPD_IT8951_GetVCOM(void);
void EPD_IT8951_SetVCOM(UWORD VCOM);

void EPD_IT8951_LoadImgStart( IT8951_Load_Img_Info* Load_Img_Info );
void EPD_IT8951_LoadImgAreaStart( IT8951_Load_Img_Info* Load_Img_Info, IT8951_Area_Img_Info* Area_Img_Info );
void EPD_IT8951_LoadImgEnd(void);

void EPD_IT8951_GetSystemInfo(void* Buf);
void EPD_IT8951_SetTargetMemoryAddr(UDOUBLE Target_Memory_Addr);
void EPD_IT8951_WaitForDisplayReady(void);


void EPD_IT8951_HostAreaPackedPixelWrite_8bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info);

void EPD_IT8951_HostAreaPackedPixelWrite_1bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info, bool Packed_Write);

void EPD_IT8951_HostAreaPackedPixelWrite_2bp(IT8951_Load_Img_Info*Load_Img_Info,IT8951_Area_Img_Info*Area_Img_Info, bool Packed_Write);

void EPD_IT8951_Display_Area(UWORD X,UWORD Y,UWORD W,UWORD H,UWORD Mode);
void EPD_IT8951_Display_AreaBuf(UWORD X,UWORD Y,UWORD W,UWORD H,UWORD Mode, UDOUBLE Target_Memory_Addr);

void EPD_IT8951_Display_1bp(UWORD X, UWORD Y, UWORD W, UWORD H, UWORD Mode,UDOUBLE Target_Memory_Addr, UBYTE Front_Gray_Val, UBYTE Back_Gray_Val);
*/

void Enhance_Driving_Capability(void);

void EPD_IT8951_SystemRun(void);

void EPD_IT8951_Standby(void);

void EPD_IT8951_Sleep(void);

IT8951_Dev_Info EPD_IT8951_Init(UWORD VCOM);

void EPD_IT8951_Clear_Refresh(IT8951_Dev_Info Dev_Info,UDOUBLE Target_Memory_Addr, UWORD Mode);

void EPD_IT8951_1bp_Refresh(UBYTE* Frame_Buf, UWORD X, UWORD Y, UWORD W, UWORD H, UBYTE Mode, UDOUBLE Target_Memory_Addr, bool Packed_Write);
void EPD_IT8951_1bp_Multi_Frame_Write(UBYTE* Frame_Buf, UWORD X, UWORD Y, UWORD W, UWORD H,UDOUBLE Target_Memory_Addr, bool Packed_Write);
void EPD_IT8951_1bp_Multi_Frame_Refresh(UWORD X, UWORD Y, UWORD W, UWORD H,UDOUBLE Target_Memory_Addr);

void EPD_IT8951_2bp_Refresh(UBYTE* Frame_Buf, UWORD X, UWORD Y, UWORD W, UWORD H, bool Hold, UDOUBLE Target_Memory_Addr, bool Packed_Write);

void EPD_IT8951_4bp_Refresh(UBYTE* Frame_Buf, UWORD X, UWORD Y, UWORD W, UWORD H, bool Hold, UDOUBLE Target_Memory_Addr, bool Packed_Write);

void EPD_IT8951_8bp_Refresh(UBYTE *Frame_Buf, UWORD X, UWORD Y, UWORD W, UWORD H, bool Hold, UDOUBLE Target_Memory_Addr);



#endif
