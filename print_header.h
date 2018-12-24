#ifndef _PRINTH_
#define _PRINTH_

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

//valeur magique de e_ident
void aff_magique (Elf32_Ehdr *entete);

//affichage du type de la classe
void aff_class_type (Elf32_Ehdr *entete);

//affichage du codage big litle ou none
void aff_codage_type (Elf32_Ehdr *entete);

//affichage de la version courant ou none
void aff_version (Elf32_Ehdr *entete);

//système d'exploitation
void aff_system (Elf32_Ehdr *entete);

//typ de fuchier
void aff_type (Elf32_Ehdr *entete);

//version 
int aff_e_version (Elf32_Ehdr *entete); 

// la machine 
void aff_machine (Elf32_Ehdr *entete);

//fonction qui affiche l'entête du fichier
void affiche_entete (Elf32_Ehdr *entete);

#endif
