STD=c90
OUT_DIR=bin
OUT_FILE=main
OUT_FILE_TEST=test
FILES=$(filter-out tests.c, $(wildcard *.c))
TEST_FILES=$(filter-out main.c, $(wildcard *.c))

# DEBUG CONFIG
debug: run-debug

run-debug: compile-debug
	@echo "Running $(OUT_DIR)/$(OUT_FILE) in debug..."
	@$(OUT_DIR)/$(OUT_FILE)
	@echo "Debugging finished"

compile-debug: create-bin
	@echo "Compiling for debugging..."
	@gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES) -DDEBUG
	@echo "Compiling finished"

# PRODUCTION CONFIG
production: run-production

run-production: compile-production
	@echo "Running $(OUT_DIR)/$(OUT_FILE) in production..."
	@$(OUT_DIR)/$(OUT_FILE)
	@echo "Program finished"

compile-production: create-bin
	@echo "Compiling for production..."
	@gcc -o $(OUT_DIR)/$(OUT_FILE) -std=$(STD) $(FILES) -O2
	@echo "Compiling finished"

# TEST CONFIG
test: run-test

run-test: compile-tests
	@echo "Running tests..."
	@$(OUT_DIR)/$(OUT_FILE_TEST) --verbose
	@echo "Testing finished"

compile-tests: create-bin
	@echo "Compiling tests..."
	@gcc -o $(OUT_DIR)/$(OUT_FILE_TEST) -std=$(STD) $(TEST_FILES)
	@echo "Compiling finished"

# UTILS
create-bin:
	@echo "Checking for bin directory..."
	@if [ -d "bin" ]; then \
		echo "Directory exists"; \
	else \
		echo "Directory doesn't exist"; \
		echo "Creating bin..."; \
		mkdir bin; \
		echo "Directory created"; \
	fi