#pragma once

class CPreprocess
{
public:
	CPreprocess(void);
	virtual ~CPreprocess(void);

	static double getMax(const vector<double> &vecDataInput);

    /**
     * 高通滤波
     * @param x0 输入信号
     * @return 滤波后信号
     */
	static vector<double> highpass(const vector<double> &vecDataInput);

    /**
     * 获得短时能量
     * @param x0 输入信号
     * @param fre 采样率
     * @return 短时能量信号
    */
	static vector<double> shortTernEnergy(const vector<double> &vecDataInput,int fre);
	
	/**
     * 获得短时过零率信号
     * @param x0 输入信号
     * @param fre 采样率
     * @return 短时过零率信号
     */
	static vector<double> shortTernCZ(const vector<double> &vecDataInput,int fre);

	/**
     * 端点检测
     * @param stEnergy 短时能量信号
     * @param stCZ 短时过零率信号
     * @return 包含端点值的list，奇偶下标分别对应语音段的首尾值
     */
	static vector<int> divide(const vector<double> &stEnergy, const vector<double> &stCZ);

	static void hamming(vector<double> &x0);
};
