#include "stm32f2xx.h"
#include "main.h"
#include "hard_bsp.h"
#include <stdio.h>
#include "Ex_Flash.h"

uint32 G_timeTicks;
uint32 sys_LED_state;
uint32 sys_LED_time;


/*!
* @brief main()
* @param 	NONE 
* @return	NONE
* @note
*/
uint8 data[3*Ex_FLASH_SecSize];
uint8 data_cache[3*Ex_FLASH_SecSize];
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
  
  
  /*测试起始地址4k对齐，1个扇区的读写*/
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data[i] = 1;
  }
  Ex_FLASH_Write(2*Ex_FLASH_SecSize,data,Ex_FLASH_SecSize);
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD_Sec(2,data_cache);
  
  for(i=0;i<Ex_FLASH_SecSize;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<Ex_FLASH_SecSize){
    printf("Test NO.1  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.1  OK");
    printf("\r\n\r\n");
  }
  
  /*测试起始地址4k对齐，2个扇区的读写*/
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data[i] = 1;
  }
  for(i=0;i<10;i++)
  {
    data[i+Ex_FLASH_SecSize] = 2;
  }
  Ex_FLASH_Write(2*Ex_FLASH_SecSize,data,Ex_FLASH_SecSize+10);
  for(i=0;i<Ex_FLASH_SecSize*3;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD(2*Ex_FLASH_SecSize,data_cache,Ex_FLASH_SecSize+10);
  
  for(i=0;i<Ex_FLASH_SecSize+10;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<(Ex_FLASH_SecSize+10)){
    printf("Test NO.2  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.2  OK");
    printf("\r\n\r\n");
  }
  
  
  /*测试起始地址4k对齐，3个扇区的读写*/
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data[i] = 1;
  }
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data[i+Ex_FLASH_SecSize] = 2;
  }
  for(i=0;i<10;i++)
  {
    data[i+Ex_FLASH_SecSize*2] = 3;
  }
  Ex_FLASH_Write(2*Ex_FLASH_SecSize,data,Ex_FLASH_SecSize*3);
  for(i=0;i<Ex_FLASH_SecSize*3;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD(2*Ex_FLASH_SecSize,data_cache,Ex_FLASH_SecSize*3);
  
  for(i=0;i<Ex_FLASH_SecSize*3;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<(Ex_FLASH_SecSize*3)){
    printf("Test NO.3  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.3  OK");
    printf("\r\n\r\n");
  }
  
  
  /*测试起始地址不是4K对齐，1个扇区的读写*/
  for(i=0;i<10;i++)
  {
    data[i] = 1;
  }
  Ex_FLASH_Write(1*Ex_FLASH_SecSize-10,data,10);
  for(i=0;i<Ex_FLASH_SecSize*3;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD(1*Ex_FLASH_SecSize-10,data_cache,10);
  
  for(i=0;i<10;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<(10)){
    printf("Test NO.4  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.4  OK");
    printf("\r\n\r\n");
  }
  
  /*测试起始地址不是4K对齐，2个扇区的读写*/
  for(i=0;i<10;i++)
  {
    data[i] = 1;
  }
  for(i=0;i<10;i++)
  {
    data[i+10] = 2;
  }
  Ex_FLASH_Write(1*Ex_FLASH_SecSize-10,data,20);
  for(i=0;i<Ex_FLASH_SecSize*3;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD(1*Ex_FLASH_SecSize-10,data_cache,20);
  
  for(i=0;i<20;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<(20)){
    printf("Test NO.5  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.5  OK");
    printf("\r\n\r\n");
  }
  
  
  /*测试起始地址不是4K对齐，3个扇区的读写*/
  for(i=0;i<10;i++)
  {
    data[i] = 1;
  }
  for(i=0;i<Ex_FLASH_SecSize;i++)
  {
    data[i+10] = 2;
  }
  for(i=0;i<10;i++)
  {
    data[i+10+Ex_FLASH_SecSize] = 3;
  }
  Ex_FLASH_Write(1*Ex_FLASH_SecSize-10,data,Ex_FLASH_SecSize+20);
  for(i=0;i<Ex_FLASH_SecSize*3;i++)
  {
    data_cache[i] = 0;
  }
  Ex_Flash_RD(1*Ex_FLASH_SecSize-10,data_cache,Ex_FLASH_SecSize+20);
  
  for(i=0;i<Ex_FLASH_SecSize+20;i++){
    if(data_cache[i]!=data[i])break;  
  }
  if(i<(Ex_FLASH_SecSize+20)){
    printf("Test NO.6  Error");
    printf("\r\n\r\n");
  }else{
    printf("Test NO.6  OK");
    printf("\r\n\r\n");
  }
  
  while(1){
    LED_ray_run();
  } 
}

