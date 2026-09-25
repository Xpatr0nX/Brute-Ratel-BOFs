make:
	mkdir -p out64 out86
	x86_64-w64-mingw32-gcc timestamp.c -c -o out64/timestamp64.o
	i686-w64-mingw32-gcc timestamp.c -c -o out86/timestamp86.o

clean:
	rm -rf out64 out86
