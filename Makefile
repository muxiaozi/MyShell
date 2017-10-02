OBJ = obj/mydef.o obj/myerrno.o obj/myhandle_cmd.o obj/mylist.o obj/myserver.o
INC = -I include
DIRS = bin/ obj/

all: $(DIRS) bin/mydef

bin/mydef: $(OBJ)
	cc -o $@ $(OBJ)

obj/mydef.o: src/mydef.c include/myhandle_cmd.h include/myserver.h
	cc -o $@ -c $< $(INC)

obj/myerrno.o: src/myerrno.c include/myerrno.h
	cc -o $@ -c $< $(INC)

obj/myhandle_cmd.o: src/myhandle_cmd.c include/myerrno.h include/myhandle_cmd.h include/mylist.h
	cc -o $@ -c $< $(INC)

obj/mylist.o: src/mylist.c include/mylist.h include/myerrno.h
	cc -o $@ -c $< $(INC)

obj/myserver.o: src/myserver.c include/myserver.h include/myerrno.h
	cc -o $@ -c $< $(INC)

$(DIRS):
	mkdir -p $(DIRS)

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) bin/*

.PHONY: all clean distclean
