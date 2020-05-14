#include <vector>
#include <fstream>
#include <iostream>
#include "Table.cpp"
#include <sstream>
using namespace std;

template <typename T>
class Conversion{
    public:
    static table<T> createTable(string fileName){
        ifstream input(fileName);
        vector<vector<T>> rows;
        
        vector<T> tempV;
        //create a vector of rows
        for(string line; getline( input, line ); ){
            stringstream ss(line);
            string item;
            T elem;
            char delim = ';';
            while(getline(ss, item, delim)){
                tempV.push_back(item);

            }
            rows.push_back(tempV);
            tempV.clear();            
        }
        input.close();
        //erase the first row that's the heading
        vector<string> heading = rows.at(0);
        rows.erase(rows.begin());
        table<T> t(rows, heading);
        return t;

    }

    static void writeCSV(table<T>& t, string fileName){
        ofstream writefile;
        writefile.open(fileName);
        vector<T> heading = t.get_heading();
        int size = heading.size();
        for (typename vector<T>::const_iterator i = heading.begin(); i != heading.end(); ++i){
            writefile << *i;
            size --;
            if(size != 0){
                writefile << ";";
            }

        }
        writefile << "\n";

        vector< vector<int> >::iterator row;
        vector<int>::iterator col;
        vector<vector<T>> elements = t.get_table_vector();
        for (typename vector<vector<T>>::const_iterator i = elements.begin(); i != elements.end(); ++i){
            size = heading.size();
            for (typename vector<T>::const_iterator i2 = (*i).begin(); i2 != (*i).end(); ++i2){        
                writefile << *i2;
                size --;
                if(size != 0){
                    writefile << ";";
                }
            }
            writefile << "\n";

        }
    }

    

};