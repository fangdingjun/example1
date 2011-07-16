#!/usr/bin/perl
use strict;
use DBI;
my $dbname="xe";
my $username="system";
my $passwd="FGFDfgfd";
my $host="localhost";
my $sid="xe";
my $dbh="";
$\="\n";
$dbh=DBI->connect("dbi:Oracle:host=$host;sid=$sid",$username,$passwd) or die "can't connect to database ".DBI->errstr;
my $sqlfile=$ARGV[0];
#my $fh;
#open $fh,$sqlfile or die "$!";
while (my $sql=<>)
{
	chomp($sql);
	my $sth=$dbh->prepare("$sql");
	$sth->execute or die DBI->errstr;
	if ($sql =~ /^select.*from/)
	{
		while( my @recs=$sth->fetchrow_array)
		{
			#print $recs[0].":".$recs[1].":".$recs[2]."\n";
			print join "\t",@recs;
		}
	}
}
#close $fh;
$dbh->disconnect;
