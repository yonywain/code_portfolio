GDFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
CFLAGS = $(GDFLAGS)
CC = gcc

#paths
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
LIB_DIR = ../lib
HEAD_DIR = /home/student/Yoni-Wainsztok/projects/include
src_dir_link = $$(pwd)/src

SRC := $(filter-out %test.c, $(wildcard $(SRC_DIR)/*.c))
HEAD := $(subst .c,.h, $(subst $(SRC_DIR),$(HEAD_DIR), $(SRC)))
OBJ := $(subst .c,.o,$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC)))
DEPS := $(subst .o,.d, $(subst $(OBJ_DIR)/,, $(OBJ)))
LIB := $(addprefix $(LIB_DIR)/,libscheduler.ar)
tests := $(addprefix $(SRC_DIR)/,knight_tour_test.c)
#DEPS = $(subst .c,.d,$(SRC))
 
VPATH = src:obj:include:lib:dep

#all: directories $(objects) $(library) symlinks
all: $(LIB) symlinks

# create the library files and place in the lib folder
$(LIB) : $(OBJ) | $(LIB_DIR)
	ar -cr $@ $(OBJ)

-include $(DEPS)    

%.d : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM -MT $(OBJ_DIR)/$(@:.d=.o) $< > $@
	echo "	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/$(@:.d=.o) $<" >> $@

# Create the symlinks and place in the headers folder
symlinks : $(HEAD)

%.h : | $(HEAD_DIR)
	-ln -sf $(subst $(HEAD_DIR), $(src_dir_link), $@) $@

$(OBJ_DIR) :
	-mkdir $(OBJ_DIR)
$(LIB_DIR) :
	-mkdir $(LIB_DIR)
$(HEAD_DIR) :
	-mkdir $(HEAD_DIR)
$(DEP_DIR) :
	-mkdir $(DEP_DIR)
	
.PHONY : clean test
clean :
	-rm -f $(OBJ)
	-rm -f $(HEAD)
	-rm -f $(LIB)
	-rm -f test.out
	-rm -f $(DEPS)
	-rmdir $(OBJ_DIR)
	-rmdir $(HEAD_DIR)
	-rmdir $(LIB_DIR)
	-rmdir $(DEP_DIR)	
	
test : $(LIB)
	$(CC) $(CFLAGS) -o test.out $(tests) $^

debug :
	echo $(OBJ)
