(ns xml-check-clojure.core
  (:gen-class))

(require '[clojure.xml :as xml])

;XML file to be parsed
(def xml_file "food.xml")
;parsed XML file
(def xml_file_parsed (xml/parse xml_file))

;return true if the XML file can be parsed by clojure.xml library
(defn well-formed? [filename]
  (try
    (xml/parse filename)
    true
    (catch Exception e false))
  )

;print list elements on separate lines with spacing
(defn print_list [L]
  (if (empty? L)
    nil
    (do (print (first L)) 
        (print "\n") 
        (print "\n") 
        (print_list (rest L))))
  )

;true if two lists have the same elements in the same position
(defn equal_list? [L1 L2]
  (if (not= (count L1) (count L2))
    false
    
    (if (empty? L1)
      true
      (and (= (first L1) (first L2))
           (equal_list? (rest L1) (rest L2)))))
  )

;return a list of tags given a :content in a XML file
(defn get_tags [L]
  (map :tag L))


;compare all the tags on the same level of a XML file
(defn compare_tags [L]
  (if (and (<= (count L) 1))
    true
    (and (equal_list?
          (get_tags (:content (first L)))
          (get_tags (:content (second L))))
         (= (:tag (first L)) (:tag (second L)))
         (compare_tags (rest L))
         ))
  )

;get depth of XML file to avoid nested tag
(defn get_depth [L]
  true
  )

(defn -main []
  (print "well formed? ")
  (println (well-formed? xml_file))
  (print "same tags? ")
  (println (compare_tags (:content xml_file_parsed)))
  )

