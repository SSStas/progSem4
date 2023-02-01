#resulting file name
EXECUTABLE=wordsFrequency

#file(s) with source code
SOURCE=main.c word.c

#compilation options
C=gcc
CFLAGS= -Wall -O2


all: $(EXECUTABLE);


$(EXECUTABLE):
	$(C) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)
		

clean:
	rm -rf *.o $(EXECUTABLE)
