cc := g++
flags := -Wall -Wextra -std=c++14 -pedantic

include_folder := ./include
src_folder := src
solutions_folder := src/solutions
bin_folder := bin
obj_folder := obj

test_folder := test
test_file := $(wildcard $(test_folder)/test_*.cpp)
test_out_folder := test/out
test_out := $(patsubst $(test_folder)/%.cpp, $(test_out_folder)/%, $(test_file))

OUT := $(patsubst $(solutions_folder)/%.cpp, $(bin_folder)/%, $(wildcard $(solutions_folder)/*.cpp))
OBJECTS := $(patsubst $(src_folder)/%.cpp, $(obj_folder)/%.o, $(wildcard $(src_folder)/*.cpp))

all: $(OUT)

$(OUT): $(bin_folder)/%: $(solutions_folder)/%.cpp $(OBJECTS) | $(bin_folder)
	$(cc) $(flags) -I$(include_folder) -o $@ $^

$(OBJECTS): $(obj_folder)/%.o: $(src_folder)/%.cpp | $(obj_folder)
	$(cc) $(flags) -I$(include_folder) -c $< -o $@

$(bin_folder):
	mkdir $(bin_folder)

$(obj_folder):
	mkdir $(obj_folder)

.PHONY: test
test: $(test_out)

$(test_out): $(test_folder)/out/%: $(test_folder)/%.cpp $(OBJECTS) | $(test_out_folder)
	$(cc) $(flags) -I$(include_folder) -o $@ $^
	./$@

$(test_out_folder):
	mkdir $(test_out_folder)

clean:
	rm -rf $(bin_folder)
	rm -rf $(obj_folder)
	rm -rf $(test_out_folder)