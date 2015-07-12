SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(SRC_FILES:src/%.c=obj/%.o)

INC=-I./

all: dirs bin/sesh

dirs:
	@mkdir -p obj
	@mkdir -p bin

bin/sesh: $(OBJ_FILES) obj/argtable3.o
	@echo Linking sesh...
	@gcc $< obj/argtable3.o -o $@ 

$(OBJ_FILES): obj/%.o: src/%.c
	@echo Compiling $<...
	@gcc $< -c -o $@ $(INC)

clean:
	@echo Cleaning...
	@rm -rf obj
	@rm -rf bin

# argtable

obj/argtable3.o: deps/argtable3/argtable3.c
	@echo Compiling argtable
	@gcc $< -c -o $@