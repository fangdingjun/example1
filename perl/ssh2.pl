#!/usr/bin/perl
#
#
use strict;
use warnings;
use Net::SSH2;

my $ssh2=Net::SSH2->new();
#$ssh2->debug(1);
my $host="localhost";
my $user="zhuzhu";
my $pw="112233";
$ssh2->connect($host) or die "$!";
if ($ssh2->auth_password($user,$pw)){
    print "login success\n";
} else { die "login failed";}
my $chan=$ssh2->channel();
$chan->shell();
my @cmds=("pwd","uptime","date","cd /","pwd","last|head");
foreach(@cmds){
    print $chan $_,"\n";
    #sleep 1;
    while(<$chan>){
        print $_ ;
    }
}
print "end\n";
$chan->close;
$ssh2->disconnect;
