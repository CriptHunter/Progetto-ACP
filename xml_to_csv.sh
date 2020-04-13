read -p "Enter the filename: " file  # read filename
fileArray=(`echo $file | tr '.' ' '`); # split it into an array of two elements
fileNoExt=${fileArray[0]} # filename without extension

read -p "Enter the number of columns : " n_col

# read columns names
for (i = 1; i <= n_col; i++); do
	read -p "Enter column ${i}: " input
	if (( $i == 1 ));
	then
		columns="${input}"
	else 
		columns="${columns},${input}"
	fi
done

#read the tag that divides elements in the xml file
read -p "Enter the item divider's name : " input
itemTag="</${input}>" 

#call awk script and writes his output to a csv file
awk -v columns=$columns -v itemTag=$itemTag -f xml_to_csv.awk $file > "${fileNoExt}.csv"
