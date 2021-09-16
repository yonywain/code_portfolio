CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
LFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj
SRC = $(filter-out %test.c,$(wildcard $(SRC_DIR)/*.c))
OBJ = $(subst .c,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
DEP = $(subst .c,.d,$(SRC))

calc.out : $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

-include $(DEP)

%.d : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< -MT $(subst .c,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) > $@
	echo "	$(CC) $(CFLAGS) -c -o $(subst .c,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$^)) $<" >> $@

$(OBJ_DIR) :
	-mkdir $(OBJ_DIR)

.PHONY : clean
clean :
	-rm -f $(OBJ)
	-rm -f calc.out
	-rm -f $(DEP)
	-rmdir $(OBJ_DIR)

