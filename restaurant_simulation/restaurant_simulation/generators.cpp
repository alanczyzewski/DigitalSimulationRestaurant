#include "stdafx.h"
#include "generators.h"
#include <cmath>
namespace generators
{
	double Uniform()
	{
		const double m = 2147483647;
		const auto a = 16807;
		const auto q = 127773;
		const auto r = 2836;
		auto h = seed_ / q;
		seed_ = a * (seed_ - q * h) - r * h;
		if (seed_ < 0) seed_ += m;
		return seed_ / m;
	}

	double Exponential(const double avg)
	{
		return (-1)*(log(Uniform()))*avg;
	}

	double Normal(const int average, const double variance)
	{
		double x = 0;
		const auto n = 12;
		for (auto i = 0; i < n; i++)
		{
			x += Uniform();
		}
		return ((x - (double(n) / 2))*(variance * 12 / n)) + average;
	}
}