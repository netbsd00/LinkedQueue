#ifndef PACKET_DATA_TYPE_H
#define PACKET_DATA_TYPE_H

typedef unsigned char BYTE;
typedef int INT32;

typedef struct 
{
	BYTE cmd;
	BYTE *data;
	BYTE data_len;
} packet_t;
#endif //PACKET_DATA_TYPE_H

