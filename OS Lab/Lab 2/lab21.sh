directory=$1
find "$directory"|grep -E .'\.[^.]{1}$'

