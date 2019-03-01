#pragma once
#include "slisc.h"

namespace slisc {

// translate from anglib.f90
// as directly as possible! all vars values unchanged.

// anglib.f90: angular momentum coupling coefficients in Fortran 90
// Copyright (C) 1998  Paul Stevenson

Doub factorial(Int_I n) {
	Doub res;
	if (n == 0 || n == 1)
		return 1.;
	else
		return n * factorial(n - 1);
}

Doub binom(Int_I n, Int_I r) {
	Doub res;
	if (n == r || r == 0)
		return 1.;
	else if (r == 1)
		return n;
	else
		return n / Doub(n - r)*binom(n - 1, r);
}

// clebsch gordan coefficient [j1/2,m1/2,j2/2,m2/2,j/2,m/2]
Doub cleb(Int_I j1, Int_I m1, Int_I j2, Int_I m2, Int_I j, Int_I m) {

	Doub cleb, factor, sum;
	Int par, z, zmin, zmax;

	if (2 * (j1 / 2) - Int(2 * (j1 / 2.0)) != 2 * (abs(m1) / 2) - Int(2 * (abs(m1) / 2.0)) ||
		2 * (j2 / 2) - Int(2 * (j2 / 2.0)) != 2 * (abs(m2) / 2) - Int(2 * (abs(m2) / 2.0)) ||
		2 * (j / 2) - Int(2 * (j / 2.0)) != 2 * (abs(m) / 2) - Int(2 * (abs(m) / 2.0)) ||
		j1<0 || j2<0  || j<0 || abs(m1)>j1 || abs(m2)>j2 ||
		abs(m)>j || j1 + j2<j || abs(j1 - j2)>j || m1 + m2 != m) {
		cleb = 0.;
	}
	else {
		factor = 0.0;
		factor = binom(j1, (j1 + j2 - j) / 2) / binom((j1 + j2 + j + 2) / 2, (j1 + j2 - j) / 2);
		factor = factor * binom(j2, (j1 + j2 - j) / 2) / binom(j1, (j1 - m1) / 2);
		factor = factor / binom(j2, (j2 - m2) / 2) / binom(j, (j - m) / 2);
		factor = sqrt(factor);

		zmin = max(0, max(j2 + (j1 - m1) / 2 - (j1 + j2 + j) / 2, j1 + (j2 + m2) / 2 - (j1 + j2 + j) / 2));
		zmax = min((j1 + j2 - j) / 2, min((j1 - m1) / 2, (j2 + m2) / 2));

		sum = 0.0;
		for (z = zmin; z <= zmax; ++z) {
			par = 1;
				if (2 * (z / 2) - int(2 * (z / 2.0)) != 0)
					par = -1;
			sum = sum + par * binom((j1 + j2 - j) / 2, z)*binom((j1 - j2 + j) / 2, (j1 - m1) / 2 - z)
				* binom((-j1 + j2 + j) / 2, (j2 + m2) / 2 - z);
		}
		cleb = factor * sum;
	}
	return cleb;
}

// 3j symbol [j1/2,m1/2,j2/2,m2/2,j/2,m/2]
// written by me
Doub threej(Int_I j1, Int_I m1, Int_I j2, Int_I m2, Int_I j3, Int_I m3)
{
	return pow(-1, (j1 -j2 -m3)/2.) / sqrt(j3+1.) * cleb(j1, m1, j2, m2, j3, -m3);
}

Doub angdelta(Int_I a, Int_I b, Int_I c) {
	Doub angdelta, scr1;
	scr1 = factorial((a + b - c) / 2);
	scr1 = scr1 / factorial((a + b + c) / 2 + 1);
	scr1 = scr1 * factorial((a - b + c) / 2);
	scr1 = scr1 * factorial((-a + b + c) / 2);
	angdelta = sqrt(scr1);
	return angdelta;
}

// 6j symbol [a/2,b/2,c/2; d/2,e/2,f/2]
Doub sixj(Int_I a, Int_I b, Int_I c, Int_I d, Int_I e, Int_I f)
{
	Doub sixj;
	Int  nlo, nhi, n;

	Doub outfactors, sum, sumterm;

	sixj = 0.;
	if (mod(a + b, 2) != mod(c, 2)) return sixj;
    if(mod(c+d,2) != mod(e,2)) return sixj;
    if(mod(a+e,2) != mod(f,2)) return sixj;
    if(mod(b+d,2) != mod(f,2)) return sixj;
    if(abs(a-b)>c || a+b<c) return sixj;
    if(abs(c-d)>e || c+d<e) return sixj;
    if(abs(a-e)>f || a+e<f) return sixj;
    if(abs(b-d)>f || b+d<f) return sixj;

	outfactors = angdelta(a, e, f) / angdelta(a, b, c);
	outfactors = outfactors * angdelta(b, d, f)*angdelta(c, d, e);

    nlo = max( (a+b+c)/2, max((c+d+e)/2, max((b+d+f)/2, (a+e+f)/2 )));
    nhi = min( (a+b+d+e)/2, min((b+c+e+f)/2, (a+c+d+f)/2));

	sum = 0.;
    for (n = nlo; n <= nhi; ++n) {
		sumterm = pow(-1,n);
       sumterm = sumterm * binom(n+1,n-(a+b+c)/2);
       sumterm = sumterm * binom((a+b-c)/2,n-(c+d+e)/2);
       sumterm = sumterm * binom((a-b+c)/2,n-(b+d+f)/2);
       sumterm = sumterm * binom((b-a+c)/2,n-(a+e+f)/2);
	   sum = sum + sumterm;
    }

	sixj = sum * outfactors;
	return sixj;
}

// 9j symbol [a/2,b/2,c/2; d/2,e/2,f/2; g/2,h/2,i/2]
Doub ninej(Int_I a, Int_I b, Int_I c, Int_I d, Int_I e, Int_I f, Int_I g, Int_I h, Int_I i) {
	Doub ninej, sum;
	Int xlo, xhi, x;

    if(abs(a-b)>c || a+b<c) return 0;
    if(abs(d-e)>f || d+e<f) return 0;
    if(abs(g-h)>i || g+h<i) return 0;
    if(abs(a-d)>g || a+d<g) return 0;
    if(abs(b-e)>h || b+e<h) return 0;
    if(abs(c-f)>i || c+f<i) return 0;
    
    xlo = max(abs(b-f),max(abs(a-i),abs(h-d)));
	xhi = min(b + f, min(a + i, h + d));
    
	sum = 0.;
	for (x = xlo; x <= xhi; x += 2) {
		sum = sum + pow(-1,x)*(x + 1)*sixj(a, b, c, f, i, x)*sixj(d, e, f, b, x, h)*
			sixj(g, h, i, x, a, d);
    }
	ninej = sum;
	return ninej;
}

} // namespace slisc
