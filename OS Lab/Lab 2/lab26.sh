file_ext=$1
dest_dir=$2

for file in *."$file_ext"; do
  cp -- "$file" "$dest_dir/"
done


echo "Files with extension .$file_ext copied to \"$dest_dir\""
