#include<iostream>
#include<math.h>
using namespace std;


class Matrix
{
	int n;
	int m;
	float* data;
public:
	Matrix()
	{
		n = 0;
		m = 0;
		data = NULL;
	}
	Matrix(int n, int m)
	{
		this->n = n;
		this->m = m;
		data = new float[n*m];
	}
	Matrix(const Matrix& c)
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
	virtual Matrix& operator = (const Matrix& a)
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
	virtual Matrix operator + (Matrix& a)
	{
		if (n == a.getN() && m == a.getM())
		{
			Matrix c(n, m);
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
			Matrix c;
			return c;
		}
	}
	virtual Matrix operator - (Matrix& a)
	{
		if (n == a.getN() && m == a.getM())
		{
			Matrix c(n, m);
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
			Matrix c;
			return c;
		}
	}
	virtual Matrix operator* (float c)
	{
		if (failed() == 1)
		{
			return *this;
		}
		Matrix res;
		res.n = this->n;
		res.m = this->m;
		res.data = new float[res.n*res.m];
		for (int i(0); i < res.n*res.m; i++)
		{
			res.data[i] = this->data[i] * c;
		}
		return Matrix(res);
	}
	virtual Matrix operator * (Matrix& a)
	{

		if (n == a.getM())
		{
			Matrix c(m, a.getN());
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
			Matrix c;
			return c;
		}

	}
	virtual Matrix transpose()
	{
		if (failed())
		{
			Matrix c;
			return c;
		}
		Matrix c(m, n);
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
	virtual Matrix GetMinor(int _i, int _j)
	{
		if (n != m)
		{
			return *(this);
		}
		Matrix temp(n - 1, m - 1);
		int k = 0;
		int p = 0;
		for (int i(0); i < n; i++)
		{
			if (i == _i)
				continue;
			p = 0;
			for (int j(0); j < m; j++)
			{
				if (j == _j)
					continue;
				temp.set(k, p, get(i, j));
				p++;
			}
			k++;
		}
		return Matrix(temp);
	}
	virtual double determinant()
	{
		if (n != m || failed() == 1)
			return 0;
		if (n == 1)
			return data[0];
		double det = 0;
		for (int i(0); i < n; i++)
			det = det + powf(-1, i)*data[i] * GetMinor(0, i).determinant();
		return det;
	}
	virtual Matrix reverse()
	{
		if (failed() == 1)
			return *this;
		double det = determinant();
		if (det == 0)
			return *this;
		Matrix _inverse(n, m);
		for (int i(0); i < n; i++)
			for (int j(0); j < m; j++)
			{
			_inverse.set(i, j, powf(-1, i + j) * GetMinor(j, i).determinant());
			}

		_inverse = _inverse*pow(det, -1);
		return Matrix(_inverse);
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
		return (n <= 0 || m <= 0 || n != m || data == NULL);
	}
virtual Matrix* get_init(int n, int m)
	{
		Matrix* N = new Matrix(n, m);
		return N;
	}
};
