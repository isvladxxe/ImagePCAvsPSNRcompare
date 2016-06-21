#pragma once
#include"XImage.h"
#include<iostream>
namespace DiplomaPCA
{
	using namespace std;

	static class XPSNR
	{
		inline	double XPSNR::getMax(XImage * img1, XImage * img2)
		{
			double max = 0;
			for (int w = 0; w < img1->Width; w++)
			{
				for (int h = 0; h < img1->Height; h++)
				{
					max = img1->ECOMP[w][h] > max ? img1->ECOMP[w][h] : max;
					max = img2->ECOMP[w][h] > max ? img2->ECOMP[w][h] : max;
				}
			}
			return max;
		}
		static	inline	double XPSNR::MSE(XImage * img1, XImage * img2)
		{
			double sum_sq = 0;
			double mse;
			for (int i = 0; i < img1->Width; i++)
			{
				for (int j = 0; j < img1->Height; j++)
				{
					double p1 = img1->ECOMP[i][j];
					double p2 = img2->ECOMP[i][j];
					double err = p2 - p1;
					sum_sq += (err * err);
				}
			}
			mse = sum_sq / (img1->Width * img1->Height);

			return mse;
		}
	public:

		static	inline	double XPSNR::CalcPSNR(XImage * img1, XImage * img2)
		{
			double psnr = 0;
			//psnr = 20 * Math::Log10(255.0 / MSE(img1, img2));
			psnr = 10 * Math::Log10((double)255 * 255 / MSE(img1, img2));

			return psnr;
		}
		static inline bool	PSNR(XImage * img1, XImage * img2)
		{
			if ((img1->Width / img1->Height) == (img1->Width / img1->Height))
			{
				if (img1->Norma == img2->Norma)
				{
					return 1;
				}
				img1->init();
				img1->PCA(3);
				img2->init();
				img2->PCA(3);
				double res = CalcPSNR(img1, img2);
				cout << "PSNR " << res << endl;
				img1->clean();
				img2->clean();
				if (res >= CONFIG::getInstance().accuracyPSNR)
				{
					return 1;
				}
				return 0;

			}

		}
	};

}