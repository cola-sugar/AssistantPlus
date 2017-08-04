#pragma once
//suServerStatus.h
//\brief ��������Agent��������״̬ά����ص��࣬Ŀǰ����:
//       rule, task(order), state�Ĳ���
#include "suServiceInterface.h"
#include <list>

#ifdef WIN32
#include <time.h>
#else 
#include <sys/time.h>
#endif


//�û��¼�
class suEvent
{
public:
	suEvent():id(-1),interval(-1),threadID(-1),timeType(1),selectType(1){GenId();}
	~suEvent(){}
	int SetEvent(){}
	int GenId()
	{
		unsigned int t = (unsigned int)time(0);
		srand(t);
		id = t+ rand()%100 * 10000000;
		return id;
	}

public:
	long   id;                //event id
	string userName;          //reserved
	string moduleName;        //ģ������
	string invokeService;     //���ط���
	string callbackService;   //�ͻ��˻ص�����
	time_t startTime;         //��ʼʱ��
	time_t endTime;           //����ʱ�� reserved
	int    interval;	      //ʱ����,���ȼ��ߣ�����趨������Կ�ʼʱ�䣬��λ����
	int    threadID;          //����¼���Ӧ����������洢��Ӧ�߳�id��Ĭ��-1
	int    timeType;          //1:ָ����Ĭ�ϣ�  2:����(reserved)  3:����(reserved) 4:����(reserved)
	int    selectType;        //1:ָ������   2:�ų�����
	vector<int> orderDate;    //a set of day|week|month need to invoke event
};

//ȫ�ֱ���
class suGlobalVariable
{
public:
	suGlobalVariable(){}
	~suGlobalVariable(){}

	void setVar(string key, string value){gVarible[key]=value;}
	string getVar(string key){return gVarible[key];}

public:
	map<string,string> gVarible;
};



/*\class susuServiceStatus
**\brief: a singleton class derived from class suEStatus
*         translate its pointer to dll, all invoked methods are done in the server space 
*
*/
class suEStatus : public suStatus
{
public:
	typedef list<suEvent> EventList;              //event list
	suEStatus(){};
	~suEStatus(){};

	//static suEStatus* gOnly();
	//Set add event to the system event list
	virtual int addEvent(string username, string moduleName,string invokeService, string callBack, time_t startTime);
	virtual int addEvent(string username, string moduleName,string invokeService, string callBack, int interval);
	virtual void deleteEvent(int id=0);     //delete event by id
	

	virtual void setGlobalVar(string key, string value);    //add key
	virtual string getGlobalVar(string key);                //get key

	suGlobalVariable&   GetGlobalVar(){return gVariable_;}
	EventList&          GetEventList(){return eventList_;}

	virtual void stopServer();
	virtual void pauseServer();
	
private:
	//static suEStatus*   gOnly_;
	EventList       eventList_;         //!<�洢�¼��б�
	suGlobalVariable gVariable_;        //!<�洢ȫ�ֱ���
};

/* \class suAgentMemory: The derived class of suStatus
 * \brief Use database to hold the Agent memories.
 **/
class suAgentMemory : public suStatus
{
public:
	suAgentMemory();
	~suAgentMemory();
	virtual int addEvent(std::string username, std::string moduleName, std::string invokeService, std::string callBack, time_t startTime){ return -1; }
	virtual int addEvent(std::string username, std::string moduleName, std::string invokeService, std::string callBack, int interval){ return -1; }
	virtual void deleteEvent(int id = 0){}     //delete event by id


	virtual void setGlobalVar(std::string key, std::string value);    //addKey
	virtual std::string getGlobalVar(std::string key);                //getKey

	virtual void setGlobalList(std::string key, std::vector<std::string> stringList);             //we can use database (like Redis) in the derive class
	virtual std::vector<std::string> getGlobalList(std::string key);      //return global list 

	virtual void remove(std::string key);


	virtual int  getRule(std::string id, suAgent::Rule& rule);
	virtual int  getTask(std::string id, suAgent::Task& task);
	virtual int  getRules(std::vector<suAgent::Rule> &ruleList);
	virtual int  getTasks(std::vector<suAgent::Task> &taskList);
	virtual int  getKeys(std::vector<suAgent::Pairs> &keyList);
	virtual std::string  addRule(suAgent::Rule rule);    //update if rule.id <> ""  return id
	virtual std::string  addTask(suAgent::Task task);    //update if task.id <> ""  return id
	
	virtual int  remRule(std::string id);
	virtual int  remTask(std::string id);
	virtual int  remKey(std::string key);

	virtual int getServices(std::vector<suAgent::Pairs> &services);

	int init();

	//shutdown server
	virtual void stopServer(){}
	//pause server
	virtual void pauseServer(){}

private:
	//use impl to hide implementation detail
	class DB_;
	DB_   *pDB_;//redispp::Connection *pConn_;	
};