CC=g++
OBJS=$(ODIR)/Game.o $(ODIR)/GameWindow.o $(ODIR)/Rectangle.o
CFLAGS=-I. -I./include -L./lib 
# add this tag to disable the cmd prompt -mwindows
LIBS=-lSDL2
ODIR=obj
INCLUDE_DIR=include
SOURCE_DIR=source

main: $(OBJS)
	$(CC) -o main.exe $(SOURCE_DIR)/main.cpp $(OBJS) $(CFLAGS) $(LIBS)

$(ODIR)/Game.o: $(SOURCE_DIR)/Game.cpp $(INCLUDE_DIR)/Game.h $(INCLUDE_DIR)/Rectangle.h $(INCLUDE_DIR)/GameWindow.h $(INCLUDE_DIR)/GameObject.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/Rectangle.o: $(SOURCE_DIR)/Rectangle.cpp $(INCLUDE_DIR)/Rectangle.h $(INCLUDE_DIR)/GameWindow.h $(INCLUDE_DIR)/GameObject.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/GameWindow.o: $(SOURCE_DIR)/GameWindow.cpp $(INCLUDE_DIR)/GameWindow.h $(INCLUDE_DIR)/GameObject.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	del /q /f $(ODIR)\*.o
	del /q /f main.exe