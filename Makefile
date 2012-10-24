all: nchoosek_native nchoosek_gmp

nchoosek_native: nchoosek.c
	# native version
	gcc -o nchoosek_native nchoosek.c -DUSE_GMP=0

nchoosek_gmp: nchoosek.c
	# GMP version
	gcc -o nchoosek_gmp nchoosek.c -DUSE_GMP=1 -lgmp
