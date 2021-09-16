#include <stdio.h> /*for input/output*/
#include <assert.h> /*for assert*/

/*x multiplied with 2 in the power of y*/
double pow2(unsigned int x, int y);
/*is a power of 2*/
int IsPow2(unsigned int n);
/*add 1 to n*/
int Add1(unsigned int n);
/*print numbers with 3 bits turned on ('1')*/
void ThreeBits(unsigned int bitArr[], int arrSize);
/*reverse number without a loop*/
unsigned int byte_mirror_no_loop(unsigned int num);
/*reverse number with a loop*/
unsigned int byte_mirror_loop(unsigned int num);
/*Are second AND sixth bits turned on*/
int Is2_and_6(unsigned char input);
/*Is second OR sixth bits turned on*/
int Is2_or_6(unsigned char input);
/*swap between 3rd & 5th bits*/
int Swap3_and_5(unsigned char input);
/*return closest number to num (smaller than num)
 which is divided by 16 with no remainder*/
unsigned int Closest16Num(unsigned int num);
/*swap between 2 variables without using extra variable*/
void Swap2Vars(unsigned int num1, unsigned int num2);
/*count the number of turned on bits*/
int CountBits(int num);
/*count the number of turned on bits without looping*/
int CountBits_noLoops(int num);
/*print float number as binary*/
void PrintFloatBit(float num);

int main()
{
	/*used to test the constructed functions below*/
	return 0;
}

double pow2(unsigned int x, int y)
{
	int z = 0;
	
	assert(y < 32 && y > -32);

	if(y < 0)
	{
		y = ~y;
		z = x >> y;
		z = z >> 1;
	}
	else
	{	
		z = x << y;
	}
	
	return (double) z;
}

int IsPow2(unsigned int n)
{	
	return ((0 ==(n & (n-1))) ? 1: 0 ;
}

int Add1(unsigned int n)
{
	int m = 1;
	/*check bit according to '1' position of 
	m num (incremented to left - multiplied by 2)*/
	while(n & m)
	{
		n = n ^ m;
		m <<= 1;
	}
	n = n ^ m;
	
	return n;
}

void ThreeBits(unsigned int *bitArr[], int arrSize)
{
	int counter = 0;
	int i = 0, bitPos = 1;
	
	assert (arrSize > 0);
	assert (NULL != bitArr);
	
	printf("Ints with 3 bits ('1') are: ");
	for(i = 0; i < arrSize; ++i)
	{
		counter = 0;
		bitPos = 1;
		while(bitPos != (1 << 31))
		{
			if(bitArr[i] & bitPos > 0)
			{
				++counter;
			}
			if(counter > 3)
			{
				break;
			}
			bitPos <<= 1;
		}
		if(3 == counter)
		{
			printf("%u ", bitArr[i]);
		}
	}
	printf("\n");
}

unsigned int byte_mirror_no_loop(unsigned int num)
{	
	/*swap every half of num increasing resolution*/
	num = (num << 16 | num >> 16);
	num = ((num & 0xFF00FF00) >> 8) | ((num & 0x00FF00FF) << 8);
	num = ((num & 0xF0F0F0F0) >> 4) | ((num & 0x0F0F0F0F) << 4);
	num = ((num & 0xCCCCCCCC) >> 2) | ((num & 0x33333333) << 2);
	num = ((num & 0xAAAAAAAA) >> 1) | ((num & 0x55555555) << 1);

	return num;
}


unsigned int byte_mirror_loop(unsigned int num)
{
	int i = 0;
	unsigned int result = 0;
	
	/*Loop through all bits (32)*/
	for(i = 0; i < 32; ++i)
	{
		result <<= 1;
		if(1 == (num & 1))
		{
			result = Add1(result);
		}
		num >>= 1;
	}
	
	return result;
}

int Is2_and_6(unsigned char input)
{
	return (input & 0x20) && (input & 0x2);
}

int Is2_or_6(unsigned char input)
{	
	return (input & 0x20) || (input & 0x2);
}

int Swap3_and_5(unsigned char input)
{
	int result = 0, tempResult = 0;

	tempResult = (((input & 0x4) << 2) | ((input & 0x10) >> 2));
	/*comparing to identify turned on 3's and 5's bits*/
	result = input & 0xEB;
	result ^= tempResult;

	return result;
}

unsigned int Closest16Num(unsigned int num)
{
	/*masking the remainder out*/
	return num & 0xFFFFFFF0;
	/*Alternative way:	
	
	unsigned int remainder = 0;

	remainder = num & 15;
	return num - remainder;*/
}


void Swap2Vars(unsigned int num1, unsigned int num2)
{
	num1 ^= num2;
	num2 ^= num1;
	num1 ^= num2;
	printf("0x%x	0x%x\n", num1, num2);
}

int CountBits(int num)
{
	int counter = 0;
	int bitPos = 1;
	
	/*Loop through all bits (32)*/
	while(bitPos != (1 << 31))
	{
		if(num & bitPos > 0)
		{
			++counter;
		}
		bitPos <<= 1;
	}

	return counter;
}

int CountBits_noLoops(int num)
{
	/*Hamming weight approch*/
	num = (num & 0x55555555) + ((num >> 1) &  0x55555555);
	num = (num & 0x33333333) + ((num >> 2) &  0x33333333);
	num = (num & 0x0F0F0F0F) + ((num >> 4) &  0x0F0F0F0F);
	num = (num & 0x00FF00FF) + ((num >> 8) &  0x00FF00FF);
	num = (num & 0x0000FFFF) + ((num >> 16) & 0x0000FFFF);

	return num;
}

void PrintFloatBit(float num)
{
	float *ptr1 = &num;
	int i = 0;
	unsigned int *ptr2 = (unsigned int *)ptr1;
	
	for(i = 0; i < 32; ++i)
	{
		/*Identifing 1's from left to right - for correct printing*/
		if((*ptr2 << 1) >> 1 != *ptr2)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		*ptr2 <<= 1;
	}
	printf("\n");
}

