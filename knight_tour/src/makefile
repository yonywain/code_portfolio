CC = g++
OUTFLAGS = -I$(HOME)/yoni-wainsztok/cpp/utils
CFLAGS = -ansi -std=c++98 -pedantic-errors -Wall -Wextra -g


knight_tour.out: knight_tour.o knight_tour_test.o bit_array.o
	@-$(CC) $(CFLAGS) $(OUTFLAGS) -o $@ $^
	
knight_tour.o: knight_tour.c bit_array.o
	@-$(CC) $(CFLAGS) $(OUTFLAGS) -c -o $@ $< 

knight_tour_test.o: knight_tour_test.c bit_array.o
	@-$(CC) -c $(CFLAGS) $(OUTFLAGS) -c -o $@ $< 

bit_array.o: bit_array.c
	@-$(CC) $(CFLAGS) $(OUTFLAGS) -c -o $@ $< 
	
.PHONY: clean
clean:
	@-rm *.o
	@-rm *.out
