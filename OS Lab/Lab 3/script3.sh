echo enter values for a b c 
read a
read b
read c

d=$((b * b - 4 * a * c))
case $d in
[0]) echo equal real roots
;;
-*) echo imaginary roots
;;
*) echo real roots
esac
