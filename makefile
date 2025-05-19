CXX = g++
CXXFLAGS = -Wall -g

TARGET = LibraryApp

TARGET_DEL = LibraryApp.exe

SRCS = main.cpp book.cpp user.cpp library.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(TARGET) clean

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o :  %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)