a_file="file_list"

a_fileIndex=`stat -c '%i' "$a_file"`;

echo "$a_fileIndex";
