#!/usr/bin/perl 
#===============================================================================
#
#         FILE:  regexp_c.pl
#
#        USAGE:  ./regexp_c.pl  
#
#  DESCRIPTION: this is a test for module Regexp::Common 
#
#      OPTIONS:  ---
# REQUIREMENTS:  ---
#         BUGS:  ---
#        NOTES:  ---
#       AUTHOR:  fangdingjun (), fangdingjun@gmail.com
#      COMPANY:  
#      VERSION:  1.0
#      CREATED:  2010-01-03 12时24分38秒
#     REVISION:  ---
#===============================================================================

use strict;
use warnings;

use Regexp::Common 'RE_ALL';
while (<DATA>){
    chomp;
    #/$RE{num}{real}/ and print qq{$_ a number\n};
    #/$RE{quoted}/ and print qq{$_ a quoted string\n};
    #m#$RE{deliited}{-delim=>'/'}# and print q{a /../ sequence};
    #/$RE{balanced}{-parens=>'()'}/ and print qq{$_ balaned parentheses\n};
    #/$RE{profanity}/ and print qq{$_ a #*-ing word\n};
    $_ =~ RE_num_real() and print qq{$_ a number\n};
    $_ =~ RE_quoted() and print qq{$_ a quoted string\n};
    $_ =~ RE_delimited(-delim=>'/') and print qq{$_ a /../ sequence};
    $_ =~ RE_balanced(-parens=>'()') and print qq{$_ balaned parentheses\n};
}

__END__
888
asdfas
10.40
"werwer"
#!@!
'asdfa'
asdfa(asf)
asdfa/adfa/
