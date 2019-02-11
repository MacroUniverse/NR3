#include "../SLISC/disp.h"
#include "../SLISC/arithmetic.h"
#include "../SLISC/time.h"

void test_disp()
{
	using namespace slisc;
	VecChar v8(3);
	linspace(v8, 1, 3); disp(v8);
	VecInt vi(3);
	linspace<Int>(vi, 1, 3); disp(vi);
	MatChar A8(2, 3);
	linspace(A8, 1, 6); disp(A8);
	MatInt AI(2, 3);
	linspace(AI, 1, 6); disp(AI);
	Mat3Doub A3(2, 2, 2);
	linspace(A3, 1, 8); disp(A3);
	Mat3Comp C3(2, 2, 2);
	linspace(C3, Comp(0, 1), Comp(14, 15)); disp(C3);
}
