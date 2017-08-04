#pragma once
/*! \class COption
*   \brief ���������������Ϣ���������ļ��д�ȡ����
*   \Change load/save info with tinyXML2  2017/08/04
*   \Change ��vector<t_OptionsCacheNew>�����µ�������Ϣd
*   \Change ʹ��suResourceMgr����������Ϣ 2013-5-4
*/
//#include "OptionTypes.h"
#include <string>
#include <map>
class COption
{
public:
	COption(void);
	~COption(void);

	//search option by name
	std::string  GetOption(std::string name);
	int          GetOptionVal(std::string name);
	void         LoadSetting();

	void      dump();
	void      Init();

	bool      m_bInitialized;
private:
	std::map<std::string, std::string> options_;
};

