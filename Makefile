all: nchoosek

nchoosek: nchoosek.c
	gcc -o nchoosek nchoosek.c -lgmp -lm
