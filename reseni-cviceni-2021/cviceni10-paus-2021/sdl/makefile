EXEC = sdl
OBJ_DIR = ./build/o
BUILD_DIR = ./bin
SRC_DIR = ./src
SRC_FILES = SDLScreen.cpp main.cpp SDLBitmap.cpp

SRCS = $(SRC_FILES:%=$(SRC_DIR)/%)
OBJS = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS = -std=c++14 -Wall -pedantic
LINKERFLAGS = -l SDL2

all: $(OBJS)
	@echo -n Linking executable: $(BUILD_DIR)/$(EXEC)
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CPPFLAGS) $(OBJS) -o $(BUILD_DIR)/$(EXEC) $(LINKERFLAGS)
	@echo " OK."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo -n Compiling source: $<
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo " OK."

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(BUILD_DIR)
	@echo Cleaned.

run:
	$(BUILD_DIR)/$(EXEC)
