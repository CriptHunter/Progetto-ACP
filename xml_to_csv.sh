awk -v columns="name,price,description,calories" -v itemTag="</food>" -f xml_to_csv.awk food.xml
