#ifndef ILRD_BIT_ARRAY_H
#define ILRD_BIT_ARRAY_H


int BArrIsBitOn(unsigned long bit_arr, int idx);
/*
Checks whether the bit at idx in bit_arr is set or not.
Return Value: 1 if bit is set, 0 if off
Parameters  : bit_arr: the bit array
			  idx: the index 
Proper Input: 0 <= idx < 64
Errors		: assert for out-of-bounds index
*/


int BArrIsBitOff(unsigned long bit_arr, int idx);
/*
Checks whether the bit at idx in bit_arr is set or not.
Return Value: 1 if bit is not set, 0 if on
Parameters  : bit_arr: the bit array
			  idx: the index 
Proper Input: 0 <= idx < 64
Errors		: assert for out-of-bounds index
*/


int BArrCountBitsOn(unsigned long bit_arr);
/*
Counts the number of bits that are set in bit_arr.
Return Value: number of set bits
Parameters  : bit_arr: the bit array
*/


int BArrCountBitsOnLUT(unsigned long bit_arr);
/*
Counts the number of bits that are set in bit_arr.
Return Value: number of set bits
Parameters  : bit_arr: the bit array
*/


int BArrCountBitsOff(unsigned long bit_arr);
/*
Counts the number of bits that are set to off in bit_arr.
Return Value: number of not set bits
Parameters  : bit_arr: the bit array
*/


int BArrCountBitsOffLUT(unsigned long bit_arr);
/*
Counts the number of bits that are set to off in bit_arr.
Return Value: number of not set bits
Parameters  : bit_arr: the bit array
*/


unsigned long BArrSetBitOn(unsigned long bit_arr, int idx);
/*
Set the bit at idx in bit_arr to 1
Return Value: array of the new value
Parameters  : bit_arr: the bit array
			  idx: the index 
Proper Input: 0 <= idx < 64
Errors		: assert for out-of-bounds index
*/


unsigned long BArrSetBitOff(unsigned long bit_arr, int idx);
/*
Set the bit at idx in bit_arr to 0
Return Value: array of the new value
Parameters  : bit_arr: the bit array
			  idx: the index 
Proper Input: 0 <= idx < 64
Errors		: assert for out-of-bounds index
*/


unsigned long BArrGetBitArrayOn();
/*
Set all bits in bit_arr to 1
Return Value: U_LONG_MAX 
Parameters  : bit_arr: the bit array
*/


unsigned long BArrGetBitArrayOff();
/*
Set all bits in bit_arr to 0
Return Value: 0
Parameters  : bit_arr: the bit array
*/


int BArrAreAllBitsOn(unsigned long bit_arr);
/*
Checks whether the entire array is set to 1
Return Value: 1 if the entire array is set to 1, 0 otherwise
Parameters  : bit_arr: the bit array
*/


int BArrAreAllBitsOff(unsigned long bit_arr);
/*
Checks whether the entire array is set to 0
Return Value: 1 if the entire array is set to 0, 0 otherwise
Parameters  : bit_arr: the bit array
*/


unsigned long BArrFlipOneBit(unsigned long bit_arr, int idx);
/*
Flips the bit at idx in bit_arr
Return Value: array of the new value
Parameters  : bit_arr: the bit array
Proper Input: 0 <= idx < 64
Errors		: assert for out-of-bounds index
*/


unsigned long BArrFlipAllBits(unsigned long bit_arr);
/*
Flips all the bits in bit_Arr
Return Value: array of the new value
Parameters  : bit_arr: the bit array
*/


unsigned long BArrRotateBitsRight(unsigned long bit_arr, int rot_time);
/*
Rotate the bits to the right by rot_time times
Return Value: array of the new value
Parameters  : bit_arr: the bit array
Proper Input: rot_time >= 0
Errors		: assert for out-of-bounds rot_time
*/


unsigned long BArrRotateBitsLeft(unsigned long bit_arr, int rot_time);
/*
Rotate the bits to the right by rot_time times
Return Value: array of the new value
Parameters  : bit_arr: the bit array
Proper Input: rot_time >= 0
Errors		: assert for out-of-bounds rot_time
*/


unsigned long BArrMirrorBitArr(unsigned long bit_arr);
/*
Return the mirror image of the array
Return Value: array of the new value
Parameters  : bit_arr: the bit array
*/

unsigned long BArrMirrorBitArrLUT(unsigned long bit_arr);
/*
Return the mirror image of the array
Return Value: array of the new value
Parameters  : bit_arr: the bit array
*/

#endif   /* ILRD_BIT_ARRAY_H */
