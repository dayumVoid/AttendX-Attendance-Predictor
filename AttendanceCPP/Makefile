CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = $(wildcard *.cpp)
OUT = attendance

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT) attendance.txt
