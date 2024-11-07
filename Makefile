CC=g++
LIBS=-lSDL2 -L.
# add this tag to CFLAGS to disable the cmd prompt -mwindows
CFLAGS=-Wall -Wextra -Wno-unused-parameter

INCLUDE_DIR=./include
SOURCE_DIR=./source
BUILD_BIR=./build

INCLUDE=-I$(INCLUDE_DIR) \
	-I$(INCLUDE_DIR)/objects \
	-I$(INCLUDE_DIR)/objects/base \
	-I$(INCLUDE_DIR)/objects \
	-I$(INCLUDE_DIR)/objects/test \
	-I$(INCLUDE_DIR)/sprites \
	-I$(INCLUDE_DIR)/types \
	-I$(INCLUDE_DIR)/utils \

SOURCE=$(SOURCE_DIR)/Game.cpp \
	$(SOURCE_DIR)/objects/base/PhysicsObject.cpp \
	$(SOURCE_DIR)/objects/test/MapEditor.cpp \
	$(SOURCE_DIR)/objects/test/Rectangle.cpp \
	$(SOURCE_DIR)/objects/test/TestBox.cpp \
	$(SOURCE_DIR)/objects/Cursor.cpp \
	$(SOURCE_DIR)/objects/TileMap.cpp \
	$(SOURCE_DIR)/objects/ViewPort.cpp \
	$(SOURCE_DIR)/sprites/AnimatedSprite.cpp \
	$(SOURCE_DIR)/sprites/Sprite.cpp \
	$(SOURCE_DIR)/sprites/SpriteSheet.cpp \
	$(SOURCE_DIR)/sprites/TileSet.cpp \
	$(SOURCE_DIR)/utils/BufferIO.cpp \
	$(SOURCE_DIR)/utils/GameWindow.cpp \
	$(SOURCE_DIR)/utils/Vector2.cpp

OBJS:= $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_BIR)/%.o, $(SOURCE))
# DEPS=$(OBJS:.o=.d)

main: $(OBJS)
	$(CC) $(CFLAGS) -o main.exe $(SOURCE_DIR)/main.cpp $^ $(INCLUDE) $(LIBS) 

$(BUILD_BIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Include the dependency files
# -include $(DEPS)

.PHONY: clean

clean:
	rm -rf $(BUILD_BIR)
	rm -f main.exe