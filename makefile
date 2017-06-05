CC=g++
ARCH=-arch x86_64

SANDBOX_DIR=/usr/local/opt/opencv

INCLUDE_FLAGS=-I$(SANDBOX_DIR)/include

CFLAGS=-c -Wall $(INCLUDE_FLAGS)
LDFLAGS= -L$(SANDBOX_DIR)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES=main.cpp Scene.cpp Object.cpp base.cpp PhotonMap.cpp LightSource.cpp Camera.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all : $(SOURCES) $(EXECUTABLE)
	rm *.o

clean :
	rm -f $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) Makefile
	$(CC) $(ARCH) $(LDFLAGS) $(OBJECTS) -o $@ -std=c++11 -O2

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -std=c++11 -O2