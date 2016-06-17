
CC = gcc
CFLAGS =
DEPS = crackConstants.h
OBJ = aFill.o attemptInput.o full.o main.o parseArgs.o passGen.o printPassword.o \
terminatePassword.o validFileCheck.o 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

crackmake: $(OBJ)
	$(CC) $^ $(CFLAGS) -o crack

clean: 
	@echo "Cleaning directory..."
	rm -f *.o a.out *.gch
	@echo "Clean."
