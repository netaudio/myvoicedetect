#include "StdAfx.h"
#include "Preprocess.h"

#define signum(x) ((double)(x>0?1:(x<0?-1:0)))

CPreprocess::CPreprocess(void)
{
	double a = signum(4);
	double b = signum(-4);
	double c = signum(0);
}

CPreprocess::~CPreprocess(void)
{
}

double CPreprocess::getMax(const vector<double> &vecDataInput)
{
	if (vecDataInput.size()==0) {
		return 0;
	}

	double max = vecDataInput[0];
	int i=0;
	int len = vecDataInput.size();
	
	for (i=0;i<len;i++) {
		if (vecDataInput[i] > max) {
			max = vecDataInput[i];
		}
	}

	return max;
}

vector<double> CPreprocess::highpass(const vector<double> &vecDataInput)
{
	vector<double> vecDataOutput;
	int len = vecDataInput.size();
	vecDataOutput.resize(len);
	vecDataOutput[0]=vecDataInput[0];
	int i=0;
	for (i=1;i<len;i++) {
		vecDataOutput[i]=vecDataInput[i]-0.9375*vecDataInput[i-1];
	}
	return vecDataOutput;
}

vector<double> CPreprocess::shortTernEnergy(const vector<double> &vecDataInput,int fre)
{
	vector<double> vecDataOutput;
	int div = 512;
	int len = vecDataInput.size();
	int num_div = (int)(len*2/div)-1;
	vecDataOutput.resize(num_div);
	int i=0,j=0;
	for (i=0;i<num_div;++i) {
		double sum = 0.0;
		for (j=0;j<div;++j) {
			sum += abs(vecDataInput[div*i/2+j]);
		}
		vecDataOutput[i]=sum;
	}

	return vecDataOutput;
}

vector<double> CPreprocess::shortTernCZ(const vector<double> &vecDataInput,int fre)
{
	vector<double> vecDataOutput;
	int div = 512;
	int len = vecDataInput.size();
	int num_div = (int)(len*2/div)-1;
	vecDataOutput.resize(num_div);
	int i=0,j=0;
	for (i=0;i<num_div;++i) {
		double sum = 0.0;
		for (j=1;j<div;++j) {
			sum += 0.5 * (abs(signum(vecDataInput[div * i / 2 + j] - 0.005) - signum(vecDataInput[div * i / 2 + j - 1] - 0.005))
				+ abs(signum(vecDataInput[div * i / 2 + j] + 0.005) - signum(vecDataInput[div * i / 2 + j - 1] + 0.005)));
		}
		vecDataOutput[i]=sum;
	}

	return vecDataOutput;
}

vector<int> CPreprocess::divide(const vector<double> &stEnergy, const vector<double> &stCZ)
{
	double maxEnergy = getMax(stEnergy);
	double amp1 = max(0.8,maxEnergy/10);//短时能量门限值
	double amp2 = max(1.6,maxEnergy/5);

	double maxCZ = getMax(stCZ);
	double zcr1 = maxCZ / 15;//短时能量门限值
	double zcr2 = maxCZ / 8;
	
	int status = 0;
	int count = 0;
	int silence = 0;
	
	int minLength = 18;
	int maxSilence = 15;
	
	int i = 0;
	int len1 = stEnergy.size();
	int len2 = stCZ.size();
	
	vector<int> divPoints;
	for (i=0; i < len1; ++i) {
		switch (status) {
			case 0:
				if (stEnergy[i]>amp2 || stCZ[i] > zcr2) {
					status = 2;
					divPoints.push_back(max(i-count-1,0));
					++count;
					silence = 0;
				} 
				else if (stEnergy[i]>amp1 || stCZ[i] > zcr1)
				{
					status = 1;
					++count;
				}
				else {
					status = 0;
					count = 0;
				}
				break;
			case 1:
				if (stEnergy[i] > amp2 || stCZ[i] > zcr2) {
					status = 2;
					divPoints.push_back(max(i - count, 0));
					++count;
					silence = 0;
				}
				else if (stEnergy[i] > amp1 || stCZ[i] > zcr1) {
					status = 1;
					++count;
				}
				else {
					status = 0;
					count = 0;
				}
				break;
			case 2:
				if (stEnergy[i] > amp1 || stCZ[i] > zcr1) {
					status = 2;
					silence = 0;
					++count;
				}
				else if (count < minLength) {
					status = 0;
					silence = 0;
					count = 0;
					divPoints.pop_back();
				}
				else {
					silence++;
					if (silence < maxSilence)
						++count;
					else
						status = 3;
				}
				break;
			case 3:
				divPoints.push_back(i - silence/2);
				status = 0;
				silence = 0;
				count = 0;
				break;
		}
	}
	
	if ((divPoints.size() & 0x01) == 1 && status == 2){
		divPoints.push_back(stEnergy.size() - silence/2 - 1);
	}

	return divPoints;
}

void CPreprocess::hamming(vector<double> &x0)
{
	int length = x0.size();

	for (int i = 0; i < length; ++i) {
		x0[i] = x0[i] * (0.54 - 0.46 * cos(2 * M_PI * i / (length - 1)));
	}
}
