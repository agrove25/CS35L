#!/bin/sh

# to run this program, feed a stdinput of a directory. ex: echo ~/testFolder

read directory
cd "$directory"

# lists and sorts the directory and only accepts regular files, having hidden files go first
file_list=`find . -maxdepth 1 -type f | sed "s/.\///" | grep ^'\.' | sort`
file_list2=`find . -maxdepth 1 -type f | sed "s/.\///" | grep -v ^[\.] | sort`
file_list="$file_list""\n""$file_list2""\n"

fullCount=0
# loops through file_list and assigns each line to var a_file
# printf "$file_list" | while read -r a_file
printf "$file_list" | while read -r a_file
do
    fullCount=$((fullCount+1));
    currentCount=0;

    # loops through file_list and assigns each line to var b_file
    # printf "$file_list" | while read -r b_file
    printf "$file_list" | while read -r b_file
    do
	currentCount=$((currentCount+1));

	# makes sure that each checked combination is unique (haven't been done before)
	if `test $currentCount -gt $fullCount`
	then
	    # checks if a_file and b_file are the same
	    if `cmp -s -- "$a_file" "$b_file"` && test -r "$a_file" 
	    then
	        a_fileIndex=`stat -c '%i' -- "$a_file"`;
		b_fileIndex=`stat -c '%i' -- "$b_file"`

		# checks if a_file and b_file share the same inode. If not then continue...
		if [ $a_fileIndex -ne $b_fileIndex ]
		then

		    # all the program actually does. removes the file that is lower ranked (in the above sort) and adds a link to the higher ranked one
		    rm -- "$b_file"
		    ln "$a_file" -- "$b_file"
		    
		fi
	    fi
	fi
    done
done

