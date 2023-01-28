#!/bin/sh
l=$(find /usr/ -name "gsl")
# pour les .h (dans le makefile sur la ligne "include=-I(+Resultat de la requète sans gsl)")
export gsl_include='-I'${l%/*}'/'
echo "showing variables (source this file with . ./configure)"
echo "gsl_include "$gsl_include
l=$(find /usr -name "libgsl.a") 
export gsl_lib='-L'${l%/*}'/'
echo "gsl_lib "$gsl_lib
# la librairie pour linker les fichiers compiler (dans le makefile sur la ligne "libs=-L(+Resultat de la requète sans libgsl.a)")
unset l
