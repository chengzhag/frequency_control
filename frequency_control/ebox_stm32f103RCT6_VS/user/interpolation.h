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
		if (x < dataX[0])
		{
			return (x - dataX[0]) / (dataX[1] - dataX[0])*(dataY[1] - dataY[0]) + dataY[0];
		}
		else if (x > dataX[length - 1]) {
			return (x - dataX[length - 1]) / (dataX[length - 1] - dataX[length - 2]) \
				*(dataY[length - 1] - dataY[length - 2]) + dataY[length - 1];
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (x >= dataX[i] && x <= dataX[i + 1])
				{
					return (x - dataX[i]) / (dataX[i + 1] - dataX[i])*(dataY[i + 1] - dataY[i]) + dataY[i];
				}
			}
		}
		return 0;
	}


}

