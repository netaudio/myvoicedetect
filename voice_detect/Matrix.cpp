#include "StdAfx.h"
#include "Matrix.h"

CMatrix::CMatrix(int row,int column)
{
	this->row = row;
	this->column = column;


	if(row<1||column<1) {
		cout<<"矩阵的行数和列数都必须大于0！"<<endl;  
	}
	else
	{
		pt=new double*[row];
		for(int i=0;i<row;i++) {
			*(pt+i)=new double[column];
			for(int j=0;j<column;j++) {
				*(*(pt+i)+j)=0.0;
			}
		}
	}
}

//拷贝构造函数，以矩阵A创建新矩阵B并以A对B进行初始化 
CMatrix::CMatrix(const CMatrix &m)
{  
	row=m.row;
	column=m.column;
	pt=new double*[row];
	for(int i=0;i<row;i++) {
		*(pt+i)=new double[column];
		for(int j=0;j<column;j++) {
			*(*(pt+i)+j)=m.pt[i][j];
		}
	}
}

//析构函数，对堆中的动态空间进行释放 
CMatrix::~CMatrix()
{
	if(pt!=NULL) {
		for(int i=0;i<row;i++) {
			delete[] pt[i];
		}
		delete[] pt;
	}
}

void CMatrix::Creat()
{
	cout<<"请输入"<<row*column<<"个数作为矩阵元素："<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++) {
			cin>>*(*(pt+i)+j);
		}
	}
	cout<<"==============================================================================="<<endl;
}

//矩阵输出函数，以矩阵的形式将矩阵输出
void CMatrix::Output() 
{
	for(int i=0;i<row;i++) {
		for(int j=0;j<column;j++) {
			cout<<left<<setw(5)<<*(*(pt+i)+j);
		}
		cout<<endl;
	}
}


