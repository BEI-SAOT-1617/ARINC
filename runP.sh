>listpid
xterm -e ./loop.sh  &
xterm -e ./Sserver  &
xterm -e ./Sclient  vivaldi-wifi.laas.fr &
echo '***** WAITING FOR INSTALL TO COMPLETE  *****'
for i in `seq 20`
do
 sleep 1
 echo -n '*-'
done
echo   
echo "Liste des pid"
ps | grep -e xterm | grep -v grep | awk '{ print $1 }' > listpid
echo '***** LIST OF PROCESSES *****'
cat listpid
