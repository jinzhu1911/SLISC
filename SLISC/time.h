#pragma once
#define SLISC_TIME_H
#include "slisc.h"
#include <chrono>
#include <ctime>

namespace slisc {

// === time utilities ===

namespace internal {
// global data for tic(), toc()
struct Tic_Data
{
	Int ind = 0;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point starts[20];
};

// global data for ctic(), ctoc()
struct Ctic_Data
{
	Int ind = 0;
	Llong start;
	Llong starts[20];
};

extern Tic_Data tic_data; extern Ctic_Data ctic_data;
} // namespace internal

inline void tic()
{ internal::tic_data.start = std::chrono::steady_clock::now(); }

inline Doub toc() {
	std::chrono::steady_clock::time_point tic_time_stop
		= std::chrono::steady_clock::now();
	std::chrono::duration<double> t
		= std::chrono::duration_cast<std::chrono::duration<double>>
		(tic_time_stop - internal::tic_data.start);
	return t.count();
}

inline void tic(Int &ind)
{
	ind = internal::tic_data.ind;
	internal::tic_data.starts[ind] = std::chrono::steady_clock::now();
	++internal::tic_data.ind;
}

inline Doub toc(Int ind) {
	std::chrono::steady_clock::time_point tic_time_stop
		= std::chrono::steady_clock::now();
	std::chrono::duration<double> t
		= std::chrono::duration_cast<std::chrono::duration<double>>
			(tic_time_stop - internal::tic_data.starts[ind]);
	return t.count();
}

inline void ctic() { internal::ctic_data.start = clock(); }

inline Doub ctoc()
{ return (clock() - internal::ctic_data.start) / (Doub)CLOCKS_PER_SEC; }

inline void pause()
{ printf("\nPress return to continue.\n"); getchar(); }

inline void pause(Doub t)
{ tic(); while (toc() < t); }

} // namespace slisc
