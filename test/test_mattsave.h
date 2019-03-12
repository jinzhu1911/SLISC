#include "../SLISC/matt.h"

void test_mattsave()
{
	using namespace slisc;

	// write to file
	Matt matt;
	matt.open("test.matt", "w");

	// scalars
	Char s8 = 88;
	save(s8, "s8", matt);

	Int si = 99;
	save(si, "si", matt);

	Doub s(3.14159265358979323);
	save(s, "s", matt);

	Comp sc(s, -s);
	save(sc, "sc", matt);

	// vectors
	VecChar v8(3);
	v8[0] = 1; v8[1] = 2; v8[2] = 3;
	save(v8, "v8", matt);
	VecInt vi(3);
	vi[0] = 1; vi[1] = 2; vi[2] = 3;
	save(vi, "vi", matt);
	VecDoub v(3);
	v[0] = 1.; v[1] = 2.; v[2] = 3.;
	save(v, "v", matt);
	VecComp vc(3);
	for (Int i = 0; i < 3; ++i)
		vc[i] = 1 + (Doub)i - I * (Doub)i;
	save(vc, "vc", matt);

	// matrices

	MatInt AI(2, 3);
	AI = 0;
	AI(0, 0) = 1; AI(0, 1) = 3; AI(0, 2) = 5; AI(1, 2) = 11;
	save(AI, "AI", matt);

	MatDoub A(2, 3);
	A = 0;
	A(0, 0) = 1; A(0, 1) = 3; A(0, 2) = 5; A(1, 2) = 11;
	save(A, "A", matt);

	MatComp C(3, 3);
	Comp *pC{ &C(0, 0) };
	for (Int i = 0; i < 9; ++i) {
		pC[i] = 1 + (Doub)i + I * (Doub)i;
	}
	save(C, "C", matt);

	// 3d arrays
	Mat3Doub A3;
	A3.resize(2, 2, 2);
	Doub *pA3 = &A3(0, 0, 0);
	for (Int i = 0; i < 8; ++i)
		pA3[i] = 1. + (Doub)i;
	save(A3, "A3", matt);

	Mat3Comp C3;
	C3.resize(2, 2, 2);
	Comp *pC3 = &C3(0, 0, 0);
	for (Int i = 0; i < 8; ++i)
		pC3[i] = Comp(1. + (Doub)i, (Doub)i);
	save(C3, "C3", matt);

	matt.close();

	// read test

	// scalars
	matt.open("test.matt", "r");

	Int r_si;
	load(r_si, "si", matt);
	if (r_si != si) error("failed!");

	Doub r_s;
	load(r_s, "s", matt);
	if (abs(r_s-s) > 1e-15) error("failed!");

	Comp r_sc;
	load(r_sc, "sc", matt);
	if (abs(r_sc-sc) > 1e-15) error("failed!");

	// vectors
	// TODO: Char

	VecInt r_vi;
	load(r_vi, "vi", matt);
	if (r_vi != vi) error("failed!");

	VecDoub r_v;
	load(r_v, "v", matt);
	r_v -= v;
	if (norm(r_v) > 1e-15) error("failed!");

	VecComp r_vc;
	load(r_vc, "vc", matt);
	r_vc -= vc;
	if (norm(r_v) > 1e-15) error("failed!");

	// matrices
	// TODO: Char

	MatInt r_AI;
	load(r_AI, "AI", matt);
	if (r_AI != AI) error("failed!");

	MatDoub r_A;
	load(r_A, "A", matt);
	r_A -= A;
	if (norm(r_A) > 1e-15) error("failed!");

	MatComp r_C;
	load(r_C, "C", matt);
	r_C -= C;
	if (norm(r_C) > 1e-15) error("failed!");

	// 3D arrays
	Mat3Doub r_A3;
	load(r_A3, "A3", matt);
	r_A3 -= A3;
	if (norm(r_A3) > 1e-15) error("failed!");

	Mat3Comp r_C3;
	load(r_C3, "C3", matt);
	r_C3 -= C3;
	if (norm(r_C3) > 1e-15) error("failed!");

	matt.close();
}
