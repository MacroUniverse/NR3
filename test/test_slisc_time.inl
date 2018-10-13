#include "../slisc_time.h"

// test time utilities
void test_time()
{
	// cpu time
	ctic(); pause(0.114);
	if (abs(ctoc() - 0.114) > 1e-4) error("failed!");

	// physical time
	Int ind;
	tic(); pause(0.114);
	if (abs(toc() - 0.114) > 1e-4) error("failed!");
	tic(ind); pause(0.114);
	if (abs(toc(ind) - 0.114) > 1e-4) error("failed!");
	if (ind != 0) error("failed!");
	tic(ind); pause(0.114);
	if (abs(toc(ind) - 0.114) > 1e-4) error("failed!");
	if (ind != 1) error("failed!");
}
