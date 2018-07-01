/*
template: Polynomial
by: AnzheWang
*/ 
#include <bits/stdc++.h>

using namespace std;
 
const int mod = 998244353, g = 3;

const int N = 1 << 19;

inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }

inline int fpow(int a, int x)
{
	int ret = 1;
	for (; x; x >>= 1)
	{
		if (x & 1) ret = 1LL * ret * a % mod;
		a = 1LL * a * a % mod;
	}
	return ret;
}

inline int legendre(int x) { return fpow(x, (mod - 1) >> 1); }

inline int fsqrt(int x)
{
	if (!x) return 0;
	if (mod == 2) return x & 1;
	if (legendre(x) == mod - 1) return -1;
	int b, w;
	do
	{
		b = rand() % mod;
		w = (1LL * b * b - x + mod) % mod;
	} while (legendre(w) != mod - 1);
	struct item
	{
		int a, b;
		item(int _a = 0, int _b = 0) : a(_a), b(_b) {  }
		item mul(item y, int w)
		{
			item x = *this, z;
			z.a = (1LL * x.a * y.a + 1LL * x.b * y.b % mod * w) % mod;
			z.b = (1LL * x.a * y.b + 1LL * x.b * y.a) % mod;
			return z;
		}
	};
	item res(1, 0), a(b, 1);
	int p = (mod + 1) / 2;
	for (; p; p >>= 1)
	{
		if (p & 1) res = res.mul(a, w);
		a = a.mul(a, w);
	}
	return min(res.a, dec(0, res.a)); 
	//两个根 
}

