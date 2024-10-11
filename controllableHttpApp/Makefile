TARGET = controllableHttpAPP

SRC = main.cpp

CXX = g++

CXXFLAGS = -Wall -g -std=c++17

INCLUDES = -I/usr/local/include/comapi


LIBS = /usr/local/lib64/comapi/libcommapiengine.so /usr/local/lib64/comapi/libcommonapicontrollableprocess.so

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
