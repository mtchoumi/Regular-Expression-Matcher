OBJS := objdir.o objfile.o objmatch.o

objdir.o: objdir.c
	gcc -c objdir.c -o objdir.o
objfile.o: objfile.c
	gcc -c objfile.c -o objfile.o
objmatch.o: objmatch.c
	gcc -c objmatch.c -o objmatch.o

static_libs: ${OBJS}
	ar rcs libobjdata.a ${OBJS}

finds.o: finds.c
	gcc -c finds.c -o finds.o
finds: finds.o static_libs
	gcc finds.o ./libobjdata.a -o finds
my_printf.o: my_printf.c
	gcc -c my_printf.c -o my_printf.o
my_printf: my_printf.o static_libs
	gcc my_printf.o ./libobjdata.a -o my_printf
clean:
	rm -f finds.o my_printf.o my_printf finds ${OBJS} libobjdata.a
