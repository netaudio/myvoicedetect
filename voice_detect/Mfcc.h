#pragma once

class CMfcc
{
public:
	CMfcc(void);
	virtual ~CMfcc(void);

	static void bitReverseCopy(vector<double> &data, int len);
	
	/**
	 * 实数快速傅里叶变换
	 * @param data 待处理数据
	 * @param len 数据长度
	 * @return 快速傅里叶变换后数据fft_data，n=0为频率为0的实部，n=1为频率点len/2的实部，n=2*i为频率点i实部，n=2*i+1为频率点i虚部
	 */
	static vector<double> rFFT(vector<double> &data, int len);

	/**
	 *
	 * @param fft 信号快速傅里叶变换数据
	 * @param len 信号长度
	 * @param m MFCC三角滤波器数目
	 * @param l MFCC参数维度,一般小于滤波器数m
	 * @param fre 采样率
	 * @return l组MFCC参数
	 */
	static vector<double> mfcc(const vector<double> &fft, int len, int m, int l, int fre);

	/**
     *
     * @param mfcc 待差分数组
     * @param k 时间差
     * @return 一阶差分数组
     */
	static vector<vector<double>> diff(const vector<vector<double>> &mfcc, int k);


};
