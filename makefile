default: roman

src/roman.o: src/roman.c src/roman.h
	gcc -c $< -o $@

roman: src/roman.o
	ar rcs roman.a src/roman.o

clean:
	-rm -f src/*.o
	-rm -f roman.a