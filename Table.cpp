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

	//aggiunge una riga nella posizione specificata
	void add_row(int pos, vector<T> row)
	{
		if(row.size() == column_count)
		{
			if(pos >= 0 && pos <= row_count)
			{
				table_vector.insert(table_vector.begin() + pos, row);
				++row_count;
			}
			else
				cout << pos << " is an invalid position" << endl;
		}
		else
			cout << "ADD_ROW: required vector of size " << column_count << ", got vector of size " << row.size() << endl;
	}

	//aggiunge una riga alla fine della tabella
	void add_row(vector<T> row)
	{
		add_row(row_count, row);
	}

	//cancella una riga in posizione pos
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

	//aggiunge una colonna in posizione pos, aggiunge l'header corrispondente alla colonna
	void add_column(int pos, vector<T> column, string _heading)
	{
		if(column.size() != row_count)
		{
			cout << "ADD_COLUMN: required vector of size " << row_count << ", got vector of size " << column.size() << endl;
			return;
		}

		if(pos < 0 || pos > column_count)
			cout << "ADD_COLUMN: row index out of bound" << endl;

		heading.insert(heading.begin() + pos, _heading);
		column_count++;

		for(int k = 0; k < row_count; ++k)
		{
			vector<T> v = table_vector[k];
			v.insert(v.begin() + pos, column[k]);
			table_vector[k] = v;
		}
	}

	void delete_column(int pos)
	{
		if(pos < 0 || pos > column_count)
		{
			cout << "ADD_COLUMN: row index out of bound" << endl;
			return;
		}

		column_count--;
		heading.erase(heading.begin() + pos);

		for(int k = 0; k < row_count; ++k)
		{
			vector<T> v = table_vector[k];
			v.erase(v.begin() + pos);
			table_vector[k] = v;
		}
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

    private:
        vector<vector<T>> table_vector;
        int row_count;
        int column_count;       
        int row;
        int column;
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

    private:
        vector<vector<T>> table_vector;
        int row_count;
        int row;
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

    private:
        vector<vector<T>> table_vector;
        int row_count;
        int column_count;
        int column;
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

    //applica la funzione f a tutti gli elementi del vettore v
    //il vettore return_v contiene elementi dello stesso tipo di quelli ritornati dalla funzione f
    template <typename X, typename Y>
    vector<X> vector_map(vector<T> v, function<X(Y)> f)
    {
    	vector<X> return_v;
    	for(const auto& elem : v)
    		return_v.push_back(f(elem));
    	return return_v;
    }

    template <typename X, typename Y>
    table<X> table_map(function<X(Y)> f)
    {
    	table<X> t2(get_column_count(), get_heading());
    	for(typename table<T>::row_iterator i = begin_ri(); i != end_ri(); ++i)
    	{
    		vector<X> v = vector_map(i.get(), f);
    		t2.add_row(v);
    	}
    	return t2;
    }
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





