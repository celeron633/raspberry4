TARGET := list_test
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
C_FLAGS := -g -O0

$(TARGET): $(OBJS)
	gcc $^ -o $@

clean:
	rm -r -f $(OBJS) $(TARGET)

%.o: %.c
	gcc -c $(C_FLAGS) $< -o $@

.phony: clean

