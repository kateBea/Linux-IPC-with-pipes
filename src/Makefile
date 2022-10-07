PROGRAM_NAME_C = ipc.c
EXECUTABLE = ipc
OPT_LEVEL = -g

# compile all
all: build_c

build_c: $(PROGRAM_NAME_C)
	gcc -Wall -Wextra \
  $(PROGRAM_NAME_C) \
  $(OPT_LEVEL) \
  $(MATH_LIB) \
  -o $(EXECUTABLE)

clean:
	rm main
