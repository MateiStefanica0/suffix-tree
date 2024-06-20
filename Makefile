CCFLAGS=-Wall -Werror

.PHONY: clean

# run: build
# 	./tema2 -c4 ./fisier.in ./fisier.out

build: main.c 
	gcc main.c functions.c $(CCFLAGS) -o tema2 -ggdb3

# regula folosita pentru testare
# valgrind:
# 	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt --track-origins=yes -s ./tema2 -c4 ./fisier.in ./fisier.out
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  --tool=memcheck --log-file=valgrind-out.txt ./a.out -c1 ./fisier.in ./fisier.out


clean:
	rm ./tema2