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
			row = 0;
			column = 0;
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
			column = 0;
		}

		void next_column()
		{
			column++;
			row = 0;
		}
	};

	void begin(iterator& i) {
		i.row = 0;
		i.column = 0;
	}

	bool end(iterator& i) {
		return i.row < row_count && i.column < column_count;
	}

	//ritorna l'elemento puntato dall'iteratore
	//scorre la tabella riga per riga
	T get_elem(iterator& i) {
		return table_vector[i.row][i.column];
	}

	//ritorna l'intera riga puntata dall'iteratore
	vector<T> get_row(iterator &i) {
		return table_vector[i.row];
	}

	//ritorna l'intera colonna puntata dall'iteratore
	vector<T> get_column(iterator &i) {
		vector<T> c;
		for(int k = 0; k < i.row_count; k++)
		{
			c.push_back(table_vector[k][i.column]);
		}
		return c;
	}
};


template <class T>
ostream &operator<<(ostream &os, Table<T>& t)
{
	typename Table<T>::iterator i(t.get_row_count(), t.get_column_count());
    for(t.begin(i); t.end(i); i.next_row())
    	cout << t.get_row(i) << endl;

    return os;
}

template<class T>
ostream& operator<<(ostream& stream, const std::vector<T>& values)
{
    stream << "[ ";
    copy( begin(values), end(values), ostream_iterator<T>(stream, " ") );
    stream << ']';
    return stream;
}

