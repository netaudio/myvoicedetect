#pragma once

class CDataProcess
{
public:
	CDataProcess(void);
	virtual ~CDataProcess(void);

	/**
     * 获得mfcc参数
     */
	static vector<vector<double>> getMfcc(const vector<double>& nomalizeData);

	/**
     *计算DTW距离
     */
	static double getDTW(const vector<vector<double>> &mfcc1, const vector<vector<double>> &mfcc2);


};
