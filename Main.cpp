#include "Table.cpp"


int main() {

	Table<int> t(2, 3);
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(30);

	t.add_row(v); 
	t.add_row(v2);

	Table<int>::iterator i(t.get_row_count(), t.get_column_count());

	for(t.begin(i); t.end(i); i.next_elem())
    {
        cout << t.get_elem(i) << endl;
    }

    for(t.begin(i); t.end(i); i.next_row())
    {
    	vector<int> v = t.get_row(i);
        for(int i = 0; i < v.size(); i++)
        	cout << v[i] << " ";
        cout << endl;
    }
}