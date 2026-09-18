CC := gcc
CFLAGS := -Wall -Wextra # -O3

MODULES := main \
           position \
           vector \
           list \
           matrix

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

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

out/main: $(addprefix build/,$(addsuffix .o, $(MODULES)))
	$(CC) $(CFLAGS) -o $@ $^ -lraylib -lGL -lm -lpthread -ldl
