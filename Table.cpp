#include <iostream> 
#include <vector> 
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>

class table 
{
private:
	vector <vector<T>> table_vector;
	vector<string> heading;
	int row_count;
	int column_count;

public:
	//costruttore con tabella vuota senza heading
	table(int _column_count = 0): row_count(0), column_count(_column_count) { }

	//costruttore con tabella vuota e heading
	table(int _column_count, vector<string> heading): row_count(0), column_count(_column_count)
	{
		set_heading(heading);
	}

	//copy constructor
	table(const table &other)
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

	class table_iterator
    {
    public:
        table_iterator(vector<vector<T>>& _table_vector, int _row_count, int _column_count, int _row = 0, int _column = 0)
        {
        	table_vector = _table_vector;
        	row = _row;
        	column = _column;
        	row_count = _row_count;
        	column_count = _column_count;
        }

        table_iterator operator++()
        { 
        	table_iterator i = *this; 
        	if(column < column_count - 1)
        		column++;
        	else
        	{
        		row++;
        		column = 0;
        	}

        	return i; 
        }

        T get() 
        { 
        	return table_vector[row][column];
        }

        bool operator!=(const table_iterator& other) 
        { 
        	return !(row == other.row && column == other.column);
        }

        int row;
        int column;

    private:
        vector<vector<T>> table_vector;
        int row_count;
        int column_count;
    };

    class row_iterator
    {
    public:
        row_iterator(vector<vector<T>>& _table_vector, int _row_count, int _row = 0)
        {
        	table_vector = _table_vector;
        	row = _row;
        	row_count = _row_count;
        }

        row_iterator operator++()
        { 
        	row_iterator i = *this; 
        	row++;
        	return i; 
        }

        vector<T> get() 
        { 
        	return table_vector[row];
        }

        bool operator!=(const row_iterator& other) 
        { 
        	return row != other.row + 1;
        }

        int row;

    private:
        vector<vector<T>> table_vector;
        int row_count;
    };

    class column_iterator
    {
    public:
        column_iterator(vector<vector<T>>& _table_vector, int _row_count, int _column_count, int _column = 0)
        {
        	table_vector = _table_vector;
        	row_count = _row_count;
        	column = _column;
        	column_count = _column_count;
        }

        column_iterator operator++()
        { 
        	column_iterator i = *this; 
        	column++;
        	return i; 
        }

        vector<T> get() 
        { 
        	vector<T> temp;
        	for(int i = 0; i < row_count; i++)
        		temp.push_back(table_vector[i][column]);
        	return temp;
        }

        bool operator!=(const column_iterator& other) 
        { 
        	return column != other.column + 1;
        }

        int column;

    private:
        vector<vector<T>> table_vector;
        int row_count;
        int column_count;
    };

    table_iterator begin_ti()
    {
    	return table_iterator(table_vector, row_count, column_count);
    }

    table_iterator end_ti()
    {
    	return table_iterator(table_vector, row_count, column_count, row_count - 1, column_count - 1);
    }

    row_iterator begin_ri()
    {
    	return row_iterator(table_vector, row_count);
    }

    row_iterator end_ri()
    {
    	return row_iterator(table_vector, row_count, row_count - 1);
    }

    column_iterator begin_ci()
    {
    	return column_iterator(table_vector, row_count, column_count);
    }

    column_iterator end_ci()
    {
    	return column_iterator(table_vector, row_count, column_count, column_count - 1);
    }

	//applica una funzione a tutti gli elementi della tabella, restituisce una nuova tabella
	/*template <typename X, typename Y>
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
	}*/
};

template<class T>
ostream& operator<<(ostream& stream, const std::vector<T>& values)
{
    stream << "[ ";
    copy(begin(values), end(values), ostream_iterator<T>(stream, " "));
    stream << ']';
    return stream;
}


template <class T>
ostream &operator<<(ostream &os, table<T>& t)
{
	cout << t.get_heading() << endl;
	for(typename table<T>::row_iterator i = t.begin_ri(); i != t.end_ri(); ++i)
    	cout << i.get() << endl;
    return os;
}





