#include "convert.h"
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

//si la valeur à convertir est de type int32_t
int32_t valeur_big_endian32 (int32_t value) {
	return __bswap_32 (value);
}

//si la valeur à convertir est de type int16_t
int16_t valeur_big_endian16 (int16_t value) {
	return bswap_16 (value);
}
