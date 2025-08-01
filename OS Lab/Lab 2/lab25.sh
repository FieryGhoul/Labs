file1=$1
file2=$2
output=$3
cat "$file1" "$file2" | sort -n | uniq > "$output"
echo "Merged and sorted file created at $output"
