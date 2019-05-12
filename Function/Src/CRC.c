/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of?
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.? See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file      CRC.h
 *  @version   1.0
 *  @date      May 2019
 *
 *  @brief     communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "CRC.h"
#include "CRC_ver.h"

//crc8 generator polynomial:G(x)=x8+x5+x4+1

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8)
{  
	unsigned char ucIndex;  
	while (dwLength--)  
	{  
		ucIndex = ucCRC8^(*pchMessage++);  
		ucCRC8 = CRC8_TAB[ucIndex];  
	}  
	return(ucCRC8);  
}

/**
 * @brief CRC8 Verify function
 * 
 * @param pchMessage Data to Verify
 * @param dwLength Stream length = Data + checksum
 * @return unsigned int True or False (CRC Verify Result)
 */
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength)  
{  
	unsigned char ucExpected = 0; 
	if ((pchMessage == 0) || (dwLength <= 2)) 
		return 0;  
	ucExpected = Get_CRC8_Check_Sum (pchMessage, dwLength-1, CRC8_INIT);  
	return ( ucExpected == pchMessage[dwLength-1] );  
} 

/**
 * @brief Append CRC8 to the end of data
 * 
 * @param pchMessage Data to CRC and append
 * @param dwLength Stream length = Data + checksum
 */
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength) 
{  
	unsigned char ucCRC = 0;  
	if ((pchMessage == 0) || (dwLength <= 2)) return;  
	ucCRC = Get_CRC8_Check_Sum ( (unsigned char *)pchMessage, dwLength-1, CRC8_INIT);  
	pchMessage[dwLength-1] = ucCRC;  
}

/**
 * @brief CRC16 checksum function
 * 
 * @param pchMessage Data to check
 * @param dwLength Stream length
 * @param wCRC Initialized checksum
 * @return unsigned short int CRC checksum
 */
unsigned short int Get_CRC16_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned short int wCRC)  
{  
	unsigned char chData;  
	if (pchMessage == NULL) return 0xFFFF;  
	while(dwLength--)  
	{  
		chData = *pchMessage++; 
		(wCRC) = ((unsigned short int)(wCRC) >> 8) ^ CRC16_TAB[((unsigned short int)(wCRC) ^ (unsigned short int)(chData)) & 0x00ff];  
	}  
	return wCRC;  
} 

/**
 * @brief CRC16 Verify function
 * 
 * @param pchMessage Data to Verify
 * @param dwLength Stream length = Data + checksum
 * @return unsigned int True or False (CRC Verify Result)
 */
unsigned int Verify_CRC16_Check_Sum(unsigned char *pchMessage, unsigned int dwLength)  
{  
	unsigned short int wExpected = 0;  
	if ((pchMessage == NULL) || (dwLength <= 2)) 
	{  
		return CRC_FALSE;  
	}  
	wExpected = Get_CRC16_Check_Sum ( pchMessage, dwLength - 2, CRC16_INIT);  
	return ((wExpected & 0xff) == pchMessage[dwLength - 2] && ((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]);  
}

/**
 * @brief Append CRC16 to the end of data
 * 
 * @param pchMessage Data to CRC and append
 * @param dwLength Stream length = Data + checksum
 */
void Append_CRC16_Check_Sum(unsigned char * pchMessage,unsigned int dwLength)  
{  
	unsigned short int wCRC = 0;  
	if ((pchMessage == NULL) || (dwLength <= 2)) return;
	wCRC = Get_CRC16_Check_Sum ( (unsigned char *)pchMessage, dwLength-2, CRC16_INIT );
	pchMessage[dwLength-2] = (unsigned char)(wCRC & 0x00ff);  pchMessage[dwLength-1] = (unsigned char)((wCRC >> 8)& 0x00ff);
}
