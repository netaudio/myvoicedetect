#pragma once

class CPreprocess
{
public:
	CPreprocess(void);
	virtual ~CPreprocess(void);

	static double getMax(const vector<double> &vecDataInput);

    /**
     * ��ͨ�˲�
     * @param x0 �����ź�
     * @return �˲����ź�
     */
	static vector<double> highpass(const vector<double> &vecDataInput);

    /**
     * ��ö�ʱ����
     * @param x0 �����ź�
     * @param fre ������
     * @return ��ʱ�����ź�
    */
	static vector<double> shortTernEnergy(const vector<double> &vecDataInput,int fre);
	
	/**
     * ��ö�ʱ�������ź�
     * @param x0 �����ź�
     * @param fre ������
     * @return ��ʱ�������ź�
     */
	static vector<double> shortTernCZ(const vector<double> &vecDataInput,int fre);

	/**
     * �˵���
     * @param stEnergy ��ʱ�����ź�
     * @param stCZ ��ʱ�������ź�
     * @return �����˵�ֵ��list����ż�±�ֱ��Ӧ�����ε���βֵ
     */
	static vector<int> divide(const vector<double> &stEnergy, const vector<double> &stCZ);

	static void hamming(vector<double> &x0);
};
