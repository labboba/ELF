CC=gcc
FLAGS=-g -Wall

.PHONY:
	clean
test_affichage: test_affichage.o print_symbole.o print_header.o print_section.o convert.o elf.o
	$(CC) $(FLAGS) -o $@ $^ 

print_header.o: print_header.c print_header.h elf.h
	$(CC) $(FLAGS) -c  $<
	
print_section.o: print_section.c print_section.h elf.h convert.h
	$(CC) $(FLAGS) -c  $<

print_symbole.o: print_symbole.c print_symbole.h convert.h print_section.h elf.h
	$(CC) $(FLAGS) -c  $<
	
test_affichage.o: test_affichage.c print_header.h print_symbole.h print_section.h elf.h convert.h
	$(CC) $(FLAGS) -c  $<
	
convert.o: convert.c convert.h
	$(CC) $(FLAGS) -c  $<
	
elf.o: elf.c elf.h convert.h
	$(CC) $(FLAGS) -c  $<
	
clean: 
	rm *.o test_affichage
