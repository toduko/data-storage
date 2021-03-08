STD=c90
OUT_DIR=bin
OUT_FILE=main
OUT_FILE_TEST=test
FILES=$(filter-out tests.c, $(wildcard *.c))
TEST_FILES=$(filter-out main.c, $(wildcard *.c))

debug:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES) -DDEBUG
	$(OUT_DIR)/$(OUT_FILE)

production:
	gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES)
	$(OUT_DIR)/$(OUT_FILE)

test:
	gcc -o $(OUT_DIR)/$(OUT_FILE_TEST) -std=$(STD) $(TEST_FILES)
	$(OUT_DIR)/$(OUT_FILE_TEST) --verbose