#include "Conversion.cpp"

int main()
{
	table<int> t0({{2, 5}, {3, 4}, {4, 1}}, {"B", "B1"});
	cout << t0 << endl;

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

	cout << "############## print using iterator #################" << endl;
	for(auto i = t.begin(); i != t.end(); i++)
		cout << *i << endl;

	for(auto i = t1.begin(); i != t1.end(); ++i)
		cout << *i << endl;

	cout << "############## print by rows #################" << endl;
	for(int i = 0; i != t.get_row_count(); ++i)
		cout << t.get_row(i) << endl;

	cout << endl;

	for(int i = 0; i != t1.get_row_count(); ++i)
		cout << t1.get_row(i) << endl;

	cout << "############## print by columns #################" << endl;
	for(int i = 0; i != t.get_column_count(); ++i)
		cout << t.get_column(i) << endl;

	cout << endl;

	for(int i = 0; i != t1.get_column_count(); ++i)
		cout << t1.get_column(i) << endl;

	cout << "############## print table using ostream<< #################" << endl;
	cout << t << endl;
	cout << t1 << endl;

	cout << "############## map function #################" << endl;
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

	cout << "############## reduce function #################" << endl;
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

	int r1 = 0;
	r1 = t.row_reduce(3, f4);
	cout << t.get_row(3) << " ---> " << r1 << endl;

	int r2 = t1.row_reduce(2, f5);
	cout << t1.get_row(2) << " ---> " << r2 << endl;

	int r3 = t.column_reduce(2, f4);
	cout << t.get_column(2) << " ---> " << r3 << endl;

	cout << "############## add/delete columns #################" << endl;
	t.add_column(2, {0, 0, 0, 0}, "N");
	cout << t << endl;

	t.delete_column(0);
	cout << t << endl;

	cout << "############## set rows/columns #################" << endl;
	vector<int> v8 = {1, 2, 3};
	t.set_row(v8, 2);

	t.set_column({7, 8, 9, 9}, 0, "H");

	cout << t << endl;

	cout << "############## edit elements ###################" << endl;	
	t.set_elem(7, 3, 1);
	cout << t << endl;

	cout << "############## copy constructor #################" << endl;
	table<string> t5(t4);
	cout << t5 << endl;

	cout << "############## conversion from CSV #################" << endl;	
	string csv = "conversion.csv";
    Conversion<string> conversion_string;
    table<string> t6 = conversion_string.createTable(csv);
    cout << t6 << endl;

	cout << "############## conversion to CSV #################" << endl;	
	//write table t1 to prova.csv
    conversion_string.writeCSV(t1, "string.csv");
	Conversion<int> conversion_int;
	conversion_int.writeCSV(t, "int.csv"); 
	cout << "done... look for csv files" << endl;

	cout << "############## table of string to other type #################" << endl;	
	table<string> t7 = conversion_string.createTable("int.csv");

    function<int(string)> to_int =
		[](string s) -> int {
			int i = 0;
			try {
				i = stoi(s);
			}
			catch(exception e) {
				cout << "the string " << s << " must represent an integer number to be converted, putting 0 instead" << endl;
				i = 0;
			}
			return i;
		};

	table<int> t8 = t6.table_map(to_int);
	table<int> t9 = t7.table_map(to_int);

	cout << t7 << endl;
	cout << t8 << endl;
	cout << t9 << endl;

	cout << "##################################### EXAMPLE OF USAGE ####################################" << endl;
	string path = "int.csv";
    Conversion<int> c_int;
    table<string> table_string = c_int.createTable(path);
	table<int>  table_int = table_string.table_map(to_int);
	cout << table_int << endl;

	function<int(int, int)> product =
	[](int total, int v) -> int
		{
			if(total == 0)
				return v;
			return v * total;
		};

	int column_product = table_int.column_reduce(0, product);
	cout << "column 1 product: " << column_product << endl << endl;
	table_int.delete_row(2);
	c_int.writeCSV(table_int, "int_new.csv");
	cout << table_int << endl;
}