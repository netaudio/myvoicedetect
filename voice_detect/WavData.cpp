#include "StdAfx.h"
#include "WavData.h"

CWavData::CWavData(char *pcmfile)
{
	if (pcmfile && *pcmfile != '\0') {
		m_pcmfile = strdup(pcmfile);
	}
}

CWavData::~CWavData(void)
{
}

vector<double> CWavData::getNormalizedData()
{
	vector<double> vecNormalizeData;

	if (m_pcmfile && *m_pcmfile == '\0') {
		return vecNormalizeData;
	}
	
	int ifilelen=0;
	FILE *fp=fopen(m_pcmfile,"rb");
	if (fp) {
		fseek(fp,0,SEEK_END);
		ifilelen=ftell(fp);
		fseek(fp,0,SEEK_SET);
		double *data=new double[ifilelen];
		fread(data,1,ifilelen,fp);
		fclose(fp);

		int i=0;
		for (i=0;i<ifilelen;i++) {
			vecNormalizeData.push_back(data[i]/SHRT_MAX);
		}

		delete[] data;
	}

	
	return vecNormalizeData;
}
