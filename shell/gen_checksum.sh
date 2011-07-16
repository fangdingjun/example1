#!/bin/bash
# add check code and md5sum into shell script file
#    add check code in second line,add md5sum in last line
# # 
# usage:
#      gen_checksum.sh file1 file2 file3 ... fileN
#      only run with shell script
#
# author: fangdingjun
# license:GPL
# date:2010-5-21
# bug report to:fangdingjun@gmail.com

###===VALIDATE MD5 CHECKSUM,DON'T DELETE OR MODIFY THIS LINE===
if [ "$(sed '/^#md5sum:/d' $0|md5sum|awk '{print $1}')"  !=  "$(sed -n 's/^#md5sum://p' $0)" ];then 
    cat <<-EOF
	[31mERROR[0m:
    	this file was modified by someone
     	or error occured when transport through network
     	please use the [32mnon-modified[0m version!
	EOF
	exit 1
fi
###===CHECKSUM END,DON'T DELETE OR MODIFY THIS LINE===

if [ $# -lt 1 ];then
    echo -e "[32mUSAGE:[0m \n\t./`basename $0` file1 file2 ...fileN"
	exit 1
fi

gen_sum()
{
	if [ $# -ne 1 ];then
		echo "usage: gen_sum file"
		return 1
	fi
    checkcode=$(sed -n '/^###===/,/^###===/p' $0)
    c=$(sed -n '/^###===/,/^###===/p' $1)
    hascheckcode=1
    if [ -z "$c" ];then
        hascheckcode=0
    fi
	perl -x $0 $1 "$checkcode" $hascheckcode
	echo -n "#md5sum:" >> $1
	sed  '/^#md5sum:/d' $1 |md5sum | awk '{print $1}' >> $1
	return 0
}

while [ $# -gt 0 ]
do
	gen_sum $1
	shift
done
exit 0

#!/usr/bin/perl
use strict;
use warnings;
my $checkcode=$ARGV[1];
my $has=$ARGV[2];
@ARGV=($ARGV[0]);
$^I="_bak";
while(<>){
    if ($. == 2){
        print $checkcode,"\n" if ($has == 0);
    }
    next if ($_ =~ /^#md5sum:/);
    print;
}
__END__

#md5sum:7daf081c3c41c1021d48bfdaca63f1f6
