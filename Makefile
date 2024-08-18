# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I include/

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Output executable name
TARGET = $(BINDIR)/mega_sena_manager

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Build the final executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# PHONY targets to prevent conflicts with files of the same name
.PHONY: all clean