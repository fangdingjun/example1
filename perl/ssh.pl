#!/usr/bin/perl 
#===============================================================================
#
#         FILE:  ssh.pl
#
#        USAGE:  ./ssh.pl  
#
#  DESCRIPTION:  this is ssh test
#
#      OPTIONS:  ---
# REQUIREMENTS:  ---
#         BUGS:  ---
#        NOTES:  ---
#       AUTHOR:  fangdingjun (), fangdingjun@gmail.com
#      COMPANY:  
#      VERSION:  1.0
#      CREATED:  2010-02-23 18时48分23秒
#     REVISION:  ---
#===============================================================================

use strict;
use warnings;
use Net::SSH::Perl;
my $user="zhuzhu";
my $pass="112233";
my $host="localhost";
my %param=(
	protocol=>2,
	debug=>1
);
my $ssh=Net::SSH::Perl->new($host,%param);
$ssh->login($user,$pass);
=head
my @cmd=("ls","pwd","ls /tmp","uptime","date");
foreach (@cmd){
    my ($stdout,$stderr,$exit)=$ssh->cmd($_);
    print $stdout if $stdout;
    print $stderr if $stderr;
}
=cut
my ($o,$e,$s)=$ssh->cmd("uptime");
print $o;
undef $ssh;
