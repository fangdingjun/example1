#!perl
#
#
use strict;
use warnings;
my $filename="d:/e.csv";
my $fh;
open $fh,">",$filename or die("open failed:$!\n");
print $fh "日期,部门,上班时间,加班时间,时间1,时间2,时间3,时间4,时间5,时间6\n";
for (1..20){
	for my $s (1..20){
		my $dept=$s;
		for (1..5){
			my $t1=int(rand(10))+50;
			my $t2;
			my $t4;
			if ($dept == 2){
				sprintf($t2,"11:%d",int(rand(5))+20);
				sprintf($t4,"17:%d",int(rand(5))+30);
			}elsif ($dept == 4){
				sprintf($t2,"11:%d",int(rand(5))+30);
				sprintf($t4,"17:%d",int(rand(5))+20);
			}else{
			sprintf($t2,"11:%d",int(rand(10))+30);
			sprintf($t4,"17:%d",int(rand(10))+20);
		}
		my $t3=int(rand(10))+50;
		my $t5=int(rand(10))+20;
		my $t6=int(rand(10));
		print $fh "2009-12-27,$dept,8:00,02:30,7:$t1,11:$t2,12:$t3,17:$t4,18:$t5,21:$t6\n";
	}
}
}
close $fh;
