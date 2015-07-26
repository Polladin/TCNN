

CC=g++

CFLAGS=-c -std=c++11 -Wall

SRC= 	../common/debugLog/debugLog.cpp 	\
	../common/ODE45/ODE45.cpp		\
	../common/test/unit_test.cpp

OBJ=$(SRC:.cpp=.o)

TARGET=unit_test

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
