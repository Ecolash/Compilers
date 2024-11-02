//This file tests control flow from one function to another

int mod = 1000000000 + 7;
int mod2 = 998244353;

int binpow(int a, int b) {
	int ans = 1;
	while (b != 0) {
		if((b & 1) != 0) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b = b >> 1;
	}
	return ans;
}

int rec(int exp, int base)
{
	if (exp == 0) return 1;
	int t = rec(exp / 2, base);
	if (exp % 2 == 0) return (t * t) % mod2;
	return (base * t * t) % mod2;
}

int main() {
    int a = 9, b = 3;
    gcd(a, b);
    binpow(++a, b++);
	int c = rec(a--, --b);
	int arr[100][200];

	while(a--) 
	{
		if (a % 2) continue;
		else a = a / 2;
		c = rec(binpow(a,b), c);
		while (c-- > -5) b++;
		arr[a][b] = c;
	}
    return 0;
}