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
LIBS       = -Wl,-rpath='/lib/x86_64-linux-gnu' -lpython3.8 -lm
INCLUDE    = -I/usr/include/python3.8
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
%.o:%.c c_python.h
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)
	@$(MOVE) $@ $(LIBRARY_DIR) # @ means do not echo command

%.e:%.c c_python.h
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
default: test c_module

test: create_dir $(PRE_HEADER) $(OBJS) 
	cd $(LIBRARY_DIR);\
	$(LINKER) -o $@ $(OBJS) $(LIBS);\
	$(MOVE) $@ ../$(BIN_DIR)

c_module: c_module.c c_python.h
	$(CC) -c c_module.c -o c_module.o -O2 -fPIC $(INCLUDE)
	$(CC) c_module.o -shared -o c_performance.so $(LIBS)
	#python3.8 setup.py build_ext --inplace

debug: BUILD_TYPE:=-g3 
debug: default

create_dir:
	@mkdir -p lib
	@mkdir -p $(LIBRARY_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(LIBRARY_DIR)/*


