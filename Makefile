###############################################################
# Standard Makefile template for all projects
# Copyright Danh Nguyen 2021
# Based on GNU C++ standard
#
# https://github.com/danny-cpp
###############################################################
PRJNAME := prodcon

# These following directories are assumed to exist; abide to GNU guideline.
CC	:= g++
SRCDIR	:= src
BLDDIR	:= build
TARGET	:= bin/$(PRJNAME)

# Do not remove -MP -MD flags. These are necessary for generating *.d files,
# which contains rules for headers
CFLAGS := -std=c++11 -MP -MD
DEBUG := $(CFLAGS) -Wall -O0 -g -D_GLIBCXX_DEBUG -DDEBUG_MODE
RELEASE := $(CFLAGS) -Wall -O0 -g -D_GLIBCXX_DEBUG

# CONFIGURE RELEASE/DEBUG MODE HERE
MODE := $(RELEASE)

SRC	:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJS	:= $(patsubst $(SRCDIR)/%, $(BLDDIR)/%, $(SRC:.cpp=.o))
INCLUDE	:= -I include

.PHONY: all clean

all: $(TARGET)


$(TARGET): $(OBJS)
	@echo "\n##__Linking objs"
	@echo "---------------------------------------------------------------"
	$(CC) $(MODE) -o $@ $^
-include $(BLDDIR)/*.d

# This section already include automatic dependency tracking by using -include
# directive above. Do not add anything in the rules
$(BLDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BLDDIR)
	@echo "\n##__Compiling translation unit" $@
	@echo "---------------------------------------------------------------"
	$(CC) $(INCLUDE) $(MODE) -c -o $@ $<


clean:
	rm -fr $(BLDDIR)
	rm -fr bin/*



