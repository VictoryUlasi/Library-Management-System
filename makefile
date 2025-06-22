CXX = g++
CXXFLAGS = -Wall -g

TARGET = LibraryApp

TARGET_DEL = LibraryApp.exe

SRCS = main.cpp Book.cpp User.cpp Library.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(TARGET) clean run

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o :  %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	del /Q $(OBJS)

run : LibraryApp.exe
	LibraryApp.exe