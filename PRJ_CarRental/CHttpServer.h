#pragma once

#include "httplib.h"
#include "CDatabase.h"

class CHttpServer
{
public:
	CHttpServer(CDatabase* pConnection);
	~CHttpServer();

	void InitServer();
	void StartServer();
	void StopServer();


protected:
	int m_nPort = 8080;
	int m_nSendTimeout = 15;
	int m_nReceiveTimeout = 15;
	int m_nTransferTimeout = 30;

	httplib::Server* m_pServer = nullptr;
	std::thread m_serverThread;
	CDatabase* m_DBConnection;
};

