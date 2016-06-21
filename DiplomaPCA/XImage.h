#pragma once

#include <iostream>
#include "XHelper.h"
#include"ConfigSingleton.h"

namespace DiplomaPCA
{
	using namespace std;
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Windows::Forms;
	using namespace System::Threading::Tasks;
	/*XXE IMAGE CLASS*/
	public class XImage
	{
	private:
		/*alpha нужно для востановления изображения из PCA*/
		double* alpha = new double[3];

	public:

		int Width;
		int Height;
		double Norma;
		string Path;
		/*PCA MATRIX*/
		Double** ECOMP;
		/*COLOR COMPONENT*/
		Byte *** RGB;
		/*Состояние чи загруженны данные цветовых компонент в память*/
		bool initState;

		inline	XImage::XImage(String^ path)
		{
			Path = Xhelper::sysStrToStdStr(path);
			init();
			calcAll();
		}


		/*Вывод из RGB в Bitmap для отображения на винФорме*/
		inline	Bitmap^ XImage::ToBitmap()
		{
			if (!initState)
			{
				init();
			}

			Bitmap^ result = gcnew  Bitmap(Width, Height);
			BitmapData^ bmpData = result->LockBits(System::Drawing::Rectangle(0, 0, Width, Height), ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
			IntPtr^ scan = bmpData->Scan0;
			Byte* ptr = (Byte*)scan->ToPointer();
			Byte* ptrHelper = ptr;
			for (int y = 0; y < Height; y++) //Порядок перебора критичен, т. к. изображение хранится в памяти построчно
			{
				for (int x = 0; x < Width; x++)
				{
					*(ptr++) = RGB[x][y][2];
					*(ptr++) = RGB[x][y][1];
					*(ptr++) = RGB[x][y][0];
				}
				ptrHelper += bmpData->Stride;
				ptr = ptrHelper;
			}
			result->UnlockBits(bmpData);

			return result;
		}

		/*Итеративный подсчет PCA
		>CountIteration - Количество итерацый int>0	*/
		inline	void XImage::PCA(int CountIteration)
		{
			if (!initState)
			{
				init();
			}

			alpha[0] = alpha[1] = alpha[2] = 1 / Math::Sqrt(3);

#pragma omp parallel for num_threads(4)
			for (int i = 0; i < this->Width; i++)
			{
				for (int j = 0; j < this->Height; j++)
				{
					this->ECOMP[i][j] = (this->RGB[i][j][0] * alpha[0] + this->RGB[i][j][1] * alpha[1] + this->RGB[i][j][2] * alpha[2]);
				}
			}
			double* beta = new double[3];
			double bot = 0;
			double N;
#pragma omp parallel for num_threads(4)
			for (int it = 0; it < CountIteration; it++)
			{
				beta[0] = beta[1] = beta[2] = bot = 0;
				for (int i = 0; i < this->Width; i++)
				{
#pragma omp parallel for num_threads(4)
					for (int j = 0; j < this->Height; j++)
					{
						bot += this->ECOMP[i][j] * this->ECOMP[i][j];
						beta[0] += this->RGB[i][j][0] * this->RGB[i][j][0];
						beta[1] += this->RGB[i][j][1] * this->RGB[i][j][1];
						beta[2] += this->RGB[i][j][2] * this->RGB[i][j][2];
					}
				}
				beta[0] = beta[0] / bot;
				beta[1] = beta[1] / bot;
				beta[2] = beta[2] / bot;

				N = Math::Sqrt(beta[0] * beta[0] + beta[1] * beta[1] + beta[2] * beta[2]);
				alpha[0] = beta[0] / N;
				alpha[1] = beta[1] / N;
				alpha[2] = beta[2] / N;
			}
		}

		/*Востановление изображения из PCA и вывод в Bitmap для винФорм*/
		inline	Bitmap ^ XImage::PcaResBitmap()
		{
			if (!initState)
			{
				init();
			}

			Bitmap^ result = gcnew  Bitmap(Width, Height);
			BitmapData^ bmpData = result->LockBits(System::Drawing::Rectangle(0, 0, Width, Height), ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
			IntPtr^ scan = bmpData->Scan0;
			Byte* ptr = (Byte*)scan->ToPointer();
			Byte* ptrHelper = ptr;
			double temp = 0;
			for (int y = 0; y < Height; y++) //Порядок перебора критичен, т. к. изображение хранится в памяти построчно
			{
				for (int x = 0; x < Width; x++)
				{
					for (int rt = 2; rt > -1; rt--)
					{
						temp = (alpha[rt] * ECOMP[x][y]);
						*(ptr++) = (Byte)(temp > 255 ? 255 : temp);
					}
				}
				ptrHelper += bmpData->Stride;
				ptr = ptrHelper;
			}
			result->UnlockBits(bmpData);


			return result;
		}

		void calcAll()
		{
			if (!initState)
			{
				init();
			}


			if (CONFIG::getInstance().pcaNorm)
			{
				PCA(3);
				CalcNormaPCA();
			}
			else
			{
				CalcNorma();
			}

			clean();
		}

		/*Подсчет нормы PCA*/
		inline	double XImage::CalcNormaPCA()
		{
			if (!initState)
			{
				init();
			}

			double norma = 0;



#pragma omp  parallel  for num_threads(4)
			for (int i = 0; i < Width; i++)
			{
				for (int j = 0; j < Height; j++)
				{
#pragma omp atomic
					norma += ECOMP[i][j] * ECOMP[i][j];
				}
			}

			norma = Math::Sqrt(norma / (Width * Height));

			Norma = norma;
			return norma;
		}

		/*Подсчет нормы RGB*/
		inline	double XImage::CalcNorma()
		{

			if (!initState)
			{
				init();
			}

			double norma = 0;

#pragma omp  parallel  for num_threads(4)
			for (int i = 0; i < Width; i++)
			{
				for (int j = 0; j < Height; j++)
				{
#pragma omp atomic
					norma += RGB[i][j][0] * RGB[i][j][0];
#pragma omp atomic
					norma += RGB[i][j][1] * RGB[i][j][1];
#pragma omp atomic
					norma += RGB[i][j][2] * RGB[i][j][2];
				}
			}

			norma = Math::Sqrt(norma / (Width * Height));

			Norma = norma;
			return norma;
		}

		/*Инициализация компонент изображения для дальнейшых рассчетов*/
		inline	void XImage::init()
		{

			String^ pathSYS = gcnew String(Xhelper::stdStrToSysStr(Path));

			Bitmap img(pathSYS);
			Width = img.Width;
			Height = img.Height;
			ECOMP = new double*[Width];
			RGB = new Byte**[Width];

#pragma omp parallel for num_threads(4)
			for (int i = 0; i < Width; i++)
			{
				ECOMP[i] = new double[Height];
				RGB[i] = new Byte*[Height];
				for (size_t j = 0; j < Height; j++) RGB[i][j] = new Byte[3];
			}

			BitmapData^ bmpData = img.LockBits(System::Drawing::Rectangle(0, 0, Width, Height), ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
			IntPtr scan = bmpData->Scan0;
			Byte* ptr = (Byte*)scan.ToPointer();
			Byte* ptrHelper = ptr;

			//Порядок перебора критичен, т. к. изображение хранится в памяти построчно
			for (int y = 0; y < img.Height; y++)
			{
				for (int x = 0; x < img.Width; x++)
				{
					RGB[x][y][2] = *(ptr++);//b
					RGB[x][y][1] = *(ptr++);//g
					RGB[x][y][0] = *(ptr++);//r
				}
				ptrHelper += bmpData->Stride;
				ptr = ptrHelper;
			}
			img.UnlockBits(bmpData);
			initState = true;

		}

		/*Очистка памяти от компонент изображения*/
		inline  void XImage::clean()
		{
			if (RGB)
			{

#pragma omp parallel for num_threads(4)
				for (int i = 0; i < Width; i++)
				{
					for (int j = 0; j < Height; j++) delete[]RGB[i][j];
				}
#pragma omp parallel for num_threads(4)
				for (int i = 0; i < Width; i++)
				{
					delete[]RGB[i];
					delete[]ECOMP[i];
				}
				delete[] RGB;
				delete[] ECOMP;
			}
			initState = false;
		}

		inline	XImage::~XImage()
		{
			if (initState)
			{
				clean();
			}
			delete[] alpha;

		}
	};

}