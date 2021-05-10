#=================================================
# Makefile settings
#=================================================
.PHONY: create_dir # specify phony target, do not generate file as target name

.DEFAULT_GOAL=default # specify default target if there is no target specified

VPATH=library # specify directory where to check target file update to date or not

SHELL=/bin/bash

#=================================================
# Compiler settings
#=================================================
CC         = gcc
LINKER     = $(CC)
DEFINES    = 
BUILD_TYPE = -g3
CFLAGS     = $(BUILD_TYPE) -Wfatal-errors -Wall -Wextra -Wenum-compare -std=gnu99 -fPIC -Wno-unused-parameter -Wno-unused-variable
LIBS       = -Wl,-rpath='/usr/local/lib' -lpython3.9
INCLUDE    = -I/usr/local/include/python3.9
MOVE       = mv -f

#=================================================
# Build target
#=================================================
LIBRARY_DIR       := library
BIN_DIR       	  := bin
OBJS              := main.o c_python.o 
PRE_HEADER        := $(OBJS:.o=.e)
TARGET            := test 

#=================================================
# Compile implicit rules
#=================================================
%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR) # @ means do not echo command

%.e:%.c
	$(CC) -E $< -o $@ $(CFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.o:%.cxx
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)

%.e:%.cxx
	$(CXX) -E $< -o $@ $(CXXFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR)


#=================================================
# Target rules
#=================================================
default: test

test: create_dir $(PRE_HEADER) $(OBJS) 
	cd $(LIBRARY_DIR);\
	$(LINKER) -o $@ $(OBJS) $(LIBS);\
	$(MOVE) $@ ../$(BIN_DIR)

debug: BUILD_TYPE:=-g3 
debug: default

create_dir:
	@mkdir -p lib
	@mkdir -p $(LIBRARY_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(LIBRARY_DIR)/*


