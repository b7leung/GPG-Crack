# The complier to use.
CC = gcc
# Options to pass into compiler.
CFLAGS = -Wall -g
# Name of program executable.
EXE = crack
# Headers for the program.
HEADERS = crackConstants.h
# .c C source files.
C_SRC = attemptInput.c full.c main.c parseArgs.c passGen.c \
terminatePassword.c validFileCheck.c 
# .o object code source files.
C_OBJS= $(C_SRC:.c=.o)

# $< = first dependency, $@ = target, $^ = all dependencies % = wildcard

# instruction to turn .c to .o (used to only compile changed files)
# also lints each file beforehand
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# main instruction to compile
$(EXE): $(C_OBJS)
	$(CC) $^ $(CFLAGS) -o $@

# cleans program directory 
clean: 
	@echo "Cleaning directory..."
	rm -f *.o a.out *.gch $(EXE)
	@echo "Clean."
