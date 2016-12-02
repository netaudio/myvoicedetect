#include "StdAfx.h"
#include "Matrix.h"

CMatrix::CMatrix(int row,int column)
{
	this->row = row;
	this->column = column;


	if(row<1||column<1) {
		cout<<"������������������������0��"<<endl;  
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

//�������캯�����Ծ���A�����¾���B����A��B���г�ʼ�� 
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

//�����������Զ��еĶ�̬�ռ�����ͷ� 
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
	cout<<"������"<<row*column<<"������Ϊ����Ԫ�أ�"<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++) {
			cin>>*(*(pt+i)+j);
		}
	}
	cout<<"==============================================================================="<<endl;
}

//��������������Ծ������ʽ���������
void CMatrix::Output() 
{
	for(int i=0;i<row;i++) {
		for(int j=0;j<column;j++) {
			cout<<left<<setw(5)<<*(*(pt+i)+j);
		}
		cout<<endl;
	}
}


