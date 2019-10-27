#pragma once
#include <array>
namespace generators
{
	double Uniform();   //Uniform generator
	double Exponential(double); //Exponential generator
	double Normal(const int average, const double variance);  //Gauss generator

	static const std::array<int, 10> seeds = { 63527281, 738291392, 612039133, 129348237, 425163492, 
												22248329, 65428821, 773629001, 737269203, 1002363281 };
	static int seed = seeds[0];
	static double p = 0.45; //probability (buffet)
	static int n2 = 4; //number of 2-person tables
	static int n3 = 10; //number of 3-person tables
	static int n4 = 4; //number of 4-person tables
	static int b = 14; //seats at the buffet
	static int mi_b = 3200; //time buffet
	static int lambda_f = 1900; //time consumption
	static int c = 4; //number of checkouts
	static int k = 7; //number of waiters
	static double p1 = 0.15; //probability (1-person)
	static double p2 = 0.36; //probability (2-person)
	static double p3 = 0.30; //probability (3-person)
	static double p4 = 0.19; //probability (4-person)
	static int mi_a = 330; //arrival new clients
	static int sigma_a = 20; //arrival new clients
	static int s = 40; //time manager
	static int sigma_b = 100; //time buffet
	static int lambda_n = 1100; //time serving drinks
	static int lambda_j = 2400; //time serving food
	static int lambda_p = 700; //time checkout
}

