#include <iostream> 
#include <vector> 
#include <iterator>

using namespace std;

template <typename T>

class Table {
private:
	vector <vector<T>> table_vector;
	int row_count;
	int column_count;

public:
	Table(int _row_count, int _column_count)
	{
		row_count = _row_count;
		column_count = _column_count;
	}

	int get_row_count()
	{
		return row_count;
	}

	int get_column_count()
	{
		return column_count;
	}

	void add_row(vector<T> &row)
	{
		if(row.size() == column_count)
			table_vector.push_back(row);
		else
			cout << "ADD_ROW: required vector of size " << column_count << ", got vector of size " << row.size() << endl;
	}

	class iterator
	{
	public:
		int row;
		int column;
		int row_count;
		int column_count;

		iterator(int _row_count, int _column_count)
		{
			row_count = _row_count;
			column_count = _column_count;
		}

		void next_elem() 
		{
			if(column < column_count - 1)
				column++;
			else
			{
				column = 0;
				row++;
			}
		}

		void next_row()
		{
			row++;
		}
	};

	void begin(iterator& i) {
		i.row = 0;
		i.column = 0;
	}

	bool end(iterator& i) {
		return i.row < row_count;
	}

	T get_elem(iterator& i) {
		return table_vector[i.row][i.column];
	}

	vector<T> get_row(iterator &i) {
		return table_vector[i.row];
	}
};


/*template <typename T>
ostream &operator<<(ostream &os, Table<T> t)
{
	typename Table<T>::Table_iterator it;

	for(it.set_begin(); it.check_end(); it.next())
	{
		cout << "ciao" << endl;
	}

	return os;
}*/