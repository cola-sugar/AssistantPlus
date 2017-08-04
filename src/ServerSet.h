#pragma once
/* \class CServerSet
*  \brief �������󣬸������Server���ú�ά������ʱ״̬
*  \date  2006-07-08
*/
/*
*2006-08-01
*Ϊ�ʺ��Զ��������󣬸Ļ�ԭ�в������Ľṹ
*/

#include "config.h"
#include "Option.h"
#include "suServerStatus.h"

////////////////////////////////////////////////////////////////
//Define all interface here
///////////////////////////////////////////////////////////////
#define IDEGINEDIR "IDEgine/"
#define APPDIR     "APP/"
#define LOGDIR     "Log/"
#define CURVERSION 0x00010000


typedef suLock CServerLock;

////////////////////////////////////////////////////////////////
//Server Status Structure
///////////////////////////////////////////////////////////////
/*! \class CServerSet
*   \brief ����Server������Ϣ
*
*/

class CServerSet
{
public:
	typedef map<string, suService*>   ModulesMap; //map between services' name and modules' interface

	//std::string GetCurrentDir();
	static CServerSet&  gOnly();
	void gClear();

	int    init();
	int    LoadSetting();


	//!����������
	void ShutdownsServer();
	void PauseResumeServer();

	//!˽�б����趨
	void    SetLog(BOOL isLog_);                  //!<�Ƿ�д��־
	void    SetThreadNum(int n) { nThreadNum = n; }
	void    SetInBufSize(DWORD dSize) { nInBufSize_ = dSize; }
	void    SetOutBufSize(DWORD dSize) { nOutBufSize_ = dSize; }

	BOOL    IsLog() { return isLog_; }
	BOOL    IsLoad() { return bPlugInLoad; }
	void    SetLogFileName(const std::string &name);//!<����log�ļ���

	std::string  GetComputerIP(std::vector<std::string> &ipArr);    //!<���ص�һ��IP��ַ�����������������û�г�ʼ����ʱ�򣬷������WSACleanup()�����������ж�
	std::string  GetDir() { return m_strCurDir; }
	std::string  GetIP() { return strBindIp_; }
	std::string  GetWebRootDir() { return m_webRootDir; }
	std::string  GetOption(std::string key);
	const int    GetThreadNum() { return nThreadNum; }
	const DWORD  GetInBufSize() { return nInBufSize_; }
	const DWORD  GetOutBufSize() { return nOutBufSize_; }
	COption&     GetOption() { return m_Options; }


	//New Load dll functions
	suService*   LoadModule(string sModuleFilePath);
	suService*   LoadModuleEx(string sModuleFilePath);//load module with input pointer
	void         ReadModules(string sModulesPath);

	//This is a dangous function
	void         GetServices(std::vector<std::string> &nameLists);

	suService*   GetModule(string sServiceName);

public:

	suAgentMemory *pStatus;

private:
	static CServerSet* gOnly_;
	CServerSet();
	~CServerSet();

	std::string strBindIp_;
	std::string m_strCurDir;
	std::string m_webRootDir;
	std::string m_appRootDir;
	DWORD       m_version;


	BOOL           isLog_;
	int            nThreadNum;
	DWORD          nInBufSize_;     //!<���ջ�������С
	DWORD          nOutBufSize_;    //!<���ͻ�������С

	BOOL           bPlugInLoad;     //!<�Ƿ�װ��plugin

	COption        m_Options;
	ModulesMap     modulesMapList_;     //!<�洢װ��Ķ�̬���ӿ⺯���ӿ�������Services����ӳ�䣬Services��=��̬ģ���ļ���
};


