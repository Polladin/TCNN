

CC=g++

CFLAGS=-c -std=c++11 -Wall #-c

SRC=../../common/debugLog/debugLog.cpp 						\
	../../common/ODE45/ODE45.cpp							\
	../../common/test/unit_test.cpp							\
	../../TCNN/chaotic/chaotic.cpp							\
	../../TCNN/opt_function/TCNN_opt_function.cpp			\
	../../common/common.cpp									\
	../../TCNN/opt_function/functions/func_to_optimize.cpp	\
	../../TCNN/opt_function/test/opt_func_shared_lib.cpp	\
	../../TCNN/opt_function/test/cmd_line_interface.cpp		\
	../dll_opt_function/dll_opt_function.cpp					


OBJ=$(SRC:.cpp=.o)


TARGET=opt_func_test
#unit_test

all: $(SRC) $(TARGET)
#all: $(TARGET)

#$(TARGET):
#	$(CC) $(CFLAGS) $(ALL_SRC) -o $@

$(TARGET): $(OBJ)
	$(CC) -shared -Wl,-soname,TCNN_lib.so $(OBJ) -o TCNN_lib.so

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ)