inline int inv(int x) { return fpow(x, mod - 2); }
//NTT
inline void dft(int *a, int n, int sig)
{
	for (int i = 0, j = 0; i < n; ++i)
	{
		if (i > j) swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	for (int i = 1; i < n; i <<= 1)
	{
		int m = i << 1;
		int w = fpow(g, (mod - 1) / m);
		if (sig == -1) w = inv(w);
		for (int j = 0; j < n; j += m)
			for (int k = 0, v = 1; k < i; ++k, v = 1LL * v * w % mod)
			{
				int x = a[j + k], y = 1LL * a[j + i + k] * v % mod;
				a[j + k] = inc(x, y), a[j + i + k] = dec(x, y);
			}
	}
	if (sig == -1)
	{
		int invn = inv(n);
		for (int i = 0; i < n; ++i)
			a[i] = 1LL * a[i] * invn % mod;
	}
}

inline void get_inv(int *a, int *r, int n)
{
	if (n == 1)
	{
		r[0] = inv(a[0]);
		if (!a[0]) throw "error!";
		return;
	}
	static int x[N], y[N], z[N];
	get_inv(a, x, (n + 1) >> 1);
	int m = 1;
	for (; m < (n << 1); m <<= 1);
	memset(y, 0, sizeof(int) * m);
	memset(z, 0, sizeof(int) * m);
	memcpy(y, x, sizeof(int) * ((n + 1) >> 1));
	memcpy(z, a, sizeof(int) * n);
	dft(y, m, 1); dft(z, m, 1);
	for (int i = 0; i < m; ++i)
		z[i] = (((y[i] << 1) - 1LL * y[i] * y[i] % mod * z[i]) % mod + mod) % mod;
	dft(z, m, -1);
	memcpy(r, z, sizeof(int) * n);
}

inline void get_sqrt(int *a, int *r, int n)
{
	if (n == 1)
	{
		r[0] = fsqrt(a[0]);
		if (r[0] == -1) throw "error!";
		return;
	}
	static int x[N], y[N], z[N], w[N];
	get_sqrt(a, x, (n + 1) >> 1);
	int m = 1;
	for (; m < (n << 1); m <<= 1);
	memset(y, 0, sizeof(int) * m);
	memset(z, 0, sizeof(int) * m);
	memset(w, 0, sizeof(int) * m);
	memcpy(y, x, sizeof(int) * ((n + 1) >> 1));
	get_inv(y, z, n);
	memcpy(w, z, sizeof(int) * n);
	memset(z, 0, sizeof(int) * m);
	memcpy(z, a, sizeof(int) * n);
	dft(z, m, 1), dft(w, m, 1);
	for (int i = 0; i < m; ++i)
		z[i] = 1LL * z[i] * w[i] % mod;
	dft(z, m, -1);
	for (int i = 0; i < n; ++i) {
		x[i] = inc(x[i], z[i]);
		if (x[i] & 1) x[i] += mod;
		x[i] >>= 1;
	}
	memcpy(r, x, sizeof(int) * n);
}

void get_division(int *A, int *B, int *D, int n, int m)
{
	if (n < m) return void(D[0] = 0);
	int t = n - m + 1, p = 1;
	for (; p < (t << 1); p <<= 1);
	static int x[N], y[N];
	fill(x, x + p, 0);
	reverse_copy(B, B + m, x);
	get_inv(x, y, t);
	fill(y + t, y + p, 0);
	dft(y, p, 1);
	reverse_copy(A, A + n, x);
	fill(x + t, x + p, 0);
	dft(x, p, 1);
	for (int i = 0; i < p; ++i) x[i] = 1LL * x[i] * y[i] % mod;
	dft(x, p, -1);
	reverse_copy(x, x + t, D);
}

struct poly
{
	
	vector< int > a;
	
	poly() { redeg(0); }
	
	poly(int n, ...)
	{
		va_list scan;
		va_start(scan, n);
		redeg(n);
		for (int i = n; ~i; --i) a[i] = va_arg(scan, int);
		va_end(scan);
	}
	
	inline int& operator[](const int &x) { return a[x]; }
	
	inline int deg() { return a.size() - 1; }
	
	inline void redeg(int n) { a.resize(n + 1); }
	
	inline void swap(poly &x) { a.swap(x.a); }
	
	inline void maintain()
	{
		int p = deg();
		while (p > 0 && !a[p]) --p;
		redeg(p);
	}
	
	inline void scan(int *x, int n)
	{
		redeg(n);
		for (int i = 0; i <= n; ++i) a[i] = x[i];
	}
	
	inline int print(int *x)
	{
		int n = deg();
		for (int i = 0; i <= n; ++i) x[i] = a[i];
		return n;
	}
	//翻转 
	inline poly reverse()
	{
		poly x = *this;
		std::reverse(x.a.begin(), x.a.end());
		return x;
	}
	//积分 
	inline poly integral()
	{
		poly x = *this;
		x.redeg(deg() + 1);
		static int Inv[N];
		static int init_n;
		if (!init_n)
			init_n = Inv[1] = 1;
		if (init_n < x.deg())
		{
			for (int i = init_n + 1, n = x.deg(); i <= n; ++i)
				Inv[i] = dec(mod, 1LL * Inv[mod % i] * (mod / i) % mod);
			init_n = x.deg();
		}
		for (int i = x.deg(); i; --i) x[i] = 1LL * x[i - 1] * Inv[i] % mod;
		x[0] = 0;
		return x;
	}
	//微分 
	inline poly diff()
	{
		poly x = *this;
		for (int i = 1; i <= x.deg(); ++i) x[i - 1] = 1LL * x[i] * i % mod;
		x[x.deg()] = 0;
		x.maintain();
		return x;
	}
	//加法 
	friend inline poly operator + (poly a, poly b)
	{
		if (a.deg() < b.deg()) a.swap(b);
		for (int i = 0; i <= b.deg(); ++i) a[i] = inc(a[i], b[i]);
		return a;
	}
	//减法 
	friend inline poly operator - (poly a, poly b)
	{
		if (a.deg() < b.deg()) a.redeg(b.deg());
		for (int i = 0; i <= b.deg(); ++i) a[i] = dec(a[i], b[i]);
		return a;
	}
	//乘法 
	friend inline poly operator * (poly a, int x)
	{
		for (int i = 0; i <= a.deg(); ++i)
			a[i] = 1LL * a[i] * x % mod;
		return a;
	}
	//乘法 
	friend inline poly operator * (poly a, poly b)
	{
		if (min(a.deg(), b.deg()) < 28)
		{
			poly c;
			c.redeg(a.deg() + b.deg());
			for (int i = 0; i <= a.deg(); ++i)
				if (a[i]) for (int j = 0; j <= b.deg(); ++j)
					if (b[j]) c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % mod;
			return c;
		}
		static int x[N], y[N];
		int n = 1; for (; n <= a.deg() + b.deg(); n <<= 1);
		memset(x, 0, sizeof(int) * n);
		memset(y, 0, sizeof(int) * n);
		a.print(x), b.print(y);
		dft(x, n, 1), dft(y, n, 1);
		for (int i = 0; i < n; ++i) x[i] = 1LL * x[i] * y[i] % mod;
		dft(x, n, -1);
		poly c;
		c.scan(x, a.deg() + b.deg());
		return c;
	}
	//除法 
	friend inline poly operator / (poly a, poly b)
	{
		a.maintain(), b.maintain();
		static int A[N], B[N], D[N];
		int n = a.print(A);
		int m = b.print(B);
		poly d;
		get_division(A, B, D, n + 1, m + 1);
		d.scan(D, max(n - m + 1, 0));
		d.maintain();
		return d;
	}
	//取模 
	friend inline poly operator % (poly a, poly b)
	{
		poly d = a / b;
		poly r = a - b * d;
		r.maintain();
		return r;
	}
	//乘方 
	friend inline poly operator ^ (poly a, int x) { return a.pow(x); }
	
	//求逆元 (满足：常数项可以求逆(不为0)) 
	inline poly inv();
	//求ln (满足：多项式可以求逆) 
	inline poly ln();
	//求exp (满足：多项式常数项为0)
	inline poly exp();
	//开根号 (满足：多项式常数项有二次剩余) 
	inline poly sqrt(); 
	//快速幂前n项 (满足：多项式常数项为1) 
	inline poly pow(int);
	//欧拉公式
	inline pair< poly, poly > euler();
	//求sin
	inline poly sin();
	//求cos
	inline poly cos();
	//求tan 
	inline poly tan();
};

inline poly get_exp(poly &x, int n)
{
	if (!n) 
	{
		if (x[0]) throw "error!";
		return poly(0, 1);
	} 
	poly F = get_exp(x, n >> 1);
	F.redeg(n);
	poly G = poly(0, 1) - F.ln();
	G.redeg(n);
	for (int i = 0; i <= n && i <= x.deg(); ++i)
		G[i] = inc(G[i], x.a[i]);
	F = G * F;
	F.redeg(n);
	F.maintain();
	return F;
}

inline poly poly::inv()
{
	int n = deg();
	static int a[N], r[N];
	poly c;
	memset(a, 0, sizeof(int) * (n + 1));
	memset(r, 0, sizeof(int) * (n + 1));
	print(a);
	get_inv(a, r, n + 1);
	c.scan(r, n);
	return c;
}

inline poly poly::ln()
{
	poly a = this -> diff();
	poly b = this -> inv();
	poly c = (a * b).integral();
	c.redeg(deg());
	c.maintain();
	return c;
}

inline poly poly::exp() { return get_exp(*this, deg()); }

inline poly poly::sqrt()
{
	int n = deg();
	static int a[N], r[N];
	poly c;
	memset(a, 0, sizeof(int) * (n + 1));
	memset(r, 0, sizeof(int) * (n + 1));
	print(a);
	get_sqrt(a, r, n + 1);
	c.scan(r, n);
	return c;
}

inline poly poly::pow(int x)
{
	if (a[0] != 1) throw "error!";
	int n = deg();
	poly c = this -> ln();
	c = c * x;
	c = c.exp();
	c.redeg(n);
	return c;
}

//三角函数操作 

namespace trigonometric_function
{
	
	struct complex
	{
		int a, b;
		complex(int _a = 0, int _b = 0) : a(_a), b(_b) {  }
		inline complex operator + (const complex &x) { return complex(inc(a, x.a), inc(b, x.b)); }
		inline complex operator - (const complex &x) { return complex(dec(a, x.a), dec(b, x.b)); }
		inline complex operator * (const complex &x) 
		{
			return complex(dec(1LL * a * x.a % mod, 1LL * b * x.b % mod), inc(1LL * a * x.b % mod, 1LL * b * x.a % mod));
		}
		inline complex operator * (const int &x) { return complex(1LL * a * x % mod, 1LL * b * x % mod); }
		inline complex inv()
		{
			int v = size();
			v = ::inv(v);
			return complex(a, dec(0, b)) * v;
		}
		inline int size()
		{
			return (1LL * a * a + 1LL * b * b) % mod;
		}
	};
	
	inline void dft(complex *a, int n, int sig)
	{
		for (int i = 0, j = 0; i < n; ++i)
		{
			if (i > j) swap(a[i], a[j]);
			for (int l = n >> 1; (j ^= l) < l; l >>= 1);
		}
		for (int i = 1; i < n; i <<= 1)
		{
			int m = i << 1;
			int w = fpow(g, (mod - 1) / m);
			if (sig == -1) w = inv(w);
			for (int j = 0; j < n; j += m)
				for (int k = 0, v = 1; k < i; ++k, v = 1LL * v * w % mod)
				{
					complex x = a[j + k], y = a[j + i + k] * v;
					a[j + k] = x + y, a[j + i + k] = x - y;
				}
		}
		if (sig == -1)
		{
			int invn = inv(n);
			for (int i = 0; i < n; ++i)
				a[i] = a[i] * invn;
		}
	}
	
	inline void get_inv(complex *a, complex *r, int n)
	{
		if (n == 1)
		{
			r[0] = a[0].inv();
			if (!a[0].size()) throw "error!";
			return;
		}
		static complex x[N], y[N], z[N];
		get_inv(a, x, (n + 1) >> 1);
		int m = 1;
		for (; m < (n << 1); m <<= 1);
		memset(y, 0, sizeof(complex) * m);
		memset(z, 0, sizeof(complex) * m);
		memcpy(y, x, sizeof(complex) * ((n + 1) >> 1));
		memcpy(z, a, sizeof(complex) * n);
		dft(y, m, 1); dft(z, m, 1);
		for (int i = 0; i < m; ++i)
			z[i] = y[i] * 2 - y[i] * y[i] * z[i];
		dft(z, m, -1);
		memcpy(r, z, sizeof(complex) * n);
	}
	
	inline void get_ln(complex *a, complex *r, int n)
	{
		static complex x[N], y[N];
		memcpy(x, a, sizeof(complex) * n);
		for (int i = 1; i < n; ++i) x[i - 1] = x[i] * i;
		x[n - 1] = complex();
		get_inv(a, y, n);
		int m = 1;
		for (; m < (n << 1); m <<= 1);
		static complex A[N], B[N];
		memset(A, 0, sizeof(complex) * m);
		memcpy(A, x, sizeof(complex) * n);
		memset(B, 0, sizeof(complex) * m);
		memcpy(B, y, sizeof(complex) * n);
		dft(A, m, 1), dft(B, m, 1);
		for (int i = 0; i < m; ++i) A[i] = A[i] * B[i];
		dft(A, m, -1);
		memcpy(r, A, sizeof(complex) * (n - 1));
		static int Inv[N];
		static int init_n;
		if (!init_n)
			init_n = Inv[1] = 1;
		if (init_n < n)
		{
			for (int i = init_n + 1; i <= n; ++i)
				Inv[i] = dec(mod, 1LL * Inv[mod % i] * (mod / i) % mod);
			init_n = n;
		}
		for (int i = n; i; --i) r[i] = r[i - 1] * Inv[i];
		r[0] = complex(0, 0);
	}
	
	inline void get_exp(complex *a, complex *r, int n)
	{
		if (!n)
		{
			if (a[0].a || a[0].b) throw "error!";
			r[0] = complex(1);
			return;
		}
		static complex x[N];
		get_exp(a, x, n >> 1);
		static complex y[N];
		memset(y, 0, sizeof(complex) * (n + 1));
		memcpy(y, x, sizeof(complex) * ((n >> 1) + 1));
		static complex z[N];
		get_ln(y, z, n + 1);
		static complex w[N];
		memset(w, 0, sizeof(complex) * (n + 1));
		memcpy(w, z, sizeof(complex) * (n + 1));
		w[0] = complex(1) - w[0];
		for (int i = 1; i <= n; ++i)
			w[i] = complex(0) - w[i];
		for (int i = 0; i <= n; ++i)
			w[i] = w[i] + a[i];
		int m = 1;
		for (; m < (n << 1); m <<= 1);
		static complex t[N], s[N];
		memset(s, 0, sizeof(complex) * m);
		memcpy(s, x, sizeof(complex) * ((n >> 1) + 1));
		memset(t, 0, sizeof(complex) * m);
		memcpy(t, w, sizeof(complex) * (n + 1));
		dft(s, m, 1), dft(t, m, 1);
		for (int i = 0; i < m; ++i) s[i] = s[i] * t[i];
		dft(s, m, -1);
		memcpy(r, s, sizeof(complex) * (n + 1));
	}
	
}

inline pair< poly, poly > poly::euler()
{
	static trigonometric_function::complex x[N], y[N];
	int n = deg();
	for (int i = 0; i <= n; ++i) x[i] = trigonometric_function::complex(0, a[i]);
	poly a, b;
	trigonometric_function::get_exp(x, y, n);
	static int A[N], B[N];
	for (int i = 0; i <= n; ++i) A[i] = y[i].a, B[i] = y[i].b;
	a.scan(A, n);
	b.scan(B, n);
	return make_pair(a, b);
}

inline poly poly::sin() { return euler().second; }

inline poly poly::cos() { return euler().first; }

inline poly poly::tan()
{
	pair< poly, poly > res = euler();
	res.first = res.first.inv();
	return res.first * res.second; 
}

int main()
{
	
}