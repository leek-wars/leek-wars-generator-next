SRC_DIR := src/ai src/area src/effect src/doc src/entity src/fight \
src/item src/map src/module src/util src/action benchmark
TEST_DIR := test

BUILD_DIR := $(addprefix build/default/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/default/,$(TEST_DIR))
BUILD_DIR += $(addprefix build/coverage/,$(SRC_DIR))

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))
SRC_TEST := $(foreach d,$(TEST_DIR),$(wildcard $(d)/*.cpp))

OBJ := $(patsubst %.cpp,build/default/%.o,$(SRC))
OBJ_MAIN = build/default/src/Main.o
OBJ_TEST := $(patsubst %.cpp,build/default/%.o,$(SRC_TEST))
OBJ_COVERAGE := $(patsubst %.cpp,build/coverage/%.o,$(SRC))

FLAGS := -std=c++11 -O2 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := -ljit -lleekscript
MAKEFLAGS += --jobs=$(shell nproc)


all: build/leek-wars-generator

build/default/%.o: %.cpp
	g++ -c -Ilibs/ $(FLAGS) -o "$@" "$<"

build/coverage/%.o: %.cpp
	g++ -c $(FLAGS) -O0 -fprofile-arcs -ftest-coverage -o "$@" "$<"

$(BUILD_DIR):
	@mkdir -p $@

build/leek-wars-generator: $(BUILD_DIR) $(OBJ) $(OBJ_MAIN)
	g++ $(FLAGS) -o build/leek-wars-generator $(OBJ) $(OBJ_MAIN) $(LIBS)
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"

# Build test target
build/leek-wars-generator-test: $(BUILD_DIR) $(OBJ) $(OBJ_TEST)
	g++ $(FLAGS) -o build/leek-wars-generator-test $(OBJ) $(OBJ_TEST) $(LIBS)
	@echo "--------------------------"
	@echo "Build (test) finished!"
	@echo "--------------------------"

# Run tests
test: build/leek-wars-generator-test
	@build/leek-wars-generator-test

# Build with coverage flags enabled
build/leek-wars-generator-coverage: $(BUILD_DIR) $(OBJ_COVERAGE) $(OBJ_TEST)
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

clean:
	rm -rf build
	@echo "----------------"
	@echo "Project cleaned."
	@echo "----------------"

