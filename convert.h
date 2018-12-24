#ifndef _CONVERT_
#define _CONVERT_

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
int32_t valeur_big_endian32 (int32_t value);

//si la valeur à convertir est de type int16_t
int16_t valeur_big_endian16 (int16_t value);

#endif
