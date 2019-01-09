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
#include "print_symbole.h"
#include "convert.h"
#include "elf.h"
#include "print_reimplantation.h"

#define OFFSET_INFO_SEP "     "
#define INFO_TYPE_SEP "    "
#define TYPE_VALUE_SEP "            "
#define VALUE_NAME_SEP "  "

//test si cest un type dynamique
int is_dynamique(Elf32_Word section_type)
{
	return (section_type == SHT_REL); 
}


//nombre de réadressage
int nb_dyn_sym(FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section [])
{
	int total=0;
	char *tampon_table ;
	//on récupère le tampon de début
	tampon_table = lecture_section (fd,table_section [entete.e_shstrndx]);
	if (tampon_table == NULL) {
		printf ("Erreur tampon\n");
	}	
	//parcours et compte le nombre de symbole dynamique
	for (int i = 0; i < entete.e_shnum ; i++) {
		if(is_dynamique(table_section[i].sh_type))
			total++;
	}
	return total;
}

//lecture table reloc
Elf32_Rel *read_reloc_table(FILE * f, Elf32_Off tableOffset, Elf32_Word tableSize)
{
    Elf32_Rel *relocTable;
    int size;

    rewind(f);
    fseek(f, tableOffset, SEEK_SET);

    /* Allocation de la table */
    relocTable = malloc(tableSize);

    /* Size */
    size = tableSize / sizeof(Elf32_Rel);

    /* Lecture de la table dans f */
    fread(relocTable, sizeof(Elf32_Rel), size, f);

    return relocTable;
}

Elf32_Rel *read_reloc_index_table(FILE * f, Elf32_Shdr * sectionHeaderTable, int tableIndex)
{
    return read_reloc_table(f, sectionHeaderTable[tableIndex].sh_offset, sectionHeaderTable[tableIndex].sh_size);
}

void print_reloc_type(Elf32_Word type)
{
    switch (type) {
    case R_ARM_NONE:
        printf("R_ARM_NONE");
        break;
    case R_ARM_PC24:
        printf("R_ARM_PC24");
        break;
    case R_ARM_ABS32:
        printf("R_ARM_ABS32");
        break;
    case R_ARM_REL32:
        printf("R_ARM_REL32");
        break;
    case R_ARM_PC13:
        printf("R_ARM_PC13");
        break;
    case R_ARM_ABS16:
        printf("R_ARM_ABS16");
        break;
    case R_ARM_ABS12:
        printf("R_ARM_ABS12");
        break;
    case R_ARM_THM_ABS5:
        printf("R_ARM_THM_ABS5");
        break;
    case R_ARM_ABS8:
        printf("R_ARM_ABS8");
        break;
    case R_ARM_SBREL32:
        printf("R_ARM_SBREL32");
        break;
    case R_ARM_THM_PC22:
        printf("R_ARM_THM_PC22");
        break;
    case R_ARM_THM_PC8:
        printf("R_ARM_THM_PC8");
        break;
    case R_ARM_AMP_VCALL9:
        printf("R_ARM_AMP_VCALL9");
        break;
    case R_ARM_TLS_DESC:
        printf("R_ARM_TLS_DESC");
        break;
    case R_ARM_THM_SWI8:
        printf("R_ARM_THM_SWI8");
        break;
    case R_ARM_XPC25:
        printf("R_ARM_XPC25");
        break;
    case R_ARM_THM_XPC22:
        printf("R_ARM_THM_XPC22");
        break;
    case R_ARM_TLS_DTPMOD32:
        printf("R_ARM_TLS_DTPMOD32");
        break;
    case R_ARM_TLS_DTPOFF32:
        printf("R_ARM_TLS_DTPOFF32");
        break;
    case R_ARM_TLS_TPOFF32:
        printf("R_ARM_TLS_TPOFF32");
        break;
    case R_ARM_COPY:
        printf("R_ARM_COPY");
        break;
    case R_ARM_GLOB_DAT:
        printf("R_ARM_GLOB_DAT");
        break;
    case R_ARM_JUMP_SLOT:
        printf("R_ARM_JUMP_SLOT");
        break;
    case R_ARM_RELATIVE:
        printf("R_ARM_RELATIVE");
        break;
    case R_ARM_GOTOFF:
        printf("R_ARM_GOTOFF");
        break;
    case R_ARM_GOTPC:
        printf("R_ARM_GOTPC");
        break;
    case R_ARM_GOT32:
        printf("R_ARM_GOT32");
        break;
    case R_ARM_PLT32:
        printf("R_ARM_PLT32");
        break;
    case R_ARM_CALL:
        printf("R_ARM_CALL");
        break;
    case R_ARM_JUMP24:
        printf("R_ARM_JUMP24");
        break;
    case R_ARM_ALU_PCREL_7_0:
        printf("R_ARM_ALU_PCREL_7_0");
        break;
    case R_ARM_ALU_PCREL_15_8:
        printf("R_ARM_ALU_PCREL_15_8");
        break;
    case R_ARM_ALU_PCREL_23_15:
        printf("R_ARM_ALU_PCREL_23_15");
        break;
    case R_ARM_LDR_SBREL_11_0:
        printf("R_ARM_LDR_SBREL_11_0");
        break;
    case R_ARM_ALU_SBREL_19_12:
        printf("R_ARM_ALU_SBREL_19_12");
        break;
    case R_ARM_ALU_SBREL_27_20:
        printf("R_ARM_ALU_SBREL_27_20");
        break;
    case R_ARM_V4BX:
        printf("R_ARM_V4BX");
        break;
    case R_ARM_TLS_GOTDESC:
        printf("R_ARM_TLS_GOTDESC");
        break;
    case R_ARM_TLS_CALL:
        printf("R_ARM_TLS_CALL");
        break;
    case R_ARM_TLS_DESCSEQ:
        printf("R_ARM_TLS_DESCSEQ");
        break;
    case R_ARM_THM_TLS_CALL:
        printf("R_ARM_THM_TLS_CALL");
        break;
    case R_ARM_GNU_VTENTRY:
        printf("R_ARM_GNU_VTENTRY");
        break;
    case R_ARM_GNU_VTINHERIT:
        printf("R_ARM_GNU_VTINHERIT");
        break;
    case R_ARM_THM_PC11:
        printf("R_ARM_THM_PC11");
        break;
    case R_ARM_THM_PC9:
        printf("R_ARM_THM_PC9");
        break;
    case R_ARM_TLS_GD32:
        printf("R_ARM_TLS_GD32");
        break;
    case R_ARM_TLS_LDM32:
        printf("R_ARM_TLS_LDM32");
        break;
    case R_ARM_TLS_LDO32:
        printf("R_ARM_TLS_LDO32");
        break;
    case R_ARM_TLS_IE32:
        printf("R_ARM_TLS_IE32");
        break;
    case R_ARM_TLS_LE32:
        printf("R_ARM_TLS_LE32");
        break;
    case R_ARM_THM_TLS_DESCSEQ:
        printf("R_ARM_THM_TLS_DESCSEQ");
        break;
    case R_ARM_IRELATIVE:
        printf("R_ARM_IRELATIVE");
        break;
    case R_ARM_RXPC25:
        printf("R_ARM_RXPC25");
        break;
    case R_ARM_RSBREL32:
        printf("R_ARM_RSBREL32");
        break;
    case R_ARM_THM_RPC22:
        printf("R_ARM_THM_RPC22");
        break;
    case R_ARM_RREL32:
        printf("R_ARM_RREL32");
        break;
    case R_ARM_RABS22:
        printf("R_ARM_RABS22");
        break;
    case R_ARM_RPC24:
        printf("R_ARM_RPC24");
        break;
    case R_ARM_RBASE:
        printf("R_ARM_RBASE");
        break;
    case R_ARM_NUM:
        printf("R_ARM_NUM");
        break;
    default:
        printf("UNKNOWN");
    }
}

