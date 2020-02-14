(ns xml-check-clojure.core
  (:gen-class
    :name com.clojure.xml
    :methods [#^{:static true} [binomial [int int] double]]))

(require '[clojure.xml :as xml])

;file xml da leggere
(def xml_file "food.xml")

(defn binomial
  "Calculate the binomial coefficient."
  [n k]
  (let [a (inc n)]
    (loop [b 1
           c 1]
      (if (> b k)
        c
        (recur (inc b) (* (/ (- a b) b) c))))))

(defn -binomial
  "A Java-callable wrapper around the 'binomial' function."
  [n k]
  (binomial n k))


;return true if the XML file can be parsed by clojure.xml library
(defn well-formed?
  [filename]
  (try
    (xml/parse filename)
    true
    (catch Exception e false))
  )

(defn print_list [L]
  (if (empty? L)
    nil
    (do (print (first L)) (print "\n") (print_list (rest L))))
    )



(defn get_tags [L]
  (list (map :tag (:content L)))
  )

(defn check_tags [L]
  (if (empty? L)
    true
    (and (=
           (get_tags (first L))
           (get_tags (second L)))
         (check_tags (rest L))
         ))
  )



(defn -main []
  (def xml_content (:content (xml/parse xml_file)))

  (print_list xml_content)
  )
