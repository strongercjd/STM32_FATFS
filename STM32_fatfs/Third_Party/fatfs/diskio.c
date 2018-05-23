/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "Ex_Flash.h"

/* Definitions of physical drive number for each drive */
#define ATA		1	/* Example: Map ATA harddisk to physical drive 0 */
#define Ex_Flash	0	//外部串行NorFlash


#define FATFS_SECTOR_SIZE 	512	
#define FATFS_BLOCK_SIZE   	8         //每个BLOCK有8个扇区
#define FATFS_SECTOR_COUNT      2*1024*1024      //GD25Q16,前2M字节给FATFS占用

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case ATA :
		return stat;
        case Ex_Flash :
          result = Ex_FLASH_ReadID();
          
          stat =0;
          return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case ATA :
		return stat;
        case Ex_Flash :
          result = Ex_FLASH_ReadID();
          
          stat =0;
          return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;
        if (!count)
          return RES_PARERR;
	switch (pdrv) {
	case ATA :
		return res;
        case Ex_Flash:
          for(;count>0;count--)
          {
            Ex_Flash_RD(sector*FATFS_SECTOR_SIZE,buff,FATFS_SECTOR_SIZE);
            sector++;
            buff+=FATFS_SECTOR_SIZE;
          }
          res = RES_OK;
          return res;
	}


	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :
		return res;
        case Ex_Flash:
          for(;count>0;count--)
          {
            Ex_FLASH_Write(sector*FATFS_SECTOR_SIZE,(uint8_t*)buff,FATFS_SECTOR_SIZE);
            sector++;
            buff+=FATFS_SECTOR_SIZE;
          }
          res = 0;
          return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case ATA :
          
          // Process of the command for the ATA drive
          
          return res;
        case Ex_Flash:
          switch(cmd)
          {
          case CTRL_SYNC:
            res = RES_OK; 
            break;	 
          case GET_SECTOR_SIZE:
            *(WORD*)buff = FATFS_SECTOR_SIZE;
            res = RES_OK;
            break;	 
          case GET_BLOCK_SIZE:
            *(WORD*)buff = FATFS_BLOCK_SIZE;
            res = RES_OK;
            break;	 
          case GET_SECTOR_COUNT:
            *(DWORD*)buff = FATFS_SECTOR_COUNT;
            res = RES_OK;
            break;
          default:
            res = RES_PARERR;
            break;
          }
          return res;
	}

	return RES_PARERR;
}
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}
