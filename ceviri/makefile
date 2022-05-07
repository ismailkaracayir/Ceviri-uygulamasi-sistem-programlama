cc=gcc



all: ceviri lib/libfdr.a
	@echo basarili....

ceviri: main.o fields.o dllist.o jval.o
	cc ./obj/fields.o ./obj/main.o ./obj/dllist.o obj/jval.o -o ./bin/ceviri

main.o:
	cc -I "./include" -c ./src/main.c -o ./obj/main.o

fields.o:
	cc -I "./include" -c ./src/fields.c -o ./obj/fields.o
jval.o:
	cc -I "./include" -c ./src/jval.c -o ./obj/jval.o	

dllist.o: jval.o
	cc -I "./include" -c ./src/dllist.c -o ./obj/dllist.o
	





lib/libfdr.a:obj/jval.o obj/dllist.o obj/fields.o 
	ar ru lib/libfdr.a obj/jval.o obj/dllist.o obj/fields.o 
	ranlib lib/libfdr.a

clean:
	rm -rf *o ./obj/* lib/* ./bin/*
	@echo obj/lib dosyalar silindi..



	








