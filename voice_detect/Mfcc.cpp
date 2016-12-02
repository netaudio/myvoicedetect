#include "StdAfx.h"
#include "Mfcc.h"
#include "Complex.h"

#define round(val) (val> 0.0) ? floor(val+ 0.5) : ceil(val- 0.5)

CMfcc::CMfcc(void)
{
}

CMfcc::~CMfcc(void)
{
}

void CMfcc::bitReverseCopy(vector<double> &data, int len)
{
	int n = (int)ceil(log10((double)len) / log10((double)2));
	for (int l = 0; l < len/2; l++) {
		int temp = l;
		for (int i = 0, j = n - 1; i < j ; i++, j--){
			if (((temp >> i & 0x01) ^ (temp >> j & 0x01)) == 1){
				temp ^= 1 << i;
				temp ^= 1 << j;
			}
		}
		if (temp != l) {
			double tmp = data[l];
			data[l] = data[temp];
			data[temp] = tmp;
		}
	}
}

vector<double> CMfcc::rFFT(vector<double> &data, int len)
{
	bitReverseCopy(data, len);
	vector<CComplex> complex_fft;
	complex_fft.resize(len);
	int i = 0;
	for (i = 0; i < len; ++i){
		complex_fft[i].setReal(data[i]);
		complex_fft[i].setImage(0.0);
	}
	int n = (int)ceil(log10((double)len) / log10((double)2));
	for (int i = 1; i <= n; i++) {
		int m = 1 << i;
		CComplex W_m(cos(2*M_PI/m), sin(2*M_PI/m));

		for (int j = 0; j < len; j += m) {
			CComplex W(1.0, 0.0);
			for (int k = 0; k < m/2; k++){
				CComplex t = CComplex::multiply(W, complex_fft[j + k + m/2]);
				CComplex u = complex_fft[j + k];
				complex_fft[j + k] = CComplex::add(u, t);
				complex_fft[j + k + m/2] = CComplex::minus(u, t);
				W = CComplex::multiply(W, W_m);
			}
		}
	}

	vector<double> fft_data;
	fft_data.resize(len);

	fft_data[0] = complex_fft[0].getReal();
	fft_data[1] = complex_fft[len / 2].getReal();
	for (int i = 1; i < len / 2; i++){
		fft_data[2 * i] = complex_fft[i].getReal();
		fft_data[2 * i + 1] = complex_fft[i].getImage();
	}

	return fft_data;
}

vector<double> CMfcc::mfcc(const vector<double> &fft, int len, int m, int l, int fre)
{
	double max_mel = 2595*log10((double)(1 + fre/(2*700)));
	double inter_mel = max_mel/(m + 1);
	int i = 0,j = 0;

	vector<double> cen_fre;
	cen_fre.resize(m + 2);
	cen_fre[0] = 0;
	for (int i = 1; i <= m; i++){
		cen_fre[i] = (pow(10, inter_mel*i / 2595) - 1) * 700;
	}
	cen_fre[m + 1] = fre / 2;

	vector<int> d_cen;
	d_cen.resize(m + 2);
	d_cen[0] = 0;
	for (i = 1; i <= m + 1; ++i) {
		d_cen[i] = (int)round(cen_fre[i] * len / fre);
	}
	
	vector<double> power_fre;
	power_fre.resize(len / 2 + 1);

	power_fre[0] = fft[0] * fft[0];
	for (int i = 1; i < len / 2; ++i) {
		power_fre[i] = fft[2 * i] * fft[2 * i] + fft[2 * i + 1] * fft[2 * i + 1];
	}
	power_fre[len / 2] = fft[1] * fft[1];

	vector<double> output;
	output.resize(m);
	
	for (i = 1; i <= m; ++i) {
		output[i - 1] = 0;
		for (int j = d_cen[i - 1]; j < d_cen[i + 1]; ++j) {
			if (j <= d_cen[i])
				output[i - 1] += power_fre[j] * (j - d_cen[i - 1] + 1) / (d_cen[i] - d_cen[i - 1] + 1);
			else
				output[i - 1] += power_fre[j] * (d_cen[i + 1] - j + 1) / (d_cen[i + 1] - d_cen[i] + 1);
		}
	}

	for (i = 0; i < m; i++) {
		output[i] = log10(output[i]);
	}
	
	vector<double> c_mfcc;
	c_mfcc.resize(l);
	for (i = 0; i < l; i++) {
		c_mfcc[i] = 0;
		for (int j = 0; j < m; j++) {
			c_mfcc[i] += output[j] * cos(M_PI * (i + 1) * (j + 0.5) / m);
		}
	}

	return c_mfcc;
}

vector<vector<double>> CMfcc::diff(const vector<vector<double>> &vecmfcc, int k)
{
	int length = vecmfcc.size();
	int dimension = vecmfcc[0].size();
	int i = 0,j = 0;

	vector<vector<double>> vecdiff;
	vecdiff.resize(length);
	for (i = 0;i < length; ++i) {
		vecdiff[i].resize(dimension);

		for (j = 0; j < dimension; ++j) {
			vecdiff[i][j] = 0;
		}
	}

	for (j = 0; j < dimension; j++) {
		for (i = 0; i < length; i++) {
			if (i < k) {
				vecdiff[i][j] = vecmfcc[i + 1][j] - vecmfcc[i][j];
			} else if (i >= length - k) {
				vecdiff[i][j] = vecmfcc[i][j] - vecmfcc[i - 1][j];
			} else {
				double sum = 0.0;
				double div = 0.0;
				for (int count = 1; count <= k; count++) {
					sum += count * (vecmfcc[i + count][j] - vecmfcc[i - count][j]);
					div += 2 * pow((double)k, 2);
				}
				vecdiff[i][j] = sum / sqrt(div);
			}
		}
	}
	return vecdiff;
}
