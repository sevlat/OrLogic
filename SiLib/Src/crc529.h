#ifndef crc529_h_already_included__19_05_2012__1CED18C0
#define crc529_h_already_included__19_05_2012__1CED18C0
//
// SeVlaT, 19.05.2012
//

// SportIdent CRC function declaration

//***************************************************************************
//** Autor: Jürgen Ehms
//** 
//** Filename: crc529.c
//** 
//** Description: Programm to generate 16 BIT CRC
//** 
//** Return values: 16 BIT CRC
//** 
//** Errormessages: none
//** 
//** Version    last change    description
//** 
//** 1.00       07.09.2004  
//***************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

unsigned int crc(unsigned int uiCount, const unsigned char *pucDat);

#ifdef __cplusplus
}
#endif

#endif
