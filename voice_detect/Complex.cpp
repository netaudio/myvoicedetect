#include "StdAfx.h"
#include "Complex.h"

CComplex::CComplex(void)
{
	m_real = 0.0;
	m_image = 0.0;
}

CComplex::CComplex(double real,double image)
{
	m_real = real;
	m_image = image;
}

CComplex::~CComplex(void)
{
}
