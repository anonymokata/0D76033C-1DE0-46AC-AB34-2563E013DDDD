LIBS=-lcheck
#  Ignore the warnings on the string pointers needing to be signed
CFLAGS=-Wall -Wno-pointer-sign
default: roman

.PHONY: clean
clean:
	-rm -f src/*.o
	-rm -f tests/*.o
	-rm -f roman
	-rm -f roman.a
	-rm -f roman-check
	-clear
	
#  Library building actions
#######################################
roman: src/main.o roman.a
	gcc $(CFLAGS) $^ -o $@

src/main.o: src/main.c
	gcc $(CFLAGS) -c $< -o $@

roman.a: src/roman.o
	ar rcs $@ $^

src/roman.o: src/roman.c src/roman.h
	gcc $(CFLAGS) -c -o $@ $<

# Unit testing actions
#######################################

check: roman-check
	./$<

roman-check: tests/check_roman.o roman.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS) 

tests/check_roman.o: tests/check_roman.c src/roman.h
	gcc $(CFLAGS) -c $< -o $@

