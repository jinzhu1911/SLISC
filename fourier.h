#include "nr3.h"

struct WrapVecDoub {
	VecDoub vvec;
	VecDoub &v;
	Int n, mask;

	WrapVecDoub(const Int nn) : vvec(nn), v(vvec), n(nn/2),
	mask(n-1) {validate();}

	WrapVecDoub(VecDoub &vec) : v(vec), n(vec.size()/2),
	mask(n-1) {validate();}
		
	void validate() {if (n&(n-1)) throw("vec size must be power of 2");}

	inline Complex& operator[] (Int i) {return (Complex &)v[(i&mask) << 1];}

	inline Doub& real(Int i) {return v[(i&mask) << 1];}

	inline Doub& imag(Int i) {return v[((i&mask) << 1)+1];}

	operator VecDoub&() {return v;}
};

void four1(Doub *data, const Int n, const Int isign);

void four1(VecDoub_IO &data, const Int isign);

void four1(VecComplex_IO &data, const Int isign);

void four1(MatComplex_IO &data, const Int isign);

void realft(VecDoub_IO &data, const Int isign);

void sinft(VecDoub_IO &y);

void cosft1(VecDoub_IO &y);

void cosft2(VecDoub_IO &y, const Int isign);