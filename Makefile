SRC_DIR := src src/ai src/area src/effect src/doc src/entity src/fight \
src/item src/map src/module src/util src/action benchmark test

BUILD_DIR := $(addprefix build/,$(SRC_DIR))
SRC := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

FLAGS := -std=c++11 -O2 -g3 -Wall -Wextra -Wno-pmf-conversions
LIBS := -ljit -lleekscript

all: makedirs leek-wars-generator

build/%.o: %.cpp
	g++ -c -Ilibs/ $(FLAGS) -o "$@" "$<"
	
makedirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

leek-wars-generator: $(OBJ)
	g++ $(FLAGS) -o build/leek-wars-generator $(OBJ) $(LIBS)
	@echo "---------------"
	@echo "Build finished!"
	@echo "---------------"
	
clean:
	rm -rf build
	@echo "----------------"
	@echo "Project cleaned."
	@echo "----------------"

