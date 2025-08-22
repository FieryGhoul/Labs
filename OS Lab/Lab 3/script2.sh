echo "Enter N"
read n
echo "printing first $n odd numbers"
count=0
num=1
while [ $count -lt $n ]
do 
echo $num
num=$((num+2))
count=$((count+1))
done
	

