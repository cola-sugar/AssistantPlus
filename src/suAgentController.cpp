#include "suAgentController.h"
#include "ServerSet.h"
suController* suController::sOnly_ = 0;
suController& suController::gOnly()
{
	if (!sOnly_)
	{
		sOnly_ = new suController();
	}
	return *sOnly_;
}

void suController::thread()
{
	CServerSet &pServerSet = CServerSet::gOnly();
	std::string strCAgentIp = pServerSet.GetOption("CAgent Address");
	std::string strCAgentPort = pServerSet.GetOption("CAgent Port");
	while (true)
	{
		if (!strCAgentPort.empty())
		{
			std::cout << "I 'm checking....\n" << std::endl;
			//pServerSet.pStatus->setGlobalVar("ACTION_CONTROLLER", "Checking...");

			//TODO: running with task pool.
			//Now is a single task model.
			string Config = strCAgentIp + "&" + strCAgentPort;
			std::string task = CServerSet::gOnly().GetModule("TaskQuery")->run(Config); // ��CAgentȡ���񣬷�������XML; 

			if (task != "tasknull" && !task.empty())
			{
				std::string taskID_ = CServerSet::gOnly().GetModule("Translator")->run(task); //���ؽ�������XML�����洢����������ID.

				std::string selectedService = CServerSet::gOnly().GetModule("RuleEngine")->run(taskID_); //�ж����ܹ�ִ�и�����,������ִ�еķ�������
						
								
				if (!selectedService.empty())
				{					
					string assign = CServerSet::gOnly().GetModule("Executor")->run(taskID_ + "," + Config); //�Ƿ���䣬��ִ��
					if (assign == "OK")
					{
						string RunRes = CServerSet::gOnly().GetModule(selectedService)->run(taskID_);

						//�������ִ����ϣ��ύ����
						if (RunRes == "OK")
						{
							string strRes_ = CServerSet::gOnly().GetModule("TaskSubmit")->run(taskID_ + "," + Config);  //�ύ������Ϣ
							//TODO: If fail(!OK), push into a un-submited array
						}
					}

				}

			}

		}
		sleep(2000);
	}
}