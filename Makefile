STD=c90
OUT=main

default:
	gcc -o $(OUT) -std=$(STD) *.c
	./$(OUT)