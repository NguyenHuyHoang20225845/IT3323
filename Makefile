# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Input / Output file
TARGET = Bai1
SRC = Bai1.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET).exe

# Run program
run: $(TARGET)
	./$(TARGET).exe

# Remove build files
clean:
	rm -f $(TARGET).exe
