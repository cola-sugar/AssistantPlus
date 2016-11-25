/*!\file ServerMain.cpp Assistant+�ڵ�������
*  \brief ͨ�������ļ��趨����������������Socket�������񣬹رպ���Դ�ͷš�
*         suAgentService��ͨ��suAgentHelper��ֱ�ӵ�ʵ��ServerMain�еĳ�ʼ���ͼ�������������
*         ʹsuAgent�ڵ������ͨ��windows����ʽ����
*
*  \date  2016-11-25
*  \author Yao Yuan
*
*/
/*
 Main Documentation
! \mainpage �����ĵ�

<center><img src = "../IDCenter.jpg"></center>

����ĵ������ˡ�Assistant+���Ĵ���˵�������ĵ���Ҫ�����¼���������ɣ�


- \subpage subpage1 ģ�����
- \subpage subpage2 ����˵��
- \subpage subpage3 ʹ���ֲ�
*/

//-----------------------------------------------------------

/*! \page subpage1 Assistant+ģ�����
Assistant+��һ�������á��������е�����Agent�����书�ܰ�����
\li ��ͨ�������״̬��֪���ݷ���
\li �ܹ�������AgentЭͬ
\li ��ͨ���ⲿ���������չ

\section sec_module   ģ�����

Assitant+��Ϊ���¼�������:
\li \ref һ��web server��������boost::asio�����д���<a href = "https://github.com/eidheim/Simple-Web-Server">
Socket Server </a>��������Socket����������ϸʵ�֡�
\li <b>���</b>���֣���Բ�ͬӦ�ã�����Ӧ�÷�������ͨ��suServiceInterface.h�ж����suService�ӿڽ��뵽ϵͳ����תΪ�ڲ�/�ⲿ�ɷ��ʵ�Web����
\li ֪ʶ�⣺ʹ��Redis���ݿ�洢��
\li <b>����ģ��</b>��ʵ����CServerSet�У�Ƕ�뵽Socket����ѭ���У�ͨ��������ǰ֪ʶ���е�״̬��������ģ���а�����������������Ͷ���ִ�У�ͬ��Ҳͨ���ⲿ���ʵ��
*/

//-----------------------------------------------------------

/*! \page subpage2 ����˵��

*/

/*! \page subpage3 ʹ���ֲ�

*/
#include "config.h"
#include "suSocketServer.hpp"
#include "ServerSet.h "
#include "suAgentController.h"

int main(int /*argc*/, char * /*argv[ ]*/)
{
	//suAgentHelper agent;

	CServerSet::gOnly().LoadSetting();
	CServerSet::gOnly().ReadModules("");

	try
	{
		int nThread = CServerSet::gOnly().GetOption().GetOptionVal(L"Number of Threads");
		int nPOrt = CServerSet::gOnly().GetOption().GetOptionVal(L"Serverport");

		HttpServer server(nPOrt, nThread);

		std::thread server_thread([&server]() {
			//Start server
			server.start();
		});

		//init agent memory
		/*
		if (!CServerSet::gOnly().init())
		{
			Utility::MessageBoxA("��������Redis��");
			server.stop();
			CServerSet::gOnly().gClear();
			server_thread.join(); //wait until server is done

			return 0;
		}
		*/
		//start agent AI Controller
		//suController::gOnly().start();

		server_thread.join(); //wait until server is done

		CServerSet::gOnly().gClear();
		return 0;


	}
	catch (const suException &e)
	{	    
		Console::WriteLine(e.what());
	}
	catch (...)
	{
		Console::WriteLine("Unexpected exception");
	}

}