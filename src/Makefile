SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:%.c=../obj/%.o)
INSTALL_PATH?=/usr

INC=-I./

all: dirs ../bin/sesh

dirs:
	@mkdir -p ../obj
	@mkdir -p ../bin

../bin/sesh: $(OBJ_FILES) ../obj/argtable3.o
	@echo Linking sesh...
	@gcc $(OBJ_FILES) ../obj/argtable3.o -o $@ 

$(OBJ_FILES): ../obj/%.o: %.c
	@echo Compiling $<...
	@gcc $< -c -o $@ $(INC)

clean:
	@echo Cleaning...
	@rm -rf ../obj
	@rm -rf ../bin

install: all
	cp ../bin/sesh $(INSTALL_PATH)/bin
	mkdir -p $(INSTALL_PATH)/share/sesh
	cp share/HELP $(INSTALL_PATH)/share/sesh

# argtable

../obj/argtable3.o: deps/argtable3/argtable3.c
	@echo Compiling argtable
	@gcc $< -c -o $@