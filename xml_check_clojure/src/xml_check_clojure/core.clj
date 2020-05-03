(ns xml-check-clojure.core
  (:gen-class))

(require '[clojure.xml :as xml])

;XML file to be parsed
(def xml_file "food.xml")
(def xml_file_parsed (xml/parse xml_file))

;return true if the XML file can be parsed by clojure.xml library
(defn well-formed?
  [filename]
  (try
    (xml/parse filename)
    true
    (catch Exception e false))
  )

;print a list in a readable way
(defn print_list [L]
  (if (empty? L)
    nil
    (do (print (first L)) (print "\n") (print "\n") (print_list (rest L))))
  )

;true if two lists have the same elements in the same position
(defn equal_list? [L1 L2]
  (if (empty? L1)
    true
    (and (= (first L1) (first L2)) (equal_list? (rest L1) (rest L2)))))

;return a list of tags given a parsed XML file
(defn get_tags [L]
  (map :tag L))

;compare all the tags in the inner level of the xml file
(defn compare_tags [L]
  (if (= (count L) 1)
    true
    (and (equal_list?
          (get_tags (:content (first L)))
          (get_tags (:content (second L))))
          (compare_tags (rest L))
         ))
  )

(defn -main []
  (println (well-formed? xml_file))
  (println (get_tags (:content (nth (:content xml_file_parsed) 4))))
  (println (equal_list? (get_tags (:content (first (:content xml_file_parsed)))) (get_tags (:content (second (:content xml_file_parsed))))))
  (println (compare_tags (:content xml_file_parsed)))
  
  )
