int main()
{
    int a = 10, b = 3, c = 5, d = 7, e = 2, f, g, h, i, j;

    f = a + (b * c) - d / e + (a % b) * (c - d);
    g = ((a - b) * (c + d) / e) % (a + 1);
    h = (a + b * (c - d)) - (e * f) + g * (d - e);

    a = ((a + c * 2) - (b + e) / (d + 1)) * 2;
    b = ((a % 3) + (f - d) * (g + e)) / 4;
    c = ((b * b) - (a + c) * 2 + d) % (e + 1);

    a = (a & b | c ^ d) + (e & f | g ^ h);
    b = (a << 2) + (b >> 1) - (c << 1) + d >> 1;
    c = (~a & b) | (c ^ (d & e)) ^ (f | g);

    a > b ? (c * e - g) : (h / f + e);
    e = (a <= d ? b : c) + (f >= g ? d : h);
    f = a == c ? ((e * g) - h) : ((b - d) + f);

    a += b * c - d;
    b -= (c / e) * (f % 3);
    c *= (g - h) + (a / 2);
    d /= e + (f - a) * 2;
    e %= (b + c * 3) / 2;

    a &= b | (c & d);
    b |= c ^ (d & f);
    c ^= (d | (e & g)) ^ h;
    d <<= (e + 2) % 3;
    e >>= (a - 1) % 2;

    f = ((a + b * c) - (d | e)) & ((f ^ g) + (h - i));
    g = ((a ^ (b & c)) << 1) + ((d | e) >> 2) - h;
    h = a && d ? e + f - g : h + i;
    i = (a | c) + (b ^ d) - ((e & g) + (f << 1)) * 3;
    j = ((a + b - c) * (d | e)) ^ (f & (g + h - i));

    return 0;
}
