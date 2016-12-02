#pragma once

class CWavData
{
public:
	CWavData(char *pcmfile);
	virtual ~CWavData(void);
	
	vector<double> getNormalizedData();
	
	char *m_pcmfile;
};
