#ifndef KEYS_H
#define KEYS_H

//ABP Credentials
uint8_t DEVADDR[4] = { 0x26, 0x0B, 0xB5, 0x40 };
uint8_t APPSKEY[16] = { 0x6A, 0x78, 0x7C, 0x69, 0x6B, 0xC5, 0xE7, 0x49, 0x69, 0x94, 0x96, 0xAD, 0x6C, 0x77, 0xD7, 0x8E };
uint8_t NWKSKEY[16] = { 0xAF, 0x3E, 0x60, 0xF0, 0xFC, 0x9C, 0x3D, 0x74, 0x16, 0xFF, 0x96, 0x6B, 0x68, 0xAB, 0xF3, 0x7D };


//OTAA Credentials
uint8_t DEVEUI[8] = { };
uint8_t APPEUI[8] = { };
uint8_t APPKEY[16] = { };

#endif