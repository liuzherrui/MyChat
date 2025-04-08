#pragma once
#include <WinSock2.h>


#pragma comment(lib,"ws2_32.lib")

namespace MyChat
{
	class ServerKernel {
	public:
		ServerKernel();
		~ServerKernel();

	public:
		int init();
		int start();
		void update();
		int isRunning();

		int GetErrorCode();

	private:
		SOCKET m_ListenSocket;
		SOCKADDR_IN m_SocketAddr_Info;

		bool m_bRunning = false;
		unsigned __int64 m_uTickTime = -1;

	};
}