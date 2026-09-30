CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -MMD -MP

TARGET := main

BUILD_DIR := build

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run debug valgrind

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)