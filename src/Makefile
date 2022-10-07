PROGRAM_NAME_C = ipc.c
OPT_LEVEL = -g

# compile all
all: build_c

build_c: $(PROGRAM_NAME_C)
	gcc -o main -Wall -Wextra \
  $(PROGRAM_NAME_C) \
  $(OPT_LEVEL) \
  $(MATH_LIB)

clean:
	rm main
