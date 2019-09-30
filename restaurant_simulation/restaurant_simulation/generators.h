#pragma once
class Generators
{
public:

	double static  Uniform();   //Uniform generator
	double static Exponential(double); //Exponential generator
	double static Normal(const int average, const double variance);  //Gauss generator
	Generators();
	~Generators();

	static int seed_;
	//can't change
	static int n2_;// = 4; //number of 2-person tables
	static int n3_; //kN3 = 10; //number of 3-person tables
	static int n4_;// kN4 = 4; //number of 4-person tables
	static int b_; //= 14; //seats at the buffet
	static int mi_b_; //kMiB //= 3200; //time buffet
	static int lambda_f_;// kLambdaF //= 1900; //time consumption
	static int c_; //= 4; //number of checkouts
	//can change
	static int w_; //= 7; //number of waiters
	static double p1_;// kP1 //= 0.11;
	static double p2_;//0.33
	static double p3_;//0.33
	static double p4_;//0.23
	static int mi_a_;//1900
	static int sigma_a_;//200
	static int s_;//30
	static int sigma_b_;//100
	static int lambda_n_;//300
	static int lambda_j_;//1700
	static int lambda_p_;//200
	static int mi_e_;//4200
	static int sigma_e_;//50

};

