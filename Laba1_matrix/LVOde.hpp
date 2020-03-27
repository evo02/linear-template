#pragma once


class LVOde {
private:
	//Lotka–Volterra parameters
	double alpha;
	double beta;
	double gamma;
	double sigma;

public:
	//constructor by parameters
	LVOde(double new_alpha = 1, double new_beta = 1.5, double new_gamma = 2, double new_sigma = 1.5) : alpha(new_alpha), beta(new_beta), gamma(new_gamma), sigma(new_sigma) {};

	//operator overload to calculate the right side of the system of equations
	Vector<double> operator()(double t, Vector<double> s) 
	{
		double dx = (alpha - beta * s[1])*s[0];
		double dy = (sigma*s[0] - gamma)* s[1];
		return { dx, dy };
	}
};