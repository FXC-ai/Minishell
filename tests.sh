echo
echo "-------test 0 : /bin/ls---------"
/bin/ls

echo
echo "-------test 1 : /bin/ls -la---------"
/bin/ls -la

echo
echo "-------test 2 : [echo -n] [echo] [echo poire poire poire poire]---------"
echo -n
echo
echo poire poire poire poire
echo

echo "-------test 3 : /bin/ls '-la' && echo \$?---------"
/bin/ls '-la'
echo $?


echo
echo "-------test 4 : ps \"aux\" && echo \$---------"
ps
echo $?

echo
echo "-------test 5 : which ls && echo \$---------"
which ls
echo $?

echo
echo "-------test 6 : /bin/fichiernul & echo \$?---------"
/bin/fichiernul
echo $?

echo
echo "-------test 7 : \$? + \$?---------"
$? + $?
echo $?

echo
echo "-------test 8 : echo \"000000 ; 111111111 , 2222222\"---------"
echo "000000 ; 111111111 , 2222222"

echo
echo "-------test 9 : echo '\"' \"''\" poire pomme'cerise'---------"
echo '"' "''" poire pomme'cerise'

echo
echo "-------test 10 echo \"cat lol.c | cat > lol.c\"---------"
echo "cat lol.c | cat > lol.c"

echo
echo "-------test 11 : echo 'bonjour' '\"ceci\"' '\"cela'---------"
echo 'bonjour' '"ceci"' '"cela'

echo
echo "-------test 12 : which 'ps'---------"
which 'ps'

echo "-------test 13 : echo \"\$USER\" '\$USER' $USER---------"
echo "$USER" '$USER' $USER


echo "-------test 14 : env ---------"
env

echo "-------test 15 : env poi poi poi & echo \$?---------"
env poi poi poi
echo $?

echo
echo "-------test 16 : export TEST=42 & env---------"
export TEST=42
env

echo
echo "-------test 17 : export TEST=41 & env---------"
export TEST=41
env

echo
echo "-------test 18 : export TEST2=42 TEST3=43 TEST4=44 ---------"
export TEST2=42 TEST3=43 TEST4=44
env

echo
echo "-------test 20 : unset TEST---------"
unset TEST
env


echo
echo "-------test 21 : unset TEST2 TEST3---------"
unset TEST2 TEST3

echo
echo "-------test 22 : cd .. & cd .. & cd Desktop/minishell & check des venv---------"
cd ..
env | grep PWD
cd ..
env | grep PWD
cd Desktop/minishell
env | grep PWD

echo
echo "-------test 23 : pwd---------"
pwd

echo
echo "-------test 24 : pwd 42---------"
pwd 42

echo
echo "-------test 25 : cd .. & pwd---------"
cd ..
pwd

echo
echo "-------test 26 : cd .. & pwd---------"
cd ..
pwd

echo
echo "-------test 27 : cd ../.. & cd bin/ & pwd---------"
cd ../..
cd bin/
pwd

echo
echo "-------test 28 : ls & date---------"
ls
date


echo
echo "-------test 29 : cd ../Users & ../bin/ls---------"
cd ../Users

echo -n 'Nous sommes dans le dossier et nous executons ../bin/ls : '
pwd
../bin/ls



echo
echo "-------test 30 : cd fcoindre/Desktop/minishell---------"
cd fcoindre/Desktop/minishell
pwd


echo
echo "-------test 31 : echo something > file_test0 & cat file_test0---------"
echo something > file_test0
cat file_test0

echo
echo "-------test 32 : echo something again >> file_test0 & cat file_test0---------"
echo something again bla>> file_test0
cat -e file_test0

echo
echo "-------test 33 : <file_test0 wc---------"
<file_test0 wc

echo
echo "-------test 33 : <file_test0 wc -l > file_test1 & cat -e file_test1---------"
<file_test0 wc -l > file_test1
cat -e file_test1

echo
echo "-------test 34 : ls > file_test0 > file_test0 & cat file_test0---------"
ls > file_test0 > file_test0
cat file_test0

echo
echo "-------test 35 : echo bla bla bla > file_test0 & cat file_test0 | grep bla---------"
echo "bla bla bla" > file_test0
cat file_test0 | grep bla

echo
echo "-------test 36 : ps aux | grep root | grep "42" | grep 'usr' | cat -e ---------"
ps aux | grep root | grep "42" | grep 'usr' | cat -e



echo
echo "-------test 37 : ls fichiernul | grep bla---------"
ls fichiernul | grep bla

echo
echo "-------test 38 : ps aux | grep root | grep 42 | grep usr | wc -l > file_test0 ---------"
ps aux | grep root | grep 42 | grep usr | wc -l > file_test0
echo "cat file_test0 :"
cat file_test0 

echo
echo "-------test 39 : echo \$USER \"$HOME\" '\$SHELL' \"'\$PWD'\" \$existepas---------"
echo $USER "$HOME" '$SHELL' "'$PWD'" $existepas




echo
echo "-------test 40 : unset PATH---------"
unset PATH

echo
echo "-------test 41 : export PATH=/usr/bin:/bin---------"
ls
PATH=/usr/bin:/bin
ls

echo
echo "-------test 42 : exit oi oi---------"
exit oi oi