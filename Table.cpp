#include <iostream> 
#include <vector> 
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>

class Table 
{
private:
	vector <vector<T>> table_vector;
	vector<string> heading;
	int row_count;
	int column_count;

public:
	//costruttore con tabella vuota senza heading
	Table(int _column_count = 0): row_count(0), column_count(_column_count) { }

	//costruttore con tabella vuota e heading
	Table(int _column_count, vector<string> heading): row_count(0), column_count(_column_count)
	{
		set_heading(heading);
	}

	//copy constructor
	Table(const Table &other)
	{
  		row_count = other.get_row_count();
  		column_count = other.get_column_count();
  		set_heading(other.get_heading());
  		table_vector = other.get_table_vector();
    }

    //ritorna il vettore della tabella per copia
    vector<vector<T>> get_table_vector() const
    {
    	return table_vector;
    }

	int get_row_count() const
	{
		return row_count;
	}

	int get_column_count() const
	{
		return column_count;
	}

	void add_row(vector<T> row)
	{
		if(row.size() == column_count)
		{
			table_vector.push_back(row);
			++row_count;
		}
		else
			cout << "ADD_ROW: required vector of size " << column_count << ", got vector of size " << row.size() << endl;
	}

	void delete_row(int pos)
	{
		if(pos < row_count && pos >= 0)
		{
			table_vector.erase (table_vector.begin() + pos);
			--row_count;
		}
		else
			cout << "DELETE_ROW: row index out of bound" << endl;
	}

	void set_heading(vector<string> _heading)
	{
		if(_heading.size() == column_count)
			heading = _heading;
		else
			cout << "SET_HEADING: required vector of size " << column_count << ", got vector of size " << _heading.size() << endl;
	}

	vector<string> get_heading() const
	{
		return heading;
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

	void begin(iterator& i) 
	{
		i.row = 0;
		i.column = 0;
	}

	bool end(iterator& i) 
	{
		return i.row < row_count && i.column < column_count;
	}

	//ritorna l'elemento puntato dall'iteratore
	//scorre la tabella riga per riga
	T get_elem(iterator& i) 
	{
		return table_vector[i.row][i.column];
	}

	//ritorna l'intera riga puntata dall'iteratore
	vector<T> get_row(iterator &i) 
	{
		return table_vector[i.row];
	}

	//ritorna l'intera colonna puntata dall'iteratore
	vector<T> get_column(iterator &i) 
	{
		vector<T> c;
		for(int k = 0; k < i.row_count; k++)
			c.push_back(table_vector[k][i.column]);
		return c;
	}

	//applica una funzione a tutti gli elementi della tabella, restituisce una nuova tabella
	template <typename X, typename Y>
	Table<T> map(function<X(Y)> function)
	{
		Table<T> t2(get_column_count(), get_heading());
		typename Table<T>::iterator i(get_row_count(), get_column_count());
		for(begin(i); end(i); i.next_row())
		{
			vector<T> v = get_row(i);
			transform(v.begin(), v.end(), v.begin(), function);
			t2.add_row(v);
		}
		return t2;
	}
};


template <class T>
ostream &operator<<(ostream &os, Table<T>& t)
{
	cout << t.get_heading() << endl;
	typename Table<T>::iterator i(t.get_row_count(), t.get_column_count());
    for(t.begin(i); t.end(i); i.next_row())
    	cout << t.get_row(i) << endl;

    return os;
}

template<class T>
ostream& operator<<(ostream& stream, const std::vector<T>& values)
{
    stream << "[ ";
    copy(begin(values), end(values), ostream_iterator<T>(stream, " "));
    stream << ']';
    return stream;
}




