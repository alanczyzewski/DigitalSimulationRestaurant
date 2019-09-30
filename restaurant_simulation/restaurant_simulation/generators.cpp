#include "stdafx.h"
#include "generators.h"
#include <cmath>

int Generators::seed_ = 63527281;
//1- 63527281; //2- 738291392; 3- 612039133; 4- 129348237; 5- 425163492; 
//6- 22248329; 7- 65428821; 8- 773629001; 9- 737269203; 10- 1002363281;
int Generators::n2_ = 4;
int Generators::n3_ = 10;
int Generators::n4_ = 4;
int Generators::b_ = 14; //seats at the buffet
int Generators::mi_b_ = 3200; //time buffet
int Generators::lambda_f_ = 1900; //time consumption
int Generators::c_ = 4;//number of checkouts

int Generators::w_ = 7; //number of waiters
double Generators::p1_ = 0.15; //how many people in the group
double Generators::p2_ = 0.36;
double Generators::p3_ = 0.30;
double Generators::p4_ = 0.19;
int Generators::mi_a_ = 330;//arrival new clients
int Generators::sigma_a_ = 20; //arrival new clients
int Generators::s_ = 400; //time manager
int Generators::sigma_b_ = 100; //time buffet
int Generators::lambda_n_ = 1100;//time serving drinks
int Generators::lambda_j_ = 2400; //time serving food
int Generators::lambda_p_ = 700; //time checkout
int Generators::mi_e_ = 4200; //alarm
int Generators::sigma_e_ = 50; //alarm

double Generators::Uniform()
{
	const double m = 2147483647;
	const auto a = 16807;
	const auto q = 127773;
	const auto r = 2836;
	const auto h = seed_ / q;
	seed_ = a * (seed_ - q * h) - r * h;
	if (seed_ < 0) seed_ += m;
	return seed_ / m;
}

double Generators::Exponential(const double avg)
{
	return (-1)*(log(Uniform()))*avg;
}

double Generators::Normal(const int average, const double variance)
{
	double x = 0;
	const auto n = 12;
	for (auto i = 0; i < n; i++)
	{
		x += Uniform();
	}
	return ((x - (double(n) / 2))*(variance * 12 / n)) + average;
}
