cc := g++
flags := -Wall -Wextra -std=c++14 -pedantic

include_folder := ./include
src_folder := src
solutions_folder := src/solutions
bin_folder := bin
obj_folder := obj

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

clean:
	rm -rf bin/
	rm -rf obj/