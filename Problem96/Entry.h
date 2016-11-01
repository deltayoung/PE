#pragma once
class Entry
{
private:
	int row;
	int col;
	int val;

public:
	Entry()
	{
		row = col = val = -1;	// unset, as 0 value actually refer to actual row/col # and unsolved entry
	}

	Entry(int r, int c, int v)
	{
		row = r;
		col = c;
		val = v;
	}

	~Entry() {}

	int getRow() { return row; }
	int getCol() { return col; }
	int getVal() { return val; }
	void setRow(const int r) { row = r; }
	void setCol(const int c) { col = c; }
	void setVal(const int v) { val = v; }

	Entry& operator=(const Entry &e)
	{
		if (&e != this)
		{
			row = e.row;
			col = e.col;
			val = e.val;
		}
		return *this;
	}

	bool operator==(const Entry &e)
	{
		return (row == e.row && col == e.col && val == e.val);
	}

	bool operator!=(const Entry &e)
	{
		return !(this == &e);
	}
};

