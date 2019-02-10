SRC_DIR := src/ai src/area src/effect src/doc src/entity src/fight \
src/item src/field src/module src/util src/action benchmark
TEST_DIR := test

BUILD_DIR := $(addprefix build/default/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/default/,$(TEST_DIR))
BUILD_DIR += $(addprefix build/coverage/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/sanitized/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/deps/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/deps/,$(TEST_DIR))

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))
SRC_TEST := $(foreach d,$(TEST_DIR),$(wildcard $(d)/*.cpp))

OBJ := $(patsubst %.cpp,build/default/%.o,$(SRC))
OBJ_MAIN = build/default/src/Main.o
OBJ_TEST := $(patsubst %.cpp,build/default/%.o,$(SRC_TEST))
OBJ_COVERAGE := $(patsubst %.cpp,build/coverage/%.o,$(SRC))
OBJ_SANITIZED := $(patsubst %.cpp,build/sanitized/%.o,$(SRC))
DEPS := $(patsubst %.cpp,build/deps/%.d,$(SRC))

FLAGS := -std=c++17 -O0 -g3 -Wall -Wextra -Wno-pmf-conversions -Ileekscript/src/
SANITIZE_FLAGS := -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=float-divide-by-zero # -fsanitize=float-cast-overflow
LIBS := `llvm-config --ldflags --libs core orcjit` -Lleekscript/build -lleekscript
MAKEFLAGS += --jobs=$(shell nproc)

.PHONY: test leekscript

all: build/leek-wars-generator

build/default/%.o: %.cpp
	g++ -c -Ilibs/ $(FLAGS) -o "$@" "$<"
	g++ $(FLAGS) -MM -MT $@ $*.cpp -MF build/deps/$*.d

build/coverage/%.o: %.cpp
	g++ -c $(FLAGS) -O0 -fprofile-arcs -ftest-coverage -o "$@" "$<"

build/sanitized/%.o: %.cpp
	g++ -c $(OPTIM) $(FLAGS) $(SANITIZE_FLAGS) -o "$@" "$<"

$(BUILD_DIR):
	@mkdir -p $@

build/leek-wars-generator: build/libleekscript.so $(BUILD_DIR) $(OBJ) $(OBJ_MAIN)
	g++ $(FLAGS) -o build/leek-wars-generator $(OBJ) $(OBJ_MAIN) $(LIBS)
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"

# Build test target
build/leek-wars-generator-test: build/libleekscript.so $(BUILD_DIR) $(OBJ) $(OBJ_TEST)
	g++ $(FLAGS) -o build/leek-wars-generator-test $(OBJ) $(OBJ_TEST) $(LIBS)
	@echo "--------------------------"
	@echo "Build (test) finished!"
	@echo "--------------------------"

# Run tests
test: build/leek-wars-generator-test
	@build/leek-wars-generator-test

build/libleekscript.so:
	@mkdir -p build
	+cd leekscript && make lib
	cp leekscript/build/libleekscript.so build/libleekscript.so

leekscript:
	@mkdir -p build
	+cd leekscript && make lib
	cp leekscript/build/libleekscript.so build/libleekscript.so

# Build with coverage flags enabled
build/leek-wars-generator-coverage: build/libleekscript.so $(BUILD_DIR) $(OBJ_COVERAGE) $(OBJ_TEST)
	g++ $(FLAGS) -fprofile-arcs -ftest-coverage -o build/leek-wars-generator-coverage $(OBJ_COVERAGE) $(OBJ_TEST) $(LIBS)
	@echo "--------------------------"
	@echo "Build (coverage) finished!"
	@echo "--------------------------"

# Coverage results with lcov.
# `apt install lcov`
coverage: build/leek-wars-generator-coverage
	mkdir -p build/html
	lcov --quiet --no-external --rc lcov_branch_coverage=1 --capture --initial --directory build/coverage/src --base-directory src --output-file build/html/app.info
	build/leek-wars-generator-coverage
	lcov --quiet --no-external --rc lcov_branch_coverage=1 --capture --directory build/coverage/src --base-directory src --output-file build/html/app.info
	cd build/html; genhtml --ignore-errors source --legend --precision 2 --branch-coverage app.info

# Valgrind
# `apt install valgrind`
valgrind: build/leek-wars-generator-test
	valgrind --verbose --track-origins=yes --leak-check=full --show-leak-kinds=all build/leek-wars-generator-test

# Build with sanitize flags enabled
build/leek-wars-generator-sanitized: $(BUILD_DIR) $(OBJ_SANITIZED) $(OBJ_TEST)
	g++ $(FLAGS) $(SANITIZE_FLAGS) -o build/leek-wars-generator-sanitized $(OBJ_SANITIZED) $(OBJ_TEST) $(LIBS)
	@echo "--------------------------"
	@echo "Build (sanitized) finished!"
	@echo "--------------------------"

sanitized: build/leek-wars-generator-sanitized
	@build/leek-wars-generator-sanitized

# Line couning with cloc.
# `apt-get install cloc`
cloc:
	cloc . --exclude-dir=.git,lib,build,leekscript
cloc-xml:
	cloc --quiet --xml . --exclude-dir=.git,lib,build,leekscript

clean:
	rm -rf build
	@echo "----------------"
	@echo "Project cleaned."
	@echo "----------------"

# Objects dependencies
-include $(DEPS)