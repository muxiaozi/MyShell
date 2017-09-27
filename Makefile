OBJ := obj/mydef.o obj/myerrno.o obj/myhandle_cmd.o obj/mylist.o
INC := -I include
DIRS := bin/ obj/

all: mydirs bin/mydef

bin/mydef: $(OBJ)
	gcc -o $@ $(OBJ) $(INC)

obj/mydef.o: src/mydef.c include/myhandle_cmd.h
	gcc -o $@ -c src/mydef.c $(INC)

obj/myerrno.o: src/myerrno.c include/myerrno.h 
	gcc -o $@ -c src/myerrno.c $(INC)

obj/myhandle_cmd.o: src/myhandle_cmd.c include/myerrno.h include/myhandle_cmd.h include/mylist.h
	gcc -o $@ -c src/myhandle_cmd.c $(INC)

obj/mylist.o: src/mylist.c include/mylist.h include/myerrno.h
	gcc -o $@ -c src/mylist.c $(INC)

mydirs:
	@mkdir -p $(DIRS)

clean:
	-rm -f obj/*

distclean: clean
	-rm -f bin/*

.PHONY: all clean distclean mydirs
