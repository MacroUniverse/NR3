// do all available tests of SLISC
// TODO: test mparith.h not finished

#include "test_meta.h"
#include "test/test_scalar_arith.h"
#include "test_dense.h"
#include "test_arithmetic.h"
#include "test_fixsize.h"
#include "test_sparse.h"
#include "test/test_eig.h"
#include "test_interp1.h"
#include "test_fft.h"
#include "test_random.h"
//#include "test_eigen_basics.h"
//#include "test_eigen_linsolve.h"
//#include "test_eigen_fft.h"
#include "test_time.h"
#include "test_coulomb.h"
#include "test_input.h"
#include "test_disp.h"
#include "test_print.h"

// #include "test/test_mparith.h"

inline void test_all()
{
	using std::cout; using std::endl;
	using slisc::Input;

	cout << "test_meta()" << endl;
	test_meta();
	cout << "test_scalar_arith()" << endl;
	test_scalar_arith();
	cout << "test_dense()" << endl;
	test_dense();
	cout << "test_arithmetic()" << endl;
	test_arithmetic();
	cout << "test_fixsize()" << endl;
	test_fixsize();
	cout << "test_sparse()" << endl;
	test_sparse();
	cout << "test_eig()" << endl;
	test_eig();
	cout << "test_interp1()" << endl;
	test_interp1();
	cout << "test_fft()" << endl;
	test_fft();
	cout << "test_rand()" << endl;
	test_random();
	cout << "test_time()" << endl;
	test_time();
	cout << "test_coulomb()" << endl;
	test_coulomb();

	// eigen
	/*cout << "test_eigen_basics()" << endl;
	test_eigen_basics();
	cout << "test_eigen_linsolve()" << endl;
	test_eigen_linsolve();
	cout << "test_eigen_fft()" << endl;
	test_eigen_fft();*/

	cout << "auto test successful!" << endl;
	Input inp;

	if (inp.Bool("test_disp() ?")) {
		test_disp();
	}
	if (inp.Bool("test_print() ?")) {
		test_print();
	}
	//cout << "test_mparith()" << endl;
	//test_mparith();
	cout << "testing successful!" << endl;
}
