@echo off
echo user fangdj fangdj > a.txt
echo bin >> a.txt
echo ls >> a.txt
echo bye >> a.txt
ftp -in -s:a.txt localhost
pause
