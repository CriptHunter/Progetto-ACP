#include "Table.cpp"

int main()
{
	table<int> t(3, {"X", "Y", "Z"});

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

	table<string> t1(3, {"QQQQ", "WWWW", "EEEE"});

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

	cout << "############## stampa per elementi #################" << endl;
	for(table<int>::table_iterator i = t.begin_ti(); i != t.end_ti(); ++i)
		cout << i.get() << endl;

	cout << endl;

	for(table<string>::table_iterator i = t1.begin_ti(); i != t1.end_ti(); ++i)
		cout << i.get() << endl;

	cout << "############## stampa per righe #################" << endl;
	for(table<int>::row_iterator i = t.begin_ri(); i != t.end_ri(); ++i)
		cout << i.get() << endl;

	cout << endl;

	for(table<string>::row_iterator i = t1.begin_ri(); i != t1.end_ri(); ++i)
		cout << i.get() << endl;

	cout << "############## stampa per colonne #################" << endl;
	for(table<int>::column_iterator i = t.begin_ci(); i != t.end_ci(); ++i)
		cout << i.get() << endl;

	cout << endl;

	for(table<string>::column_iterator i = t1.begin_ci(); i != t1.end_ci(); ++i)
		cout << i.get() << endl;

	cout << "############## stampa tabella #################" << endl;
	cout << t << endl;
	cout << t1 << endl;

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

	table<bool> t2 = t.table_map(f1);
	cout << t2 << endl;

	table<int> t3 = t.table_map(f2);
	cout << t3 << endl;

	table<string> t4 = t1.table_map(f3);
	cout << t4 << endl;

	cout << "############## aggiunta/eliminazione colonne #################" << endl;
	t.add_column(2, {0, 0, 0, 0}, "N");
	cout << t << endl;

	t.delete_column(0);
	cout << t << endl;
}