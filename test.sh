#!/bin/sh

i=0
for FILE in TESTS/Fichiers_elf/*.o 
do
touch TESTS/Resultats/resultat$i.txt
./test_affichage $FILE < TESTS/entrees > TESTS/Resultats/resultat$i.txt
i=`expr $i + 1`
done
