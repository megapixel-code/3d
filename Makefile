CC := gcc
CFLAGS := -Wall -Wextra
MODULES := main \
           position \
           vector

.PHONY = all clean
all: build/ out/ out/main
	out/main
clean:
	-rm -r out
	-rm -r build

out/:
	mkdir -p out
build/:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

out/main: $(addprefix build/,$(addsuffix .o, $(MODULES)))
	$(CC) $(CFLAGS) -o $@ $^ -lraylib -lGL -lm -lpthread -ldl
