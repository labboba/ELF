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

/*principe : affiche les 16 premières valeurs du tableau e_ident [] qui correspondent aux valeurs magiques de l’entête du fichier elf.
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_magique (Elf32_Ehdr *entete);

/*principe : affiche le type de la classe correspondante
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_class_type (Elf32_Ehdr *entete);

/*principe : donne des informations sur le codage utilisé par le fichier elf fourni
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_codage_type (Elf32_Ehdr *entete);

/*principe : affichage de la version courant ou none
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_version (Elf32_Ehdr *entete);

/*principe : Indique la version de la machine sur la quelle le fichier à été encodé
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_system (Elf32_Ehdr *entete);

/*principe : Informations sur le type du fichier elf fourni
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_type (Elf32_Ehdr *entete);

/*principe : Indique la version de la machine sur la quelle le fichier à été encodé
  parametre : l'entete du fichier ELF
  valeur de retour : 0 si le fichier a tete encodé sur le meme system sinon 1
*/
int aff_e_version (Elf32_Ehdr *entete);

/*principe : donne le nom de la machine sur la quelle à été encodé le fichier
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void aff_machine (Elf32_Ehdr *entete);

/*principe : cette fonction permet d'afficher toute les informations des methodes precedentes
  parametre : l'entete du fichier ELF
  valeur de retour : aucune
*/
void affiche_entete (Elf32_Ehdr *entete);

#endif
