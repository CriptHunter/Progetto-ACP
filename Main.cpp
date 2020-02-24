#include "Table.cpp"

int main()
{
	table<int> t(3, {"X", "Y", "Z"});
	table<int> t0(1, {"a"});
	t0.add_row({1});
	t0.add_row({2});

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
	for(auto i = t.begin(); i != t.end(); i++)
		cout << *i << endl;

	cout << endl;

	for(auto i = t1.begin(); i != t1.end(); ++i)
		cout << *i << endl;

	cout << "############## stampa per righe #################" << endl;
	for(int i = 0; i != t.get_row_count(); ++i)
		cout << t.get_row(i) << endl;

	cout << endl;

	for(int i = 0; i != t1.get_row_count(); ++i)
		cout << t1.get_row(i) << endl;

	cout << "############## stampa per colonne #################" << endl;
	for(int i = 0; i != t.get_column_count(); ++i)
		cout << t.get_column(i) << endl;

	cout << endl;

	for(int i = 0; i != t1.get_column_count(); ++i)
		cout << t1.get_column(i) << endl;

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

	function<int(string)> f6 =
		[](string v) -> int
		{
			return v.length();
		};

	table<bool> t2 = t.table_map(f1);
	cout << t2 << endl;

	table<int> t3 = t.table_map(f2);
	cout << t3 << endl;

	table<string> t4 = t1.table_map(f3);
	cout << t4 << endl;

	auto ve1 = t1.row_map(1, f3);
	cout << "map di una riga: " <<  ve1 << endl;

	vector<int> ve2 = t1.column_map(2, f6);
	cout << "map di una colonna: " << ve2 << endl;

	cout << "############## funzione reduce #################" << endl;
	function<int(int, int)> f4 =
		[](int total, int v) -> int
		{
			if(total == 0)
				return v;
			
			return v * total;
		};

	function<int(int, string)> f5 =
		[](int total_length, string s) -> int
		{
			return total_length + s.length();
		};

	int r1 = t.vector_reduce(v1, f4);
	cout << v1 << " ---> " << r1 << endl;

	int r2 = t1.vector_reduce(v5, f5);
	cout << v5 << " ---> " << r2 << endl;


	cout << "############## aggiunta/eliminazione colonne #################" << endl;
	t.add_column(2, {0, 0, 0, 0}, "N");
	cout << t << endl;

	t.delete_column(0);
	cout << t << endl;

	cout << "############## copy constructor #################" << endl;
	table<string> t5(t4);
	cout << t5 << endl;

}