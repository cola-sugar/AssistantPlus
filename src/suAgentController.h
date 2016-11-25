#pragma once

/*!\file suController.h suAgent controller
*  \brief The main agent action contoller
*         
*         �ṩһ���򵥵�Agent���ؽ���ִ���̣߳�
*         ���ڲ�ͬ��Agent�����߳��ڵ�����Ӧ���
*         ���ʵ�ʹ���
*         1.Scan task -> process
*         2.Scan status -> process
*         3.Scan
*
*  \date  2015-02-01
*  \author Yao Yuan
*
*/
#include <Engines.h>

class suController : public suThread
{
public:
	static suController &gOnly();
	void thread();

private:
	static suController* sOnly_;
	suController(){}
};

