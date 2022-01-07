CC := gcc
scriptName := FMindex

$(scriptName): main.o FMindex.o getRank.o BWT.o
	$(CC) -o $@ $^
	@echo DONE!

BWT.o: BWT.c bwt.h
	$(CC) -c $<

getRank.o: getRank.c getRank.h
	$(CC) -c $<

FMindex.o: FMindex.c FMindex.h
	$(CC) -c $<

main.o: main.c
	$(CC) -c $<


.PHONY: clean
clean:
	rm *.o
	rm $(scriptName)
