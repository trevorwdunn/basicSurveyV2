# Tells make to treat these keywords like targets instead of files
.PHONY: all clean run

all:
	gcc -g main.cpp -lstdc++ -o main

clean:
	rm main

run: all
	./main
