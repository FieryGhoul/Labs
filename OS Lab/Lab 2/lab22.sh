
directory=$1
pattern=$2
find  "$directory" | grep -E "$pattern"
