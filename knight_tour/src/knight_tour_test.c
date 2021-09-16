#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <string.h> /* memset */

#include "knight_tour.h"


#define RUN_TEST(test) test ? printf("OK: " #test "\n") : \
                              printf("FAILED:  " #test "\n");

int GameOn(int *answer);

int main(void)
{
    int *answer = NULL;
    int is_game_on = 0;
    int start_idx = 0;
    
    answer = (int *)calloc(64, sizeof(int));
    printf("WELCOME to Chess Knight's Tour Aewsome game\n\n");
    printf("            {)\n"          
"        c==//\\\n"         
"   _-~~/-._|_|\n"         
"  /'_,/,   //'~~~\\;;,\n"  
"  `~  _( _||_..\\ | ';;\n" 
"    /'~|/ ~' `\\<\\>  ;\n"  
"    '  |      /  |     \n"
"      ''     ''  '')\n\n");

    printf("To start Choose (1 or 2):\n"
            "1. Start game\n"
            "2. Testing:\n"); 

    scanf("%d", &is_game_on);
    
    if(1 == is_game_on)
    {
        while(64 != start_idx)
        {
            start_idx = GameOn(answer);
        }
        memset(answer, 0, 64 * sizeof(int));
        free(answer);
    }
    else
    {
        RUN_TEST(1 == IsTour(0, answer, 0));
        PrintTheBoard(answer);
        memset(answer, 0, 64 * sizeof(int));
        RUN_TEST(1 == IsTour(0, answer, 1));
        PrintTheBoard(answer);
        memset(answer, 0, 64 * sizeof(int));
        free(answer);
    }
    printf("Hope you enjoyed ! See you next time !! \n");

    return (0);
}

int GameOn(int *answer)
{
    int start_idx = 999;
    int ride_type = 999;

    while(0 > start_idx || start_idx > 64)
    {
        printf("Enter starting Index (0 to 63) or 64 to exit:\n"); 
        scanf("%d", &start_idx);
        if(0 > start_idx || start_idx > 64)
        {
            printf("Invalid starting index!! Try again\n");
        }
    }
    while((0 > ride_type || ride_type > 1) && start_idx != 64)
    {
        printf("Enter 1 for Smart-Knight or 0 for Stupid-Knight:\n"); 
        scanf("%d", &ride_type);
        if(0 > ride_type || ride_type > 1)
        {
            printf("Invalid Knight Type!! Try again\n");
        }
    }
    printf("\n\n");
    if(64 != start_idx)
    {
        if (0 == IsTour(start_idx, answer, ride_type))
        {
            printf("Knight was killed by double passing mine !\n");
        }
        PrintTheBoard(answer);
    }
    
    return (start_idx);
}

