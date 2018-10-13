#include "../slisc_interp1.h"
#include "../slisc_interp2.h"

void test_interp1()
{
	Int i, N0 = 10;
	VecDoub x0; linspace(x0, 0., 2 * PI, N0);
	VecDoub y0; sin(y0, x0);
	Spline_interp spline(x0, y0);
	for (i = 0; i < N0; ++i) {
		if (abs(spline.interp(x0[i]) - y0[i]) > 1e-15) error("failed!");;
	}

	linspace(x0, 1., (Doub)N0, N0);
	Spline_interp spline1(x0, x0);
	for (i = 1; i < N0; ++i) {
		if (abs(spline1.interp(x0[i] - 0.5) - (x0[i] - 0.5)) > 1e-10) error("failed!");;
	}
}