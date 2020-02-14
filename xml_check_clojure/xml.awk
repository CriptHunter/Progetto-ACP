BEGIN {
    FS="[<>]" #variabile awk usata come field separator
    n = split("name price description calories",tags,/ /)
    for (i=1; i<=n; i++) {
        printf "%s", tags[i]
        if(i < n)
        	printf "%s", ";" # se non è l'ultimo tag mette un ; come delimitatore
        else
        	printf "%s", "\n" # se è l'ultimo tag va a capo
    }
}

NF==5 { 
	tag2val[$2] = $3 
}

/<\/food>/ {
    for (i=1; i<=n; i++) {
        printf "%s%s", tag2val[tags[i]], (i<n ? ";":"\n")
    }
}

/<\/breakfast_menu>/ { delete tag2val }