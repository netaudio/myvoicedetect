#pragma once

class CMatrix
{
public:
	CMatrix(int row,int column);//���캯��
	virtual ~CMatrix(void);//��������
	CMatrix(const CMatrix &);//�������캯��
	void Creat();//����ֵ����
	void Output();//�����������
private:  
	int row;  
	int column;  
	double **pt;
};
