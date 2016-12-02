#pragma once

class CDataProcess
{
public:
	CDataProcess(void);
	virtual ~CDataProcess(void);

	/**
     * ���mfcc����
     */
	static vector<vector<double>> getMfcc(const vector<double>& nomalizeData);

	/**
     *����DTW����
     */
	static double getDTW(const vector<vector<double>> &mfcc1, const vector<vector<double>> &mfcc2);


};
