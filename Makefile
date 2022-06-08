CC := gcc

CCFLAGS := \
	-std=c99                        \
	-g                              \
	-D_DEFAULT_SOURCE               \
	-Wall                           \
	-Wextra                         \
	-Wpointer-arith                 \
	-Wcast-align                    \
	-Wwrite-strings                 \
	-Wswitch-default                \
	-Wunreachable-code              \
	-Winit-self                     \
	-Wmissing-field-initializers    \
	-Wno-unknown-pragmas            \
	-Wstrict-prototypes             \
	-Wundef                         \
	-Wold-style-definition

OBJS := \
	src/file_io.o \
	src/rdt.o \
	src/utils.o

TEST_TARGETS := \
	test_file_io \
	test_rdt \
	test_utils

all : client server

test : $(TEST_TARGETS)

client : % : src/client.o $(OBJS)
	$(CC) -o bin/$@ $^ $(CCFLAGS)

server : % : src/server.o $(OBJS)
	$(CC) -o bin/$@ $^ $(CCFLAGS)

src/%.o : src/%.c
	$(CC) -I src -c -o $@ $^ $(CCFLAGS)

$(TEST_TARGETS) : % : test/%.o $(OBJS)
	$(CC) -o runner/$@ $^

test/%.o : test/%.c
	$(CC) -I src -I test -c -o $@ $^

clean :
	rm -f src/*.o
	rm -f test/*.o
	rm -f bin/*
	rm -f runner/*
