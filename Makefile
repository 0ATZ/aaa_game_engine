
INCLUDE_DIR=./include
SOURCE_DIR=./source
ODIR=./obj

INCLUDE=-I$(INCLUDE_DIR)
CC=g++
LIBS=-lSDL2 -L.
# add this tag to CFLAGS to disable the cmd prompt -mwindows
CFLAGS=-Wall -Wextra -Wno-unused-parameter

OBJS=$(ODIR)/Game.o $(ODIR)/GameWindow.o $(ODIR)/Rectangle.o \
	$(ODIR)/Sprite.o $(ODIR)/TileSet.o $(ODIR)/TileMap.o \
	$(ODIR)/ViewPort.o $(ODIR)/PhysicsObject.o $(ODIR)/Vector2.o \
	$(ODIR)/BufferIO.o $(ODIR)/SpriteSheet.o $(ODIR)/AnimatedSprite.o \
	$(ODIR)/TestBox.o $(ODIR)/Cursor.o

DEPS=$(OBJS:.o=.d)

main: $(OBJS)
	$(CC) $(CFLAGS) -o main.exe $(SOURCE_DIR)/main.cpp $^ $(INCLUDE) $(LIBS) 

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ $(INCLUDE)

# Include the dependency files
-include $(DEPS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.d
	rm -f $(ODIR)/*.o
	rm -f main.exe