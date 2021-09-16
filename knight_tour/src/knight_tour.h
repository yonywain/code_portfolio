#ifndef ILRD_KNIGHT_TOUR_H
#define ILRD_KNIGHT_TOUR_H


int IsTour(int idx, int *answer, int smart_ride);

void PrintTheBoardBit(size_t board);
void PrintTheBoard(int *moves);

/* static int TravelIMP(int index, unsigned long bit_array, int *tour_arr, int i);
static int IsValidMoveIMP(int next_move, int index, unsigned long bit_array); */


#endif   /* ILRD_KNIGHT_TOUR_H */
