#pragma once
class CONFIG
{
private:
	CONFIG() {}
	CONFIG(const CONFIG&);
	CONFIG& operator=(CONFIG&);
public:
	static CONFIG& getInstance() {
		static CONFIG  instance;
		return instance;
	}
	bool pcaNorm = 1;
	bool psnrON = 1;
	double accuracyPSNR = 24.0;
	double accuracy=0;
	bool acceptDelete=1;

};