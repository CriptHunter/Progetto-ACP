#include <iostream> 
#include <vector> 
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>

class table {
private:
	vector<vector<T>> table_vector; // values of the table
	vector<string> heading; //columns names
	int row_count;
	int column_count;

public:
	// constructor for an empty table without heading
	// column count is fixed
	table(int _column_count = 0): row_count(0), column_count(_column_count) { }

	// constructor for an empty table with heading
	table(int _column_count, vector<string> heading): row_count(0), column_count(_column_count)
	{
		set_heading(heading);
	}

	// constructor for a table made by vector<vector>, with heading
	table(vector<vector<T>> _table_vector, vector<string> _heading)
	{
		try 
		{
			int n_col = _table_vector[0].size();
			for(const auto& row : _table_vector)
				if(row.size() != n_col)
					throw "CONSTRUCTOR: Trying to add rows with different columns number";

			if(_heading.size() != n_col)
				throw "CONSTRUCTOR: Trying to add heading with wrong columns number";		

			table_vector = _table_vector;
			heading = _heading;
			row_count = table_vector.size();
			column_count = n_col;
		}

		catch(const char* msg)
		{
			cerr << msg << endl;
		}
	}

	// copy constructor
	table(const table &other)
	{
  		row_count = other.get_row_count();
  		column_count = other.get_column_count();
  		set_heading(other.get_heading());
  		table_vector = other.get_table_vector();
    }

    // return the table vector by copy
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

	// add a row in position pos
	// it does not overwrite existing row
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

	// add a row at the end of the table
	void add_row(vector<T> row)
	{
		add_row(row_count, row);
	}

	// delete a row in position pos
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

	// add a column in position pos, add to the heading the column name
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

	// add a column at the end of the table
	void add_column(vector<T> column, string _heading)
	{
		add_column(column_count, column, _heading);
	}

	// delete a column in position pos
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

	vector<T> get_row(int pos) const 
	{
		if(pos < 0 || pos >= row_count)
		{
			cout << "GET_ROW: row index out of bound";
			return {};
		}
		else
			return table_vector[pos];
	}

	vector<T> get_column(int pos) const
	{
		if(pos < 0 || pos >= row_count)
		{
			cout << "GET_COLUMN: column index out of bound";
			return {};
		}
		else
		{
			vector<T> column;
    		for(int i = 0; i < row_count; i++)
    			column.push_back(table_vector[i][pos]);
    		return column;
		}
	}

	// table iterator pointing to a single cell in position row | column
	class iterator
    {
    public:
    	// constructor
        iterator(vector<vector<T>>& _table_vector, int _row = 0, int _column = 0)
        {
        	table_vector = &_table_vector;
        	row = _row;
        	column = _column;
        	row_count = (*table_vector).size();
        	column_count = (*table_vector)[0].size();
        }

        // prefix operator++
        iterator operator++()
        { 
        	iterator i = *this; 
        	if(column < column_count - 1)
        		column++;
        	else
        	{
        		row++;
        		column = 0;
        	}
        	return i; 
        }

        // postfix operator ++
        iterator operator++(int) 
        { 
        	if(column < column_count - 1)
        		column++;
        	else
        	{
        		row++;
        		column = 0;
        	}
        	return *this; 
        }

        // return by reference the value of the cell pointed by the iterator
        T& operator*() const
		{
			return (*table_vector)[row][column];
		}

		// checks if two iterator are equals
        bool operator==(const iterator& other) const 
        {
        	return table_vector == other.table_vector && row == other.row && column == other.column;
        }

        // checks if two iterator are not equals
        bool operator!=(const iterator& other) const
        { 
        	return !(*this == other);
        }

    private:
        vector<vector<T>> *table_vector = nullptr;
        int row_count;
        int column_count;       
        int row;
        int column;
    };

    
    // return an iterator pointing at the first cell of the table
    iterator begin()
    {
    	return iterator(table_vector);
    }

    // return an iterator pointing at the last cell of the table
    iterator end()
    {
    	return iterator(table_vector,row_count - 1, column_count - 1);
    }

    // apply the function f to every element of vector v
    // the function f takes a value of type T and return a value of type X
    // the returned vector return_v contains element of type X, as the function f
    template <typename X>
    vector<X> vector_map(vector<T> v, function<X(T)> f) const
    {
    	vector<X> return_v;
    	for(const auto& elem : v)
    		return_v.push_back(f(elem));
    	return return_v;
    }

    // apply the map function to a row in position pos
    template <typename X>
    vector<X> row_map(int pos, function<X(T)> f) const
    {
    	return vector_map(get_row(pos), f);
    }

    // apply the map function to a column in position pos
    template <typename X>
    vector<X> column_map(int pos, function<X(T)> f) const
    {
    	return vector_map(get_column(pos), f);
    }

    // apply map to all the element of the table
    template <typename X>
    table<X> table_map(function<X(T)> f) const
    {
    	table<X> t2(get_column_count(), get_heading());
    	for(auto i = table_vector.begin(); i != table_vector.end(); i++)
    	{
    		vector<X> v = vector_map(*i, f);
    		t2.add_row(v);
    	}
    	return t2;
    }

    // reduce a vector to  value using the function f
    // the function takes two arguments of type X T, and return a value of type X
    // the first argument is the accumulator, the second is an element of the vector
	template <typename X>
    X vector_reduce(vector<T> v, function<X(X, T)> f) const
    {
    	X reduced_v {};
    	for(auto i = v.begin(); i != v.end(); i++)
    		reduced_v = f(reduced_v, *i);
    	return reduced_v; 
    }
};

// override of the ostream operator << for a vector
// it prints the vector between []
template<class T>
ostream& operator<<(ostream& stream, const std::vector<T>& values)
{
    stream << "[ ";
    copy(begin(values), end(values), ostream_iterator<T>(stream, " "));
    stream << ']';
    return stream;
}

// override of the ostream operator << for a table
// it prints the heading, and the table row by row between []
template <class T>
ostream &operator<<(ostream &os, table<T>& t)
{
	auto vv = t.get_table_vector();
	cout << t.get_heading() << endl;
	for(auto i = vv.begin(); i != vv.end(); i++)
    	cout << *i << endl;
    return os;
}