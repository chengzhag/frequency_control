#pragma once

namespace sky {
	class Interpolation {
	public:
		double *dataX, *dataY;
		int length;
		Interpolation(double *x, double *y, int l);
		double operator()(double x);
	};

	Interpolation::Interpolation(double *x, double *y, int l)
	{
		dataX = x;
		dataY = y;
		length = l;
	}

	double Interpolation::operator()(double x)
	{
		for (int i = 0; i < length; i++)
		{
			if (x >= dataX[i] && x <= dataX[i + 1])
			{
				return (x - dataX[i]) / (dataX[i + 1] - dataX[i])*(dataY[i + 1] - dataY[i]) + dataY[i];
			}
		}
		return 0;
	}


}

