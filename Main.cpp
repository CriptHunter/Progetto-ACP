#include "Table.cpp"

int main()
{
	Table<int> t(3, {"X", "Y", "Z"});

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2;
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	vector<int> v3;
	v3.push_back(7);
	v3.push_back(8);
	v3.push_back(9);

	vector<int> v4;
	v4.push_back(10);
	v4.push_back(11);
	v4.push_back(12);

	t.add_row(v1); 
	t.add_row(v2);
	t.add_row(v3);
	t.add_row(v4);
	t.delete_row(3);

	Table<string> t1(3, {"AAAA", "BBBB", "CCCC"});

	vector<string> v5;
	v5.push_back("aaaa");
	v5.push_back("bbbb");
	v5.push_back("cccc");

	vector<string> v6;
	v6.push_back("dddd");
	v6.push_back("eeee");
	v6.push_back("ffff");

	vector<string> v7;
	v7.push_back("gggg");
	v7.push_back("hhhh");
	v7.push_back("iiii");

	t1.add_row(v5);
	t1.add_row(v6);
	t1.add_row(v7);

	/*Table<int>::iterator i(t.get_row_count(), t.get_column_count());
	Table<string>::iterator i1(t1.get_row_count(), t1.get_column_count());

	cout << "############## stampa per elementi #################" << endl;
	for(t.begin(i); t.end(i); i.next_elem())
		cout << t.get_elem(i) << " ";
	cout << endl;

	for(t1.begin(i1); t1.end(i1); i1.next_elem())
		cout << t1.get_elem(i1) << " ";
	cout << endl;

	cout << "############## stampa per righe #################" << endl;
	for(t.begin(i); t.end(i); i.next_row())
		cout << t.get_row(i) << endl;

	cout << endl;

	for(t1.begin(i1); t1.end(i1); i1.next_row())
		cout << t1.get_row(i1) << endl;

	cout << "############## stampa per colonne #################" << endl;
    for(t.begin(i); t.end(i); i.next_column())
    	cout << t.get_column(i) << endl;

	cout << "############## stampa per tabella #################" << endl;
    cout << t;

	cout << "############## funzione map #################" << endl;
    function<bool(int)> f1 =
		[](int v) -> bool
		{
			if(v % 2 == 0)
				return true;
			else
				return false;
		};

    function<int(int)> f2 =
		[](int v) -> int
		{
			return v * 10;
		};

	function<string(string)> f3 =
		[](string v) -> string
		{
			return "#" + v + "#";
		};

    Table<int> t3 = t.map(f1);
    Table<int> t4 = t.map(f2);
    Table<string> t5 = t1.map(f3);

    cout << t3 << endl;
    cout << t4 << endl;
    cout << t5 << endl;*/

    
}