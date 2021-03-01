STD=c90
OUT=main
FILES=$(wildcard *.c)

debug:
	gcc -o $(OUT) -std=$(STD) $(FILES)
	./$(OUT) -d

production:
	gcc -o $(OUT) -std=$(STD) $(FILES)
	./$(OUT)