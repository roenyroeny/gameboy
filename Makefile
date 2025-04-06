GBDK_HOME = ./
CC = $(GBDK_HOME)tools/gbdk/bin/lcc
COMPILER_FLAGS = -std=c99 -Wall -g
SRCS = $(wildcard ./src*.c)
OBJS = $(patsubst %.c, ./build/%.o, $(SRCS))
INCLUDE_PATHS = -Iinclude 

TARGET = gameboy.gb

all: $(TARGET)

# Make a .GB ROM in ./build (create it if it does not exist), and remove all of the intermediate files
$(TARGET): $(OBJS)
	mkdir -p build
	$(CC) -o ./build/$@ $(OBJS)
	rm -f ./build/*.lst ./build/*.sym ./build/*.asm ./build/*.ihx

./build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

# Delete all of the generated files including the ROM
clean:
	rm -f ./build/*.o ./build/*.lst ./build/*.map ./build/*~ ./build/*.rel ./build/*.cdb ./build/*.lnk ./build/*.sym ./build/*.asm ./build/*.noi ./build/*.ihx ./build/$(TARGET)
