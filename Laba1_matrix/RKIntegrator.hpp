#pragma once

//integrator class
template <typename Ode, typename Method>
class RKIntegrator {
private:
	
public:
	Ode ode;
	Method method;
	//default constructor
	RKIntegrator() = default;

	//the constructor of the class as an object of the differential equation (in case the parameters need to be set manually)
	RKIntegrator(const Ode& new_ode) : ode(new_ode) {}

	//one step integration
	Vector<double> OneStep(double t0, double h, const Vector<double>& s0, bool choose_b = true)
	{
		Matrix<double> hub(method.c.size(), s0.size());
		Vector<double> sum(s0.size());
		Vector<double> b = choose_b ? method.b_main : method.b_subs;
		//Vector<Vector<double>> k(method.c.size());
		for (size_t i{ 0 }; i < method.c.size(); ++i)
		{
			Vector<double> temp(s0.size());
			for (size_t j{ 0 }; j < i; ++j)
			{
				for (unsigned short int n{ 0 }; n < s0.size(); ++n)
					temp[n] += method.A(i, j) * hub(j, n);
			}
			for (unsigned short int m{ 0 }; m < s0.size(); ++m)
			{
				hub(i, m) = ode(t0 + method.c[i] * h, s0 + h * temp))[m];
				sum[m] += h * (hub(i, m) * b[i]);
			}
		}
		//std::cout << s0 + sum;	
		return s0 + sum;
	}



	Matrix<double> NSteps(double t0, size_t numsteps, double h, const Vector<double>& s0, bool choose_b = 1)
	{
		Matrix<double> result(numsteps + 1, s0.size());
		std::cout << s0;
		for (unsigned short int n{ 0 }; n < s0.size(); ++n)
			result(0, n) = s0[n];
		//result(0, 1) = s0[1];
		double current_time = t0;
		for (size_t i = 1; i < numsteps + 1; i++)
		{
			current_time += h;
			
			for (unsigned short int n{ 0 }; n < s0.size(); ++n)
			{
				Vector<double> temp(2);
				temp[n] = result(i - 1, n);
				result(i, n) = OneStep(current_time, h, temp, choose_b)[n];
			}
			/*temp[0] = result(i - 1, 0);
			temp[1] = result(i - 1, 1);
			result(i, 1) = OneStep(current_time, h, temp, choose_b)[0];
			result(i, 0) = OneStep(current_time, h, temp, choose_b)[0];*/
		}
		return result;
	}



	//N integration steps
	/*Matrix<double> NSteps(double t0, size_t numsteps, double h, Vector<double>& s0, bool choose_b = 1)
	{
		Matrix<double> result = Matrix<double>(2, numsteps + 1);
		result(0, 0) = s0(0, 0);
		result(1, 0) = s0(1, 0);
		double time = t0;
		for (int i = 1; i < numsteps + 1; i++) {
			time += h;
			Matrix<double> temp(2, 1);
			temp(0, 0) = result(0, i - 1);
			temp(1, 0) = result(1, i - 1);
			result(0, i) = OneStep(time, h, temp,  choose_b)[0];
			result(1, i) = OneStep(time, h, temp,  choose_b)[1];
		}
		return result;
	}

	/*Matrix<double> OneStep(double t0, double h, Matrix<double> s0, bool choose_b = true)
		{
			Matrix<double> b = choose_b ? method.b_main : method.b_subs;
			Matrix<double> k(2, method.c.Rows());
			Matrix<double> add(2, 1);
			for (int i = 0; i < method.c.Rows(); i++) {
				Matrix<double> temp(2, 1);
				for (size_t j = 0; j < i; j++) {
					temp(0, 0) += (method.A(i, j) * k(0, j));
					temp(1, 0) += (method.A(i, j) * k(1, j));
				}
				k(0, i) = (t0 + method.c(i, 0) * h, s0 + h * temp)(0, 0);
				k(1, i) = (t0 + method.c(i, 0) * h, s0 + h * temp)(1, 0);
				add(0, 0) += h * (k(0, i) * b(i, 0));
				add(1, 0) += h * (k(1, i) * b(i, 0));
			}
			return s0 + add;
		}*/
};

