#pragma once
#include"XImage.h"
namespace DiplomaPCA
{

	using namespace System::Threading::Tasks;
	static ref class XPCA
	{
	public:
		inline	static double* calcBeta(XImage * image)
		{
			double * beta = new double[3];
			double bot = 0;

#pragma omp parallel for num_threads(4)
			for (int i = 0; i < image->Width; i++)
			{

				for (int j = 0; j < image->Height; j++)
				{
					bot += image->ECOMP[i][j] * image->ECOMP[i][j];
					beta[0] += image->RGB[i][j][0] * image->RGB[i][j][0];
					beta[1] += image->RGB[i][j][1] * image->RGB[i][j][1];
					beta[2] += image->RGB[i][j][2] * image->RGB[i][j][2];
				}
			}

			beta[0] = beta[0] / bot;
			beta[1] = beta[1] / bot;
			beta[2] = beta[2] / bot;

			return beta;
		}

		inline	static double* calcAlpha(double* beta)
		{
			double* alpha = new double[3];
			double N = Math::Sqrt(beta[0] * beta[0] + beta[1] * beta[1] + beta[2] * beta[2]);
			alpha[0] = beta[0] / N;
			alpha[1] = beta[1] / N;
			alpha[2] = beta[2] / N;

			return alpha;
		}

		inline	static double* getAlpha(XImage *image)
		{
			return calcAlpha(calcBeta(image));
		}
	};

}