void print_reloc(FILE* f, Elf32_Rel reloc, Elf32_Sym* symtab)
{
    Elf32_Word info = valeur_big_endian32(reloc.r_info);
    Elf32_Addr offset = valeur_big_endian32(reloc.r_offset);
    Elf32_Word sym = ELF32_R_SYM(info);
    
    /* Offset */
    printf(" %08x", offset);

    /* Info */
    printf("  %08x ", info);
    
    //type
    print_reloc_type(ELF32_R_TYPE(info));
    
    //sym
   
    if(sym!=0)
    {
		//tampon = lecture_section (f,table_section [sym]);
		printf("\t    %08x    ", valeur_big_endian32(symtab[sym].st_value));
	}
}

//Affichage de la table des sections
void get_ln (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []) {
	char *tampon_table ;
	Elf32_Rel *relocTable;
	Elf32_Sym *symtab;
	
	//tester sil exite un symbole dynamique
	if(nb_dyn_sym(fd, entete, table_section) == 0)
	{
		printf("il nya pas de readressage dans le fichier\n");
		exit(0);
	}
	
	//on récupère le tampon de début
	tampon_table = lecture_section (fd,table_section [entete.e_shstrndx]);
	if (tampon_table == NULL) {
		printf ("Erreur tampon\n");
	}
	
	//Affiche le contenu d'une section dont le nom est donné en paramètre
	for (int i = 0; i < entete.e_shnum ; i++) {
		if(is_dynamique(table_section[i].sh_type))
		{
			if(table_section[i].sh_link !=0) 
			{
				
				symtab = (Elf32_Sym *) lecture_section (fd,table_section[i]);
				//nombre Entree
				int nbEntree = table_section[i].sh_size/sizeof(Elf32_Rel);	
				printf("Section de réadressage %s à l'adresse de decalage %06x contenant %d entrée\n", tampon_table +table_section[i].sh_name, table_section[i].sh_offset, nbEntree);
				printf(" Offset%sInfo%sType%sSym.value%sSym.name\n",
           OFFSET_INFO_SEP, INFO_TYPE_SEP, TYPE_VALUE_SEP, VALUE_NAME_SEP);
				relocTable = read_reloc_index_table(fd, table_section, i); 	
				for(int j=0; j<nbEntree; j++)
				{
					print_reloc(fd, relocTable[j], symtab);
					printf ("\n");
				}
			}
		}

	}
}







