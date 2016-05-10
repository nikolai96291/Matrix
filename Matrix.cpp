#include<iostream>
using namespace std;


class matrix 
{
	int n;
	int m;
	float* data;
public:
	matrix()
	{
		n = 0;
		m = 0;
		data = NULL;
	}
	matrix(int n, int m)
	{
		this->n = n;
		this->m = m;
		data = new float[n*m];
	}
	matrix(const matrix& c)
	{
		float tmp;
		n = c.n;
		m = c.m;
		data = new float[n*m];
		for (int j = 0; j < m; j++)
		{
			for (int i = 0; i < n; i++)
			{
				tmp = c.data[j*n + i];
				set(i, j, tmp);
			}
		}
	}
	virtual matrix& operator = (matrix& a)
		{
			float tmp;
			n = a.n;
			m = a.m;
			data = new float[n*m];
			for (int j = 0; j < m; j++)
			{
				for (int i = 0; i < n; i++)
				{
					tmp = a.data[j*n + i];
					set(i, j, tmp);
				}
			}
			return (*this);
		}
	virtual matrix operator + (matrix& a)
	{
		if (n == a.getN() && m == a.getM())
		{
			matrix c(n,m);
			float tmp;
			for (int j = 0; j < m; j++)
			{
				for (int i = 0; i < n; i++)
				{
					tmp = get(i, j) + a.get(i, j);
					c.set(i, j, tmp);
				}
			}
			return c;
		}
		else
		{
			matrix c;
			return c;
		}
	}
	virtual matrix operator - (matrix& a)
	{
		if (n == a.getN() && m == a.getM())
		{
			matrix c(n, m);
			float tmp;
			for (int j = 0; j < m; j++)
			{
				for (int i = 0; i < n; i++)
				{
					tmp = get(i, j) - a.get(i, j);
					c.set(i, j, tmp);
				}
			}
			return c;
		}
		else
		{
			matrix c;
			return c;
		}
	}
	virtual matrix operator * (matrix& a)
	{
		
		if (n == a.getM())
		{
			matrix c(m,a.getN());
			float k = 0;
			for (int j = 0; j < m; j++)
			{
				for (int i = 0; i < n; i++)
				{
					for (int p = 0; p < n; p++)
						k = k + get(p, j)*a.get(i, p);
					c.set(i, j, k);
					k = 0;
				}
			}
			return c;
		}
		else
		{
			matrix c;
			return c;
		}
	
	}
	virtual matrix transpose()
	{
		if (failed())
		{
			matrix c;
			return c;
		}
		matrix c(m, n);
		for (int j = 0; j < m; j++)
			for (int i = 0; i < n; i++)
				c.set(j, i, get(i, j));
		return c;
	}
	virtual ostream& print(ostream& o)
	{
		for (int j = 0; j < m; j++)
		{
			for (int i = 0; i < n; i++)
			{
				o << get(i, j) << ' ';
			}
			o << endl;
		}
		return(o);
	}
	virtual istream& read(istream& o)
	{
		o >> n;
		o >> m;
		data = new float[n*m];
		float tmp;
		for (int j = 0; j < m; j++)
		{
			for (int i = 0; i < n; i++)
			{
				o >> tmp;
				set(i, j, tmp);
			}
		}
		return(o);
	}
	virtual void set(int i, int j, float data)
	{
		this->data[j*this->n + i] = data;
	}
	virtual float get(int i, int j)
	{
		return(data[j*this->n + i]);
	}
	virtual int getN()
	{
		return n;
	}
	virtual int getM()
	{
		return m;
	}
	virtual bool failed()
	{
		if ((n == 0 && m == 0) || data == NULL)
			return true;
		else
			return false;
	}
};
