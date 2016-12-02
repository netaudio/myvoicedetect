#pragma once

class CMfcc
{
public:
	CMfcc(void);
	virtual ~CMfcc(void);

	static void bitReverseCopy(vector<double> &data, int len);
	
	/**
	 * ʵ�����ٸ���Ҷ�任
	 * @param data ����������
	 * @param len ���ݳ���
	 * @return ���ٸ���Ҷ�任������fft_data��n=0ΪƵ��Ϊ0��ʵ����n=1ΪƵ�ʵ�len/2��ʵ����n=2*iΪƵ�ʵ�iʵ����n=2*i+1ΪƵ�ʵ�i�鲿
	 */
	static vector<double> rFFT(vector<double> &data, int len);

	/**
	 *
	 * @param fft �źſ��ٸ���Ҷ�任����
	 * @param len �źų���
	 * @param m MFCC�����˲�����Ŀ
	 * @param l MFCC����ά��,һ��С���˲�����m
	 * @param fre ������
	 * @return l��MFCC����
	 */
	static vector<double> mfcc(const vector<double> &fft, int len, int m, int l, int fre);

	/**
     *
     * @param mfcc ���������
     * @param k ʱ���
     * @return һ�ײ������
     */
	static vector<vector<double>> diff(const vector<vector<double>> &mfcc, int k);


};
