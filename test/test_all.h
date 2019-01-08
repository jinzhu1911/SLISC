// do all available tests of SLISC
// TODO: test mparith.h not finished

#include "test_time.h"
#include "test_slisc.h"
#include "test_arithmatic.h"
#include "test_sparse.h"
#include "test_interp1.h"
#include "test_fft.h"
#include "test_random.h"
#include "test_eigen_basics.h"
#include "test_eigen_linsolve.h"
#include "test_eigen_fft.h"
#include "test_disp.h"
#include "test_print.h"
#include "test_coulomb.h"
// #include "test/test_mparith.h"

inline void test_all()
{
	using std::cout; using std::endl;

	cout << "test_time()" << endl;
	test_time();
	cout << "test_slisc()" << endl;
	test_slisc();
	cout << "test_self_op()" << endl;
	test_self_op();
	cout << "test_plus_minus_times_devide()" << endl;
	test_plus_minus_times_devide();
	cout << "test_sparse()" << endl;
	test_sparse();
	cout << "test_interp1()" << endl;
	test_interp1();
	cout << "test_fft()" << endl;
	test_fft();
	cout << "test_rand()" << endl;
	test_random();
	cout << "test_eigen_basics()" << endl;
	test_eigen_basics();
	cout << "test_eigen_linsolve()" << endl;
	test_eigen_linsolve();
	cout << "test_eigen_fft()" << endl;
	test_eigen_fft();
	cout << "test_disp()" << endl;
	test_disp();
	cout << "test_print()" << endl;
	test_print();
	cout << "test_coulomb()" << endl;
	test_coulomb();
	//cout << "test_mparith()" << endl;
	//test_mparith();
	cout << "done testing!" << endl;
}
