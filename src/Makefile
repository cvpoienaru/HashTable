CC = cl
CFLAGS = /W3 /O2 /D_CRT_SECURE_NO_DEPRECATE

build: hashtable.exe

hashtable.exe: main.obj hash.obj list.obj bucket.obj hashtable.obj
	$(CC) $(CFLAGS) $** /Fe$@

main.obj: main.c
hash.obj: hash.h hash.c
list.obj: list.h list.c
bucket.obj: bucket.h bucket.c
hashtable.obj: hashtable.h hashtable.c

clean:
	del *.obj
	del *.exe
