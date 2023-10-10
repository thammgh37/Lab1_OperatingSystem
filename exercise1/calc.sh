#! /usr/bin/bash

if [ -s "myvar.txt" ]; then
	ANS=$(<myvar.txt)
else
	ANS=0
fi
exp=""

displayHist() {
	cat history.txt
}

Calculate() {
	#replace string ANS with saved value in file
	#exp=${exp//ANS/$ANS}
	
	#split operators and operand
	read operand1 operator operand2 <<< $exp

	#check valid operand
	if [[ ! "$operand1" =~ ^[+-]?[0-9]+\.?[0-9]*$|^ANS$ ]] || [[ ! "$operand2" =~ ^[+-]?[0-9]+\.?[0-9]*$|^ANS$ ]]; then
		echo "SYNTAX ERROR"
		return 1
	fi 
	
	if [[ "$operand1" = "ANS" ]]; then
		operand1=$ANS
	fi
	if [[ "$operand2" = "ANS" ]]; then
		operand2=$ANS
	fi
	
	#calculate
	case $operator in
		"+")
		result=`echo $operand1 + $operand2 | bc `
		;;
		"-")
		result=`echo $operand1 - $operand2 | bc`
		;;
		"*")
		result=`echo $operand1 \* $operand2 | bc`
		;;
		"/")
		if [ $operand2 -eq 0 ]; then
			echo "MATH ERROR"
			return 1
		fi
		result=`echo "scale=2; $operand1 / $operand2" | bc`
		;;
		"%")
  		if [ $operand2 -eq 0 ]; then
			echo "MATH ERROR"
			return 1
		fi
		result=`echo $(($operand1 / $operand2))`
		;;
		*)
		echo "SYNTAX ERROR"
		return 1
		;;
	esac

	#print result and update variable ANS
	echo "$result"
	ANS=$result

	#Write new value of ANS to file
	nloFile=$(wc -l < history.txt)
	if [ $nloFile -eq 5 ]; then
		sed -i '5d' history.txt
	fi
	if [ $nloFile -eq 0 ]; then
		echo "$tmp = $ANS" > history.txt
	else 
		sed -i "1i $tmp = $ANS" history.txt
	fi
	echo "$ANS" > myvar.txt
}
while true; do

	read -p ">> " exp
	tmp=$exp
	if [ "$exp" = "EXIT" ]; then
		break
	elif [ "$exp" = "HIST" ]; then
		displayHist
		read -n 1 -s -r -p "Press any char"
		clear
	else 
		Calculate
		read -n 1 -s -r -p "Press any char"
		clear
	fi
done
