echo enter a number
read num
a=1

while [ $num -gt 0 ]
do
	a=$(( $a * $num ))
	num=$(($num - 1))
done
echo $a

	
