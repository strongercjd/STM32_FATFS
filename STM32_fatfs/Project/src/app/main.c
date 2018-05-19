#include "stm32f2xx.h"
#include "main.h"
#include "hard_bsp.h"
#include <stdio.h>
#include "Ex_Flash.h"
#include "ff.h"	


uint32 G_timeTicks;
uint32 sys_LED_state;
uint32 sys_LED_time;

FATFS fs1[_VOLUMES]; 
FIL fil;
FRESULT res;
UINT bww;
char buf[100];

/*!
* @brief main()
* @param 	NONE 
* @return	NONE
* @note
*/
int main(){
  uint8  uid[8];
  uint32 RDID_data;
  uint32 i;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  timer4Init();
  LED_Init();
  UART_Init();
  SPIInit();
  
  printf("\r\n======================================================================");
  printf("\r\n=               (C) COPYRIGHT 2018   zxbc1024                        =");
  printf("\r\n=                                                                    =");
  printf("\r\n=                ST207_Fatfs Program Demo                            =");
  printf("\r\n=                                                                    =");
  printf("\r\n=                                           By Firefly               =");
  printf("\r\n======================================================================");
  printf("\r\n\r\n");
  
  Ex_FLASH_ReadUID(uid);  
  printf("UID  of NOR Flash : %x%x%x%x%x%x%x%x\r\n",uid[0],uid[1],uid[2],uid[3],uid[4],uid[5],uid[6],uid[7]);
  RDID_data = Ex_FLASH_ReadID();
  printf("RDID of NOR Flash : %x",RDID_data);
  printf("\r\n\r\n");
  
  //Ex_FLASH_SectorErase(0);

  res=f_mount(&fs1[0],"0:",1);
  if(res != 0)
    res=f_mkfs("0:",1,4096);
  res=f_mount(&fs1[0],"0:",1); 
  res=f_open (&fil,"0:/message.txt", FA_CREATE_ALWAYS|FA_WRITE);	
  
  f_write (&fil, "onbon", 10, &bww);
  
  f_close(&fil);
  
  res=f_open (&fil,"0:/message.txt", FA_READ);
  
  f_read (&fil, buf,10,&bww);	
  f_close(&fil);
  
  printf("%s",buf);

  
  while(1){
    LED_ray_run();
  } 
}

