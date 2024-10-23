#include "CHttpServer.h"
#include <threads.h>

CHttpServer::CHttpServer(CDatabase* pConnection) : m_DBConnection(pConnection),
	m_pServer(nullptr)
{
	m_pServer = new httplib::Server();
}

CHttpServer::~CHttpServer()
{
	if (m_pServer != nullptr)
		StopServer();
}

void CHttpServer::InitServer()
{
	if (!m_pServer->is_valid())
	{
		std::cout << "Could not start the server" << std::endl;
		return;
	}

	m_pServer->set_read_timeout(m_nReceiveTimeout, 0);
	m_pServer->set_write_timeout(m_nSendTimeout, 0);
	m_pServer->set_keep_alive_timeout(30);

	m_pServer->Get("/CarRenting/Rent", [this](const httplib::Request& req, httplib::Response& res)
		{
			std::string strHeader = "application/json";
			std::string plateId = "";
			std::string username = "";
			int daysRented;

			if (req.has_param("plate-id"))
			{
				plateId = req.get_param_value("plate-id");
			}

			if (req.has_param("days-rented"))
			{
				daysRented = std::stoi(req.get_param_value("days-rented"));
			}

			if (req.has_param("user-name"))
			{
				username = req.get_param_value("user-name");
			}

			m_DBConnection->SetCustomerRented(username, m_DBConnection->getCar(plateId), daysRented);

			std::string strResponse = username + " has rented vehicle (" + plateId + ")";
			res.set_content(strResponse, strHeader);
		});

	m_pServer->Get("/CarRenting/Return", [this](const httplib::Request& req, httplib::Response& res)
		{
			std::string strHeader = "application/json";
			std::string plateId = "";
			std::string username = "";
			int daysRented;

			if (req.has_param("plate-id"))
			{
				plateId = req.get_param_value("plate-id");
			}

			if (req.has_param("days-rented"))
			{
				daysRented = std::stoi(req.get_param_value("days-rented"));
			}

			if (req.has_param("user-name"))
			{
				username = req.get_param_value("user-name");
			}

			m_DBConnection->SetCustomerReturn(username, m_DBConnection->getCar(plateId), daysRented);

			std::string strResponse = username + " has returned vehicle (" + plateId + ")";
			res.set_content(strResponse, strHeader);
		});


	if (!m_pServer->listen("0.0.0.0", m_nPort))
	{
		std::cout << "Could not start the server at port " << m_nPort << std::endl;
		return;
	}
}

void CHttpServer::StartServer()
{
	std::cout << "Starting server at port " << m_nPort << std::endl;
	m_serverThread = std::thread(&CHttpServer::InitServer, this);
	m_serverThread.detach();
}

void CHttpServer::StopServer()
{
	std::cout << "Stopping server..." << std::endl;
	m_pServer->stop();

	if (m_serverThread.joinable())
		m_serverThread.join();

	if (m_pServer != nullptr)
		delete(m_pServer);
}
