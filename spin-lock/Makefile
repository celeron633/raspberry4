TARGET := spin-lock-test
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
C_FLAGS := -Wall -Wextra -g -O0

$(TARGET): $(OBJS)
	gcc $^ -o $@

clean:
	rm -r -f $(OBJS) $(TARGET)

%.o: %.c
	gcc -c $(C_FLAGS) $< -o $@

.phony: clean

