STD=c90
OUT_DIR=bin
OUT_FILE=main
FILES=$(wildcard *.c)
TEST_FILES=$(wildcard tests/*.c)

debug:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES)
	$(OUT_DIR)/$(OUT_FILE) -d

production:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES)
	$(OUT_DIR)/$(OUT_FILE)

test:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(TEST_FILES)
	$(OUT_DIR)/$(OUT_FILE)