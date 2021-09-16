/***************************************
* Author: Yoni Wainsztok
* Date: 21/01/2019
* Reviewer: Yarin
* Subject: knight_tour-RC1
***************************************/
#include <stdio.h>  /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* abs */

#include "bit_array.h" /* IsBitOn */
#include "knight_tour.h" /* API */

typedef struct next_move
{
	int counter;
	int MOVES_idx;
}next_move_t;

static int TravelIMP(int idx, 
					 int *answer, 
					 unsigned long bitarr, 
					 int k, 
					 int smart_ride);
static int IsValidMoveIMP(int idx, int next_move, unsigned long bitarr);
static void FindNextTravel(int idx, unsigned long bitarr, int smart_ride);
static int MOVES_ADJUSTED_cmp(const void *a, const void *b);

void PrintTheBoardBit(size_t board);
void PrintTheBoard(int *moves);

int MOVES[8] = {-15, -6, -10, -17, 15, 6, 10, 17};
next_move_t MOVES_ADJUSTED[8] = {0};

const int POSSIBLE_MOVES = 8;
const int SQUARES_NUM = 64;

enum RETURN_VAL
{
	NO = 0,
	YES = 1
};

int IsTour(int idx, int *answer, int smart_ride)
{
	unsigned long bitarr = 0ul;

	assert(0 <= idx && idx < SQUARES_NUM);

	return TravelIMP(idx, answer, bitarr, 0, smart_ride);
}

static int TravelIMP(int idx, 
					 int *answer, 
					 unsigned long bitarr, 
					 int k, 
					 int smart_ride)
{
	int next_move = 0;
	int i = 0;
	int res = 0;

	assert(0 <= idx && idx < SQUARES_NUM);
	
	bitarr = BArrSetBitOn(bitarr, idx);
	answer[idx] = k;
	
	if(YES == BArrAreAllBitsOn(bitarr))
	{
		return (YES);
	}
	
	FindNextTravel(idx, bitarr, smart_ride);
	for(i = 0; i < POSSIBLE_MOVES && 0 == res; ++i)
	{
		next_move = MOVES[MOVES_ADJUSTED[i].MOVES_idx] + idx;
		if(YES == IsValidMoveIMP(idx, next_move, bitarr))
		{
			res = TravelIMP(next_move, answer, bitarr, k + 1, smart_ride);
		}
	}

	return (res);
}

static int IsValidMoveIMP(int idx, int next_move, unsigned long bitarr)
{
	int next_move_modul = next_move % POSSIBLE_MOVES;
	int idx_modul = idx % POSSIBLE_MOVES;
	int next_move_div = next_move / POSSIBLE_MOVES;
	int idx_div = idx / POSSIBLE_MOVES;

	int result = 	(next_move >= 0
                    && next_move < SQUARES_NUM
                    && (abs(next_move_modul - idx_modul) < 3) 
					&& (abs(next_move_div - idx_div)  < 3)					 
					&& (YES == BArrIsBitOff(bitarr, next_move)));

	return (result);
}


static void FindNextTravel(int idx, unsigned long bitarr, int smart_ride)
{
	int j = 0;
	int check_idx = 0;
	int count = 0;

	if(0 == smart_ride)
	{
		for(j = 0; j < POSSIBLE_MOVES; ++j)
		{
			MOVES_ADJUSTED[j].MOVES_idx = j;
			MOVES_ADJUSTED[j].counter = -1;
		}
	}
	else
	{
		for(j = 0; j < POSSIBLE_MOVES; ++j)
		{
			count = POSSIBLE_MOVES;
			for(check_idx = 0; check_idx < POSSIBLE_MOVES; ++check_idx)
			{
				if(	NO == IsValidMoveIMP(idx + MOVES[j], 
					idx + MOVES[j] + MOVES[check_idx], 
					bitarr))
				{
					--count;
				}
			}
			MOVES_ADJUSTED[j].counter = count;
			MOVES_ADJUSTED[j].MOVES_idx = j;
		}
		qsort(MOVES_ADJUSTED, 
			  POSSIBLE_MOVES, 
			  sizeof(next_move_t), 
			  MOVES_ADJUSTED_cmp);
	}
}

static int MOVES_ADJUSTED_cmp(const void *a, const void *b)
{
	next_move_t *idx1 = (next_move_t *)a;
	next_move_t *idx2 = (next_move_t *)b;

	return (idx1->counter - idx2->counter);
}

/* Generic Chess/Bit Board Printing Functions*/
void PrintTheBoardBit(size_t board)
{
  int i = 0;
  int j = 0;
  int mask = 1;

  for (i = 0; i < 8; ++i)
  {
      for (j = 0; j < 8; ++j)
      {
          if (1 == (mask & board))
          {
              printf("1   ");
          }
          else
          {
              printf("0   ");
          }
          board = board >> 1;
      }
      printf("\n\n");
  }
  printf("\n\n\n\n\n");
}

void PrintTheBoard(int *moves)
{
  int i = 0;

  for (i = 1; i < 65; ++i)
  {
      printf("%d\t", moves[i-1]);
      if (0 == i % 8)
      {
          printf("\n\n");
      }
  }

  printf("\n\n\n");
}