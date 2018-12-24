#ifndef _PRINTR_
#define _PRINTR_

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

#include "print_section.h"
#include "print_header.h"
#include "print_symbole.h"
#include "elf.h"
#include "convert.h"

//lis la table de reimplantation et le met dans la table de section
Elf32_Rela *lecture_reimplantation(FILE *fd, Elf32_Shdr *table_section);

//recupere la valeur de la section ou symbole ou faire la reimplantation
Elf32_Addr getValueReimplantation(Elf32_Sym *tableSymbole, Elf32_Word info);

//recupere le nom de la section ou symbole ou faire la reimplantation
char *getSectionOrSymboleName(Elf32_Shdr *table_section, Elf32_Sym *tableSymbole, Elf32_Word info);

#endif
