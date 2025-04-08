#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "../include/Server.h"


namespace MyChat
{
	ServerKernel::ServerKernel()
	{
		memset(&m_ListenSocket, 0, sizeof(m_SocketAddr_Info));
		memset(&m_SocketAddr_Info, 0, sizeof(m_SocketAddr_Info));
	}

	ServerKernel::~ServerKernel()
	{

	}

	int ServerKernel::init()
	{
		// 开启网络库
		WORD wVersionRequird = MAKEWORD(2, 2);	// MAKEWORD(主版本,副版本)
		WSADATA wdScokMsg;
		int status = WSAStartup(wVersionRequird, &wdScokMsg);
		switch (status)
		{
		case WSASYSNOTREADY:
		{
			std::cout << "[ServerKernel][Init Error]: 重启电脑试试，或者检查网络库" << std::endl;
			return -1;
		}
		break;
		case WSAVERNOTSUPPORTED:
		{
			std::cout << "[ServerKernel][Init Error]: 请更新网络库" << std::endl;
			return -1;
		}
		break;
		case WSAEPROCLIM:
		{
			std::cout << "[ServerKernel][Init Error]: 请尝试关掉不必要的软件，以为当前网络运行提供充足的资源" << std::endl;
			return -1;
		}
		break;
		case WSAEINPROGRESS:
		{
			std::cout << "[ServerKernel][Init Error]: 请重新启动" << std::endl;
			return -1;
		}
		break;
		case SEC_E_OK:
		{
			std::cout << "[ServerKernel]: WSA Start Success!" << std::endl;
		}
		break;
		default:
			std::cout << "[ServerKernel][Init Error]: Unknown Error, Code: " << status << std::endl;
			return -1;
		}

		// 校验版本
		if (2 != HIBYTE(wdScokMsg.wVersion) || 2 != LOBYTE(wdScokMsg.wVersion))
		{
			std::cout << "[ServerKernel][Init Error]: 版本不存在" << std::endl;
			WSACleanup();
			return -1;
		}

		return 0;
	}

	int ServerKernel::start()
	{
		// 创建服务器socket（监听套接字）
		m_ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == m_ListenSocket)
		{
			std::cout << "[ServerKernel][Start Error]: 创建socket失败 error:" << WSAGetLastError() << std::endl;
			WSACleanup();
			return -1;
		}

		// 绑定地址
		std::string ipv4_address = "127.0.0.1";
		USHORT port = 55564;

		m_SocketAddr_Info.sin_family = AF_INET;
		m_SocketAddr_Info.sin_addr.s_addr = inet_addr(ipv4_address.c_str());	// INADDR_ANY --- 任何地址都可以
		m_SocketAddr_Info.sin_port = htons(port);
		if (SOCKET_ERROR == bind(m_ListenSocket, (struct sockaddr*)&m_SocketAddr_Info, sizeof(m_SocketAddr_Info)))
		{
			std::cout << "[ServerKernel][Start Error]: 绑定地址失败 error:" << WSAGetLastError() << std::endl;
			closesocket(m_ListenSocket);
			WSACleanup();
			return -1;
		}
		std::cout << "[ServerKernel]: 绑定地址: " << ipv4_address << "端口: " << port << std::endl;

		// 开始监听
		if (SOCKET_ERROR == listen(m_ListenSocket, SOMAXCONN))
		{
			std::cout << "[ServerKernel][Start Error]: 监听失败 error:" << WSAGetLastError() << std::endl;
			closesocket(m_ListenSocket);
			WSACleanup();
			return -1;
		}
		std::cout << "[ServerKernel]: 开始监听" << std::endl;

		m_bRunning = true;
		m_uTickTime = GetTickCount64();
		return 0;
	}

	void ServerKernel::update()
	{
		auto time = GetTickCount64();
		if (time - m_uTickTime > 20 * 1000) {
			m_bRunning = false;
			std::cout << "[ServerKernel][Update Error]: Listen Out Of Time." << std::endl;
			closesocket(m_ListenSocket);
			WSACleanup();
		}

		// 接受链接
		SOCKADDR_IN sockClient;
		int nLen = sizeof(sockClient);
		SOCKET socketClient = accept(m_ListenSocket, (struct sockaddr*)&sockClient, &nLen);
		if (INVALID_SOCKET == socketClient)
		{
			std::cout << "[ServerKernel][Update Error]: 接受链接失败 error:" << WSAGetLastError() << std::endl;
			closesocket(m_ListenSocket);
			WSACleanup();
		}
		std::cout << "[ServerKernel]: 客户端连接成功" << std::endl;
		std::cout << "[ServerKernel]: 客户端地址: " << sockClient.sin_addr.s_addr << "端口号: " << sockClient.sin_port << std::endl;
	}

	int ServerKernel::isRunning()
	{
		return m_bRunning;
	}

	int ServerKernel::GetErrorCode()
	{
		return 0;
	}
}