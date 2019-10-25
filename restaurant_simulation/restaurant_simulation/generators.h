#pragma once
#include <array>
namespace generators
{
	static const std::array<int, 10> seeds_ = { 63527281, 738291392, 612039133, 129348237, 425163492, 22248329, 65428821, 773629001, 737269203, 1002363281 };
	static int seed_ = seeds_[0];
	//can't change
	static int n2_ = 4; //number of 2-person tables
	static int n3_ = 10; //number of 3-person tables
	static int n4_ = 4; //number of 4-person tables
	static int b_ = 14; //seats at the buffet
	static int mi_b_ = 3200; //time buffet
	static int lambda_f_ = 1900; //time consumption
	static int c_ = 4; //number of checkouts
	//can change
	static int w_ = 7; //number of waiters
	static double p1_ = 0.15;
	static double p2_ = 0.36;
	static double p3_ = 0.30;
	static double p4_ = 0.19;
	static int mi_a_ = 330; //arrival new clients
	static int sigma_a_ = 20; //arrival new clients
	static int s_ = 70; //time manager
	static int sigma_b_ = 100; //time buffet
	static int lambda_n_ = 1100; //time serving drinks
	static int lambda_j_ = 2400; //time serving food
	static int lambda_p_ = 700; //time checkout
	static int mi_e_ = 4200; //alarm
	static int sigma_e_ = 50; //alarm

	double Uniform();   //Uniform generator
	double Exponential(double); //Exponential generator
	double Normal(const int average, const double variance);  //Gauss generator
}

