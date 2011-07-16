#!/bin/bash
###===check md5 checksum===DON'T DELETE OR THIS LINE===
if [ "$(sed '/^#md5sum:/d' $0|md5sum|awk '{print $1}')"  !=  "$(sed -n 's/^#md5sum://p' $0)" ];then 
    cat <<-EOF
	[31mERROR[0m:
    	this file was modified by someone
     	or error occured when transport through network
     	please use the [32mnon-modified[0m version!
	EOF
	exit 1
fi
###===checksum end===DON'T DELETE OR MODIFY THIS LINE===
username="fangdj"
passwd="fangdj"
cmd="ls"
ip="localhost"
{
    sleep 1
    echo user $username $passwd
    sleep 1
    echo $cmd
    sleep 1
    echo bye
} | ftp -in $ip
#md5sum:7b3ad8c5dfa67e625ecf815914a28f0b
