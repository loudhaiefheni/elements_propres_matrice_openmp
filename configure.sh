res1=$(find /usr/ -name "gsl")
echo $res1
# pour les .h (dans le makefile sur la ligne "include=-I(+Resultat de la requète sans gsl)")
res2=$(find /usr -name "libgsl.a")
echo $res2
# la librairie pour linker les fichiers compiler (dans le makefile sur la ligne "libs=-L(+Resultat de la requète sans libgsl.a)")