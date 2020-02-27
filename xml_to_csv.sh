columns=""
echo "Enter the number of columns : "
read n_col


for ((i = 1; i <= n_col; i++)); do
	read -p "Enter column : " input
	if (( $i == 1 ));
	then
		columns="${input}"
	else 
		columns="${columns},${input}"
	fi
done

read -p "Enter the item divider's name : " input
itemTag="</${input}>"

#columns="name,price,description,calories"
#itemTag="</food>"

awk -v columns=$columns -v itemTag=$itemTag -f xml_to_csv.awk food.xml
