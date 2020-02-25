# to make heading
BEGIN {
    FS="[<>]" # field separator, it's an AWK's variable
    n = split(columns, tags, ",") # split parameters: a string, a destination array, a delimiter 
    for (i=1; i<=n; i++) {
        printf "%s", tags[i]
        if(i < n)
        	printf "%s", ";" # if it's not the last tag, it adds a ; as delimiter
        else
        	printf "%s", "\n" # if it's the last tag it makes a new line
    }
}

# when the number of field is 5
NF==5 {
    # $1 some spaces (???) 
    # $2 is the name of the tag <...>
    # $3 is the value between <> and </>
    # $4 is the name of the tag </...>
    # $5 some spaces (???)

	valueBtwTag[$2] = $3
}


#/<\/food>/ {
$0 ~ itemTag {
    for (i=1; i<=n; i++) {
        if(i < n)
            # tags[i] is the tag name, used to retrive the tag value
            printf "%s%s", valueBtwTag[tags[i]], ";" 
        else
            printf "%s%s", valueBtwTag[tags[i]], "\n"
    }
}