CC=gcc
GTK_CFLAGS=`pkg-config --cflags gtk+-3.0`
GTK_LIBS=`pkg-config --libs gtk+-3.0`
FILENAME=gtk-reversi

compile:
	$(CC) $(GTK_CFLAGS) $(GTK_LIBS) $(FILENAME).c -o $(FILENAME)

run: compile
	./$(FILENAME)