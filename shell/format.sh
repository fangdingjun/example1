perl -ane '($F[8])=($F[8]=~/.*?(.{1,5})$/);print join "\t",@F,"\n";' a.txt
#md5sum:beb0c33c354b561f22a32aa650aa0d9c
