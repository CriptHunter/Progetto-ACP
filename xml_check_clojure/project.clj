(defproject com.clojure.xml "clojure_xml_check_library"
  :description "xml checker"
  :url "https://github.com/lucafumagalli/ACPproject"
  :license {:name "EPL-2.0 OR GPL-2.0-or-later WITH Classpath-exception-2.0"
            :url "https://www.eclipse.org/legal/epl-2.0/"}
  :dependencies [[org.clojure/clojure "1.10.0"]]
  :repl-options {:init-ns xml-check-clojure.core}
  :main xml-check-clojure.core
  :aot :all)
