clear
clear
clear
echo "*****-----Begin Compilation-----*****"
cc gen_c.c -std=c11 -Wall -o gen_c_lxe
if [[ $? -eq 0 ]]
then
  echo "*****-----Compilation Successful.....Opening Program-----*****"
  echo "--"
  ./gen_c_lxe
  echo "--"
  echo "*****-----Done Executing the Program-----*****"
else
  echo "*****-----Compilation Failed-----*****"
fi