#pragma once

//integrator class
template <typename Ode, typename Method>
class RKIntegrator {
private:
	
public:
	Ode ode;
	Method mode;
	//default constructor
	RKIntegrator() = default;

	//the constructor of the class as an object of the differential equation (in case the parameters need to be set manually)
	RKIntegrator(const Ode& new_ode) : mode(new_ode) {}

	//one step integration
	Vector<double> OneStep(double initial_time, double h, const Vector<double>& elemental, bool choice = 1)
	{
		Matrix<double> hub(mode.c.size(), elemental.size());
		Vector<double> pam(elemental.size());
		Vector<double> b = choice ? mode.b_main : mode.b_subs;
		for (size_t i{ 0 }; i < mode.c.size(); ++i)
		{
			Vector<double> temp(elemental.size());
			for (size_t j{ 0 }; j < i; ++j)
			{
					temp[0] += mode.A(i, j) * hub(j, 0);
					temp[1] += mode.A(i, j) * hub(j, 1);
			}
			for (unsigned short int m{ 0 }; m < elemental.size(); ++m)
			{
				hub(i, m) = ode(initial_time + mode.c[i] * h, (h * temp) + elemental)[m];
				pam[m] += h * (hub(i, m) * b[i]);
			}
		} 
		return elemental + pam;
	}
	//N steps integration
	Matrix<double> NSteps(double initial_time, size_t number_of_steps, double h, const Vector<double>& elemental, bool choice = 1)
	{
		Matrix<double> result(number_of_steps + 1, elemental.size());
		result(0, 0) = elemental[0];
		result(0, 1) = elemental[1];
		double current_time = initial_time;
		for (size_t i{ 1 }; i < number_of_steps + 1; i++)
		{
			current_time += h;
			Vector<double> temp(2);
			temp[0] = result(i - 1, 0);
			temp[1] = result(i - 1, 1);
			result(i, 1) = OneStep(current_time, h, temp, choice)[1];
			result(i, 0) = OneStep(current_time, h, temp, choice)[0];
		}
		return result;
	}
};

