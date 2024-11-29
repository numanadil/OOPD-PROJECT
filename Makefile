# Variables
CC = g++
CFLAGS = -std=c++11
LIBRARY_NAME = WiFiSimulator.dll
EXECUTABLE_NAME = wifi4.exe
SOURCE_DIR = .
BUILD_DIR = build

# Source Files
LIBRARY_SRC = $(SOURCE_DIR)/WiFiSimulator.cpp
EXEC_SRC = $(SOURCE_DIR)/wifi4.cpp

# Object Files
LIBRARY_OBJ = $(BUILD_DIR)/WiFiSimulator.o
EXEC_OBJ = $(BUILD_DIR)/wifi4.o

# Targets
all: $(EXECUTABLE_NAME)

# Create the shared library (DLL)
$(LIBRARY_NAME): $(LIBRARY_OBJ)
	$(CC) -shared -o $(LIBRARY_NAME) $(LIBRARY_OBJ)

# Compile WiFiSimulator.cpp into object file
$(LIBRARY_OBJ): $(LIBRARY_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -c $(LIBRARY_SRC) -o $(LIBRARY_OBJ)

# Compile wifi4.cpp and link it with WiFiSimulator.dll
$(EXECUTABLE_NAME): $(EXEC_SRC) $(LIBRARY_NAME)
	$(CC) $(CFLAGS) $(EXEC_SRC) -o $(EXECUTABLE_NAME) -L. -lWiFiSimulator

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) $(LIBRARY_NAME) $(EXECUTABLE_NAME)

.PHONY: all clean
