#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <byteswap.h>
#include "print_header.h"

//valeur magique de e_ident
void aff_magique (Elf32_Ehdr *entete) {
	for (int i = 0; i < 15 ; i++) 
		printf ("%02x ",entete -> e_ident [i]);
	printf ("\n");
}

//affichage du type de la classe
void aff_class_type (Elf32_Ehdr *entete) {
	if (entete -> e_ident [EI_CLASS] == ELFCLASSNONE) printf (" ici ELF_NONE \n");
	if (entete -> e_ident [EI_CLASS] == ELFCLASS32) printf ("ici ELF32\n");
	if (entete -> e_ident [EI_CLASS] == ELFCLASS64) printf ("ici ELF64\n");
}
//affichage du codage big litle ou none
void aff_codage_type (Elf32_Ehdr *entete) {
	if (entete -> e_ident [EI_DATA] == ELFDATANONE)
		printf ("Invalid encodage");
    else if (entete -> e_ident [EI_DATA] == ELFDATA2MSB) 
		printf ("complément à 1,sytème à octets de poids faible d'abord (Big endian)");
	else if (entete -> e_ident [EI_DATA] == ELFDATA2LSB) 
		printf ("complément à 2,sytème à octets de poids faible d'abord (little endian)");
	printf ("\n");
}
//affichage de la version courant ou none
void aff_version (Elf32_Ehdr *entete) {
	if (entete -> e_ident [EI_VERSION] == EV_NONE) printf ("%d (invalid)\n",entete -> e_ident [EI_VERSION]);
	if (entete -> e_ident [EI_VERSION] == EV_CURRENT) printf ("%d (current)\n",entete -> e_ident [EI_VERSION]);
}
//système d'exploitation
void aff_system (Elf32_Ehdr *entete) {
	if (entete -> e_ident [EI_OSABI] == ELFOSABI_SYSV) printf("UNIX - System V \n");
	if (entete -> e_ident [EI_OSABI] == ELFOSABI_ARM)  printf("Architecture ARM\n");
	if (entete -> e_ident [EI_OSABI] == ELFOSABI_LINUX)printf("LINUX - System \n");
	if (entete -> e_ident [EI_OSABI] == ELFOSABI_TRU64)printf("UNIX TRU64\n");
}
//typ de fuchier
void aff_type (Elf32_Ehdr *entete) {
	if (entete -> e_type == ET_NONE) printf ("NONE (Type du fichier inconnu)");
	if (entete -> e_type == ET_REL) printf ("REL (Fichier de réadressage)");
	if (entete -> e_type == ET_EXEC) printf ("EXE (Fichier exécutable)");
	if (entete -> e_type == ET_DYN) printf ("DYN (objet partagé");
	if (entete -> e_type == ET_CORE) printf ("CORE (Fichier core");
	printf ("\n");
}

//version 
int aff_e_version (Elf32_Ehdr *entete) {
	if (entete -> e_version == EV_NONE) return 0;
 	else if (entete -> e_version == EV_CURRENT) return 1;
 	else return -1;
}

// la machine 
void aff_machine (Elf32_Ehdr *entete) {

		if  (EM_NONE == entete -> e_machine)
			printf("machine inconne");
		if (EM_M32 == entete -> e_machine)
			printf("AT&T WE 32100");
		if (EM_SPARC == entete -> e_machine)
			printf("Sun Microsystems SPARC");
		if (EM_386 == entete -> e_machine)
			printf("Intel 80386");
		if (__bswap_16(EM_68K) == entete -> e_machine)
			printf("Motorola 68000");
		if (entete -> e_machine == EM_88K)
			printf("Motorola 88000");
		if (entete -> e_machine == EM_860)
			printf("Intel 80860");
		if (entete -> e_machine == EM_MIPS)
			printf("MIPS RS3000");
		if (entete -> e_machine == EM_PARISC)
			printf("HP/PA");
		if (entete -> e_machine == EM_SPARC32PLUS)
			printf("SPARC avec jeu d'instruction étendu");
		if (entete -> e_machine == EM_PPC)
			printf("PowerPC");
		if (entete -> e_machine == EM_PPC64)
			printf("PowerPC 64 bits");
		if (entete -> e_machine == EM_S390)
			printf("IBM S/390");
		if (entete -> e_machine == EM_ARM)
			printf("ARM RISC");
		if (entete -> e_machine == EM_SH)
			printf("Renesas SuperH");
		if (entete -> e_machine == EM_SPARCV9)
			printf("SPARCC v9 64 bits");
		if (entete -> e_machine == EM_IA_64)
			printf("Intel Itanium");
		if (entete -> e_machine == EM_X86_64)
			printf("AMD x86-64");
		if (entete -> e_machine == EM_VAX)
  	printf("DEC Vax");				
	printf("\n");
}
//fonction qui affiche l'entête du fichier
void affiche_entete (Elf32_Ehdr *entete) {
	printf ("En-tête ELF:\n");
	printf (" Magique:\t\t");
		aff_magique (entete);
    printf (" Classe:\t\t\t");
		aff_class_type (entete);
	printf (" Données:\t\t\t");
		aff_codage_type (entete);
	printf (" Version:\t\t\t");
		aff_version (entete);
	printf (" OS/ABI:\t\t\t");
		aff_system (entete);
	printf (" Version ABI:\t\t\t%d\n",entete -> e_ident [EI_ABIVERSION]);
	printf (" Type:\t\t\t\t");
		aff_type (entete);
	printf (" Machine:\t\t\t");
		aff_machine (entete);
	printf (" Version:\t\t\t0x%d\n",aff_e_version (entete));
	printf (" Adresse du point d'entrée:\t%d\n",entete -> e_entry);
	
	printf (" Début des en-têtes de programme:\t%d (octets dans le fichier)\n",entete->e_phoff);
	printf (" Début des en_têtes de section:\t\t%d (octets dans le fichier)\n",entete -> e_shoff);
	printf (" Fanions:\t\t\t\t%d\n",entete-> e_flags);
	printf (" Taille de cet en-tête:\t\t\t %d (octets)\n",entete -> e_ehsize);
	printf (" Taille de l'en-tête du programme:\t%d (octets)\n",entete ->e_phentsize);
	printf (" Nombre d'en-tête du programme:\t\t%d\n",entete -> e_phnum);
	printf (" Taille des en-têtes de section:\t%d(octets)\n",entete -> e_shentsize);
	printf (" Nombre d'en-têtes de section:\t\t%d\n",entete -> e_shnum);
	printf (" Table d'indexes des chaines d'en-tête de section:\t%d\n",entete -> e_shstrndx);
    printf ("\n\n");
}
