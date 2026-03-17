CXX= g++
CXXFLAGS = -std=c++17

TARGET = ascii_drawer
SRC = image_to_ascii.cpp

OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS := $(shell pkg-config --libs opencv4)

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(OPENCV_CFLAGS) $(OPENCV_LIBS)

clean:
	rm -f $(TARGET)


