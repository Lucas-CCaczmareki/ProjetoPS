CXX = g++
CXXFLAGS = -std=c++17 -O2 -I src

SRC = src/main.cpp \
      src/vm/vm.cpp \
      src/cpu/cpu.cpp \
      src/instruction_set/decoder.cpp \
      src/instruction_set/executor.cpp \
      src/loader/binary_loader.cpp \
      src/memory/memory.cpp

OUT = vm

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)