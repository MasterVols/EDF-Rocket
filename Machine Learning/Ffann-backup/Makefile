CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS =

SRCS = ffann.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = ffann_executable

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

ffann.o: ffann.cpp ffann.hpp
	$(CXX) $(CXXFLAGS) -c ffann.cpp

main.o: main.cpp ffann.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	$(RM) $(OBJS) $(TARGET)
