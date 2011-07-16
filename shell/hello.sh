#!/bin/bash

###===check md5 checksum===DON'T DELETE OR MODIFY THIS LINE====
if [ "$(sed '/^#md5sum:/d' $0|md5sum|awk '{print $1}')"  !=  "$(sed -n 's/^#md5sum://p' $0)" ];then 
    cat <<-EOF
	[31mERROR[0m:
    	this file was modified by someone
     	or error occured when transport through network
     	please use the [32mnon-modified[0m version!
	EOF
	exit 1
fi
###===checksum end====DON'T DELETE OR MODIFY THIS LINE====

echo "hello,world"



#md5sum:4370341a2e1e3783063d1bb9ebbb4635
