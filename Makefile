OBJ = obj/mydef.o obj/myerrno.o obj/myhandle_cmd.o 
INC = -I include

mydef: $(OBJ) 
	gcc -o $@ $(OBJ) $(INC)

obj/mydef.o: src/mydef.c include/*
	gcc -o $@ -c src/mydef.c $(INC)

obj/myerrno.o: src/myerrno.c include/* 
	gcc -o $@ -c src/myerrno.c $(INC)

obj/myhandle_cmd.o: src/myhandle_cmd.c include/*
	gcc -o $@ -c src/myhandle_cmd.c $(INC)

clean:
	-rm -f $(OBJ)

distclean: clean
	-rm -f mydef

.PHONY: clean distclean
