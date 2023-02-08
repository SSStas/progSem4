#resulting file name
EXECUTABLE=wordsFrequency

#file(s) with source code
SOURCE=main.c wordsFreq.c

#compilation options
CC=gcc
CFLAGS=-Wall -O2


all: $(EXECUTABLE);

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) -ldl
		

clean:
	rm -rf *.o $(EXECUTABLE)
