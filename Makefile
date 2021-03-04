STD=c90
OUT_DIR=bin
OUT_FILE=main
FILES=$(wildcard *.c)

debug:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES)
	$(OUT_DIR)/$(OUT_FILE) -d

production:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES)
	$(OUT_DIR)/$(OUT_FILE)