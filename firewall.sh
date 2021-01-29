#!/bin/bash

output=""

packets=$(cat)


while read rule
do
	
		# remove spaces, empety lines, and remove comments 
		rule=`echo "$rule" | sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
		if [[ "$rule" == "" ]]; then
			continue
		fi
		#split by ','
		mapfile -d , -t filters <<< "$rule"

	    #check if packets passed all parts of sub_rules

		pakets_temp=`echo "$packets" | ./firewall.exe "${filters[0]}"`
		pakets_temp=`echo "$pakets_temp" | ./firewall.exe "${filters[1]}"`
		pakets_temp=`echo "$pakets_temp" | ./firewall.exe "${filters[2]}"`
		pakets_temp=`echo "$pakets_temp" | ./firewall.exe "${filters[3]}"`
		
		#creat output
		if [[ "$pakets_temp" == "" ]]; then
			continue
		fi
		output+=`echo -e "${pakets_temp}"`
		output+="\n"
		
done < "$1"  

echo -e "${output}" | sort -u |sed 's/ //g' | sed '/^$/d' 



