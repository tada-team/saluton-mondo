revert.exe : revert_lib.c revert_lib.h revert.c
	gcc -Wall -Wextra revert_lib.c revert_lib.h revert.c `pkg-config --cflags --libs glib-2.0` -o revert.exe

test : revert_lib.c revert_lib.h test.c
	gcc -g3 -Wall -Wextra revert_lib.c revert_lib.h test.c `pkg-config --cflags --libs glib-2.0` -o test.exe
	./test.exe

clean :
	if [ -f revert.exe ]; then rm revert.exe; fi;
	if [ -f test.exe ]; then rm test.exe; fi;
