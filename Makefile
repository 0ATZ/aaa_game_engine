CC=g++
OBJS=$(ODIR)/Game.o $(ODIR)/Renderer.o $(ODIR)/Rectangle.o
CFLAGS=-I. -I./include -L./lib 
# add this tag to disable the cmd prompt -mwindows
LIBS=-lSDL2
ODIR=obj
INCLUDE_DIR=include
SOURCE_DIR=source


$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o main.exe $(SOURCE_DIR)/main.cpp $(OBJS) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del /q /f $(ODIR)\*.o
	del /q /f main.exe