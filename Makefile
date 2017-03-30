SRC_DIR := src/ai src/area src/effect src/doc src/entity src/fight \
src/item src/map src/module src/util src/action benchmark
TEST_DIR := test

BUILD_DIR := $(addprefix build/default/,$(SRC_DIR))
BUILD_DIR += $(addprefix build/default/,$(TEST_DIR))

SRC := $(foreach d,$(SRC_DIR),$(wildcard $(d)/*.cpp))
SRC_TEST := $(foreach d,$(TEST_DIR),$(wildcard $(d)/*.cpp))

OBJ := $(patsubst %.cpp,build/default/%.o,$(SRC))
OBJ_MAIN = build/default/src/Main.o
OBJ_TEST := $(patsubst %.cpp,build/default/%.o,$(SRC_TEST))

FLAGS := -std=c++11 -O2 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := -ljit -lleekscript
MAKEFLAGS += --jobs=$(shell nproc)

all: makedirs leek-wars-generator

all: build/leek-wars-generator

build/default/%.o: %.cpp
	g++ -c -Ilibs/ $(FLAGS) -o "$@" "$<"

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
clean:
	rm -rf build
	@echo "----------------"
	@echo "Project cleaned."
	@echo "----------------"

