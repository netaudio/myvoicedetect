#pragma once

class CMatrix
{
public:
	CMatrix(int row,int column);//构造函数
	virtual ~CMatrix(void);//析构函数
	CMatrix(const CMatrix &);//拷贝构造函数
	void Creat();//矩阵赋值函数
	void Output();//矩阵输出函数
private:  
	int row;  
	int column;  
	double **pt;
};
