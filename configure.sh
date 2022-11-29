find /usr/ -name "gsl"
# pour les .h (dans le makefile sur la ligne "include=-I(+Resultat de la requète sans gsl)")
find /usr -name "libgsl.a"
# la librairie pour linker les fichiers compiler (dans le makefile sur la ligne "libs=-L(+Resultat de la requète sans libgsl.a)")