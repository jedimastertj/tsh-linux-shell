all:
	gcc main.c -o main
	gcc cat.c -o cat
	gcc date.c -o date
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm

clean:
	rm -f main
	rm -f cat
	rm -f date
	rm -f ls
	rm -f mkdir
	rm -f rm
