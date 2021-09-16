#include <assert.h>/*assert*/

#include "bit_array.h"

const int UNSIGNED_LONG_SIZE = 64;
const unsigned long MAX_BIT_ARR = 0xFFFFFFFFFFFFFFFF;

const char LUT[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2,
 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3,
 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3,
 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2,
 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5,
 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3,
 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3,
 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4,
 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6,
 7, 7, 8};

static const unsigned char LUTMirror[256] = {0, 128, 64, 192, 32, 160, 96, 224,
 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24,
 152, 88, 216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148,
 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92,
 220, 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210,
 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58,
 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182,
 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126,
 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241,
 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5,
 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141,
 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67,
 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203,
 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39,
 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175,
 111, 239, 31, 159, 95, 223, 63, 191, 127, 255};

int BArrIsBitOn(unsigned long bit_arr, int idx)
{		
	assert(idx >= 0 && idx < UNSIGNED_LONG_SIZE);		

	return ((bit_arr >> idx) & 1);
}

int BArrIsBitOff(unsigned long bit_arr, int idx)
{
	assert(idx >= 0 && idx < UNSIGNED_LONG_SIZE);	
	
	return (!((bit_arr >> idx) & 1));
}

int BArrCountBitsOn(unsigned long bit_arr)
{
	unsigned long temp = 0ul;
	int count = 0;	
		
	while(0 != bit_arr)
	{
		temp = bit_arr - 1ul;
		bit_arr &= temp;
		++count;
	}
	
	return count;
}

int BArrCountBitsOnWithLUT(unsigned long bit_arr)
{
	int count = 0;
	unsigned long mask = 0x00000000000000FF;
	
	while(0 != bit_arr)
	{
		count += LUT[(bit_arr & mask)];
		bit_arr >>= 8;
	}

	return count; 
}

int BArrCountBitsOff(unsigned long bit_arr)
{
	return UNSIGNED_LONG_SIZE - BArrCountBitsOn(bit_arr);
}

unsigned long BArrSetBitOn(unsigned long bit_arr, int idx)
{
	unsigned long mask = 1ul ;
		
	assert(idx >= 0 && idx < UNSIGNED_LONG_SIZE);	

	mask <<= idx;
	
	return (bit_arr | mask);
}

unsigned long BArrSetBitOff(unsigned long bit_arr, int idx)
{
	unsigned long mask = 1ul ;
		
	assert(idx >= 0 && idx < UNSIGNED_LONG_SIZE);	

	mask <<= idx;
	
	return (bit_arr & ~mask);
}

unsigned long BArrGetBitArrayOn()
{
	return MAX_BIT_ARR;
}

unsigned long BArrGetBitArrayOff()
{
	return 0;
}

int BArrAreAllBitsOn(unsigned long bit_arr)
{
	return (bit_arr == BArrGetBitArrayOn());
}

int BArrAreAllBitsOff(unsigned long bit_arr)
{
	return (bit_arr == BArrGetBitArrayOff());
}

unsigned long BArrFlipOneBit(unsigned long bit_arr, int idx)
{	
	unsigned long mask = 1ul;

	assert(idx >= 0 && idx < UNSIGNED_LONG_SIZE);	

	mask <<= idx;
		
	return (bit_arr ^= mask);
}

unsigned long BArrFlipAllBits(unsigned long bit_arr)
{
	return (bit_arr ^ MAX_BIT_ARR);
}

unsigned long BArrRotateBitsRight(unsigned long bit_arr, int rot_time)
{
	unsigned long temp = bit_arr;
	
	assert(rot_time >= 0);

	temp <<= (UNSIGNED_LONG_SIZE - (rot_time % UNSIGNED_LONG_SIZE));
	bit_arr >>= rot_time;
	
	return (bit_arr | temp); 
}

unsigned long BArrRotateBitsLeft(unsigned long bit_arr, int rot_time)
{
	unsigned long temp = bit_arr;	

	assert(rot_time >= 0);

	temp >>= (UNSIGNED_LONG_SIZE - (rot_time % UNSIGNED_LONG_SIZE));
	bit_arr <<= rot_time;
	
	return (bit_arr | temp);
}

unsigned long BArrMirrorBitArr(unsigned long bit_arr)
{
	bit_arr = bit_arr >> 32 | bit_arr << 32 ;
	bit_arr = (bit_arr & 0xFFFF0000FFFF0000) >> 16 | 
					(bit_arr & 0x0000FFFF0000FFFF) << 16;
	bit_arr = (bit_arr & 0xFF00FF00FF00FF00) >> 8 | 
					(bit_arr & 0x00FF00FF00FF00FF) << 8;
	bit_arr = (bit_arr & 0xF0F0F0F0F0F0F0F0) >> 4 | 
					(bit_arr & 0x0F0F0F0F0F0F0F0F) << 4;
	bit_arr = (bit_arr & 0xCCCCCCCCCCCCCCCC) >> 2 | 
					(bit_arr & 0x3333333333333333) << 2;
	bit_arr = (bit_arr & 0xAAAAAAAAAAAAAAAA) >> 1 | 
					(bit_arr & 0x5555555555555555) << 1;

	return bit_arr;
}

unsigned long BArrMirrorBitArrWithLUT(unsigned long bit_arr)
{	
	unsigned long mask = 0x00000000000000FF;
	unsigned long temp = 0ul;
	unsigned int i = 0;
	
	for(i = 0; i < 8; ++i)
	{
		temp <<= 8;
		temp |= LUTMirror[bit_arr & mask];
		bit_arr >>= 8;
	}		

	return temp;
}
