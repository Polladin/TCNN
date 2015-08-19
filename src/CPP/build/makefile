

CC=g++

CFLAGS=-c -std=c++11 -Wall #-c

SRC= ../common/debugLog/debugLog.cpp 					\
	../common/ODE45/ODE45.cpp							\
	../common/test/unit_test.cpp						\
	../TCNN/chaotic/chaotic.cpp							\
	../TCNN/opt_function/TCNN_opt_function.cpp			\
	../common/common.cpp								\
	../TCNN/opt_function/functions/func_to_optimize.cpp	\
	../TCNN/opt_function/test/opt_func_test.cpp			\
	../TCNN/opt_function/test/cmd_line_interface.cpp
	

ALL_SRC=	\
	../common/debugLog/debugLog.cpp 					\
	../common/ODE45/ODE45.cpp							\
	../common/test/unit_test.cpp						\
	../TCNN/chaotic/chaotic.cpp							\
	../TCNN/opt_function/TCNN_opt_function.cpp			\
	../common/common.cpp								\
	../TCNN/opt_function/test/opt_func_test.cpp			\
	../common/common.h									\
	../common/debugLog/debugLog.h						\
	../common/debugLog/configLogging.h					\
	../common/ODE45/ODE45.h								\
	../TCNN/chaotic/chaotic.h							\
	../TCNN/opt_function/CNN_opt_function.h				\
	../TCNN/opt_function/test/cmd_line_interface.cpp	\
	../TCNN/opt_function/test/cmd_line_interface.h



OBJ=$(SRC:.cpp=.o)


TARGET=opt_func_test
#unit_test

all: $(SRC) $(TARGET)
#all: $(TARGET)

#$(TARGET):
#	$(CC) $(CFLAGS) $(ALL_SRC) -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ)
