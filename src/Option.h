#pragma once
/*! \class COption
*   \brief ���������������Ϣ���������ļ��д�ȡ����
*   \Change ��vector<t_OptionsCacheNew>�����µ�������Ϣd
*   \Change ʹ��suResourceMgr����������Ϣ 2013-5-4
*/
//#include "OptionTypes.h"

class COption
{
public:
	COption(void);
	~COption(void);

	BOOL       GetAsCommand(char **pBuffer, DWORD *nBufferLength);
	BOOL        ParseOptionsCommand(unsigned char *pData, DWORD dwDataLength, BOOL bFromLocal = FALSE);

	//search option by name
	std::string  GetOption(std::wstring name);
	int          GetOptionVal(std::wstring name);
	void         LoadSetting();	

	void      dump();

//protected:
	static bool IsNumeric(LPCTSTR str);

	void  Init();

	BOOL           m_bInitialized;

};

