#pragma once

class CComplex
{
public:
	CComplex(void);
	CComplex(double real,double image);
	virtual ~CComplex(void);
public:
	inline void setReal(double real) {
		m_real = real;
	}

	inline void setImage(double image){
		m_image = image;
	}

	inline double getReal(){
		return m_real;
	}

	inline double getImage(){
		return m_image;
	}

	static CComplex add(CComplex lhs, CComplex rhs) {
		CComplex result(lhs.getReal() + rhs.getReal(), lhs.getImage() + rhs.getImage());
		return result;
	}

	static CComplex multiply(CComplex lhs, CComplex rhs) {
		CComplex result;
		result.setReal(lhs.getReal()*rhs.getReal() - lhs.getImage()*rhs.getImage());
		result.setImage(lhs.getReal()*rhs.getImage() + lhs.getImage()*rhs.getReal());
		return result;
	}

	static CComplex minus(CComplex lhs, CComplex rhs) {
		CComplex result(lhs.getReal() - rhs.getReal(), lhs.getImage() - rhs.getImage());
		return result;
	}
private:
	double m_real;
	double m_image;
};
