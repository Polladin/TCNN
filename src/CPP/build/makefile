

CC=g++

CFLAGS=-c -std=c++11 -Wall

SRC= 	../common/debugLog/debugLog.cpp 			\
	../common/ODE45/ODE45.cpp				\
	../common/test/unit_test.cpp				\
	../TCNN/opt_function/chaotic/chaotic.cpp		\
	../TCNN/opt_function/functions/TCNN_opt_function.cpp	\
	../common/common.cpp					\
	../TCNN/opt_function/test/opt_func_test.cpp

OBJ=$(SRC:.cpp=.o)

TARGET=opt_func_test
#unit_test

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
