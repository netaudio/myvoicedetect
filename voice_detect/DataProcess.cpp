#include "StdAfx.h"
#include "DataProcess.h"
#include "DTWrecognize.h"
#include "Preprocess.h"
#include "Mfcc.h"

CDataProcess::CDataProcess(void)
{
}

CDataProcess::~CDataProcess(void)
{
}

vector<vector<double>> CDataProcess::getMfcc(const vector<double>& nomalizeData)
{
	const int NUM_OF_MFCC = 12;
	const int NUM_OF_FILTER = 26;
	vector<vector<double>> result;
	//预加重信号
	vector<double> preEmphasis = CPreprocess::highpass(nomalizeData);
	//短时能量和短时过零率
	vector<double> stApm = CPreprocess::shortTernEnergy(preEmphasis, 8000);
	vector<double> stCZ = CPreprocess::shortTernCZ(preEmphasis, 8000);
	//端点检测
	vector<int> endPoints;
	endPoints = CPreprocess::divide(stApm, stCZ);

	if (endPoints.size() < 2) {
		return result;
	}
	
	int i = 0,j = 0,k = 0,l = 0;
	vector<vector<double>> speechFrames;

	for (i = 0; i < endPoints.size(); i = i + 2){
		for (j = endPoints[i]; j < endPoints[i+1]; ++j) {
			vector<double> frame;
			frame.resize(512);
			for (k = 256*j,l=0; k < preEmphasis.size(),l<512; ++k,++l) {
				frame[l] = preEmphasis[k];
			}
			CPreprocess::hamming(frame);
			speechFrames.push_back(frame);
		}
	}

	vector<vector<double>> mfcc;
	mfcc.resize(speechFrames.size());
	for (i=0;i < speechFrames.size(); ++i) {
		mfcc[i].resize(NUM_OF_MFCC);
	}

	for (i = 0; i < speechFrames.size(); ++i) {
		vector<double> fftData = CMfcc::rFFT(speechFrames[i], 512);
		vector<double> mfccData = CMfcc::mfcc(fftData, 512, NUM_OF_FILTER, NUM_OF_MFCC, 8000);
		mfcc[i] = mfccData;
	}
	vector<vector<double>> dtMfcc = CMfcc::diff(mfcc, 2); //mfcc一阶差分参数
	
	result.resize(speechFrames.size());
	for (i = 0; i < speechFrames.size(); ++i) {
		result[i].resize(2 * NUM_OF_MFCC);
	}
	
	for (i = 0; i < result.size(); ++i){ //合并mfcc和一阶差分参数
		for (k = 0; k < NUM_OF_MFCC; ++k) {
			result[i][k]=mfcc[i][k];
		}
		for (k = NUM_OF_MFCC; k < 2 * NUM_OF_MFCC; ++k) {
			result[i][k]=dtMfcc[i][k-NUM_OF_MFCC];
		}
	}
	return result;
}

double CDataProcess::getDTW(const vector<vector<double>> &mfcc1, const vector<vector<double>> &mfcc2)
{
	return CDTWrecognize::dtw(mfcc1,mfcc2);
}
