revert.exe : revert_lib.c revert_lib.h revert.c
	gcc `pkg-config --cflags --libs glib-2.0` -Wall -Wextra revert_lib.c revert_lib.h revert.c -o revert.exe

test : revert_lib.c revert_lib.h test.c
	gcc `pkg-config --cflags --libs glib-2.0` -g3 -Wall -Wextra revert_lib.c revert_lib.h test.c -o test.exe
	./test.exe

clean :
	if [ -f revert.exe ]; then rm revert.exe; fi;
	if [ -f test.exe ]; then rm test.exe; fi;
