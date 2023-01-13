# Copyright 2010, 2010 IPOL Image Processing On Line http://www.ipol.im/
# Author: Catalina Sbert <catalina.sbert@uib.es>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

CSRC = io_png.c  auxiliary_lib.c screened_lib.c screened_poisson.c

# all source code
SRC	= $(CSRC) 

# C objects
COBJ = $(CSRC:.c=.o)
# all objects
OBJ	= $(COBJ) 

# binary target
BIN	= screened_poisson

default	: $(BIN)

# C optimization flags
COPT = -O3  -funroll-loops

# C compilation flags
CFLAGS = $(COPT) -Wall -Wextra  \
	-Wno-write-strings -ansi 

# link flags
LDFLAGS	= -lfftw3 -lpng -lm


# partial compilation of C source code
%.o: %.c %.h
	$(CC) -c -o $@  $< $(CFLAGS) -I/opt/local/include/ -I/usr/local/include/   

$(BIN)	: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -L/opt/local/lib/ -L/usr/local/lib/

.PHONY	: clean distclean
clean	:
	$(RM) $(OBJ)
distclean	: clean
	$(RM) $(BIN)



















