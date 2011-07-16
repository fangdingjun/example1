#!/usr/bin/perl
#
use strict;
while (<>)
{
	my @a=split /\s+/;
	($a[4])=($a[4]=~/.*?(.{1,4})$/);
	print join "\t",@a;
	print "\n";
}
