#include "Table.cpp"


int main() {

	Table<int> t(3, 3);

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int> v2;
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	vector<int> v3;
	v3.push_back(7);
	v3.push_back(8);
	v3.push_back(9);


	t.add_row(v); 
	t.add_row(v2);
	t.add_row(v3);

	Table<int>::iterator i(t.get_row_count(), t.get_column_count());

	cout << "############## stampa per elementi #################" << endl;
	for(t.begin(i); t.end(i); i.next_elem())
		cout << t.get_elem(i) << " ";
	cout << endl;

	cout << "############## stampa per righe #################" << endl;
	for(t.begin(i); t.end(i); i.next_row())
		cout << t.get_row(i) << endl;

	cout << "############## stampa per colonne #################" << endl;
    for(t.begin(i); t.end(i); i.next_column())
    	cout << t.get_column(i) << endl;

	cout << "############## stampa per tabella #################" << endl;
    cout << t <<endl;
}