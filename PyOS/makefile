# PyOS Pro main makefile

# Define the compiler and flags
CC = gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

# Define the assembler
AS = nasm
ASFLAGS = -f elf64

# Define the target binary
TARGET = kernel.bin

# Define the source files
C_SOURCES = \
    ./PyOS/interpret/interpreter/interpreter_entry.c \
    ./PyOS/interpret/interpreter/interpreter.c \
    ./PyOS/boot/bootmngr.c \
    ./PyOS/boot/arm/arm_bootloader.c \
    ./PyOS/boot/x86/x86_bootloader.c \
    ./PyOS/src/error_handler.c \
    ./PyOS/src/kernel.c \
    ./PyOS/src/bmp.c \
    ./PyOS/src/display.c \
    ./PyOS/setup/setup.c

ASM_SOURCES = ./PyOS/src/kernel_entry.ASM

# Define the object files
OBJECTS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.ASM=.o)

# Define the build directory
BUILD_DIR = build

# Define the ISO directory
ISO_DIR = iso

# Define the ISO file
ISO_FILE = $(ISO_DIR)/PyOSpro.iso

# Default target
all: $(ISO_FILE)

# Compile C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble ASM source files
%.o: %.ASM
	$(AS) $(ASFLAGS) $< -o $@

# Link the kernel binary
$(TARGET): $(OBJECTS)
	$(CC) -T ./PyOS/src/linker.ld -o $(TARGET) $(LDFLAGS) $(OBJECTS)

# Create the ISO file
$(ISO_FILE): $(TARGET)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(TARGET) $(ISO_DIR)/boot/
	cp ./PyOS/src/splash/PYOSSPLASH.bmp $(ISO_DIR)/boot/
	cp ./PyOS/setup/config.ini $(ISO_DIR)/boot/
	cp ./PyOS/setup/headers/ini.h $(ISO_DIR)/boot/
	cp ./PyOS/.devcontainer/devcontainer.json $(ISO_DIR)/boot/
	cp ./PyOS/.devcontainer/dockerfile $(ISO_DIR)/boot/
	cp ./PyOS/interpret/script/main.py $(ISO_DIR)/boot/
	cp ./PyOS/interpret/modules/modules/PyOS\ module/PyOS.py $(ISO_DIR)/boot/
	cp ./PyOS/boot/bootmngr.c $(ISO_DIR)/boot/
	cp ./devtools/index.py $(ISO_DIR)/boot/
	cp grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf $(ISO_DIR)

# Run the kernel using QEMU
run: $(ISO_FILE)
	qemu-system-x86_64 -cdrom $(ISO_FILE)

.PHONY: all clean run