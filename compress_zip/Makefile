CC = x86_64-w64-mingw32-gcc
STRIP = x86_64-w64-mingw32-strip

SOURCE = compress_zip.c
OUTPUT = compress_zip.o

CFLAGS = -Os -Wall -DBOF

all:
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OUTPUT)
	$(STRIP) --strip-unneeded $(OUTPUT)

clean:
	rm -f $(OUTPUT)
