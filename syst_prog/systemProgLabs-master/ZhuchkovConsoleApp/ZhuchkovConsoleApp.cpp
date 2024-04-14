// ZhuchkovConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "ZhuchkovConsoleApp.h"
#include "Session.h"
#include "Message.h"
#include "SafeWriting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;




struct header
{
	int addr;
	int size;
};
__declspec(dllimport) std::string getMessage(header& h);




DWORD WINAPI workFunc(LPVOID _param)
{
	auto session = static_cast<Session*>(_param);
	SafeWrite("session", session->sessionID, "created");
	while (true)
	{
		Message m;
		if (session->getMessage(m))
		{
			switch (m.header.messageType)
			{
			case MT_CLOSE:
			{
				SafeWrite("session", session->sessionID, "closed");
				delete session;
				return 0;
			}
			case MT_DATA:
			{
				SafeWrite("session", session->sessionID, "data", m.data);
				break;
			}
			}
		}
	}
	return 0;
}



void start()
{
	HANDLE confirmEvent = ::CreateEvent(NULL, FALSE, FALSE, "ConfirmEvent");
	HANDLE startEvent = ::CreateEvent(NULL, FALSE, FALSE, "StartEvent");
	HANDLE stopEvent = ::CreateEvent(NULL, FALSE, FALSE, "CloseProcZhuchkov");
	HANDLE exitEvent = ::CreateEvent(NULL, FALSE, FALSE, "ExitProcZhuchkov");
	HANDLE sendEvent = ::CreateEvent(NULL, FALSE, FALSE, "SendEvent");

	HANDLE events[4];
	events[0] = startEvent;
	events[1] = stopEvent;
	events[2] = exitEvent;
	events[3] = sendEvent;


	std::vector<HANDLE> hThreads;
	std::vector<Session*> sessions;

	while (true)
	{
		DWORD dwWaitRes = ::WaitForMultipleObjects(sizeof(events) / sizeof(HANDLE), events, FALSE, INFINITE);

		switch (dwWaitRes)
		{
		case WAIT_OBJECT_0:
			sessions.push_back(new Session(hThreads.size() + 1));

			hThreads.push_back(AfxBeginThread((AFX_THREADPROC)workFunc, (LPVOID)sessions.back(), THREAD_PRIORITY_HIGHEST));
			break;

		case WAIT_OBJECT_0 + 1:

			if (!hThreads.size())
			{
				::SetEvent(confirmEvent);
				return;
			}
			sessions.back()->addMessage(MT_CLOSE);
			sessions.pop_back();

			::CloseHandle(hThreads.back());
			hThreads.pop_back();

			break;

		case WAIT_OBJECT_0 + 2:

			for (int i{ 0 }; i < sessions.size(); ++i)
			{
				sessions[i]->addMessage(MT_CLOSE);
				::CloseHandle(hThreads[i]);
			}
			SetEvent(confirmEvent);
			return;

		case WAIT_OBJECT_0 + 3:
		{

			header h;
			std::string message = getMessage(h);

			if (h.addr == -1)
			{
				SafeWrite("Main received data: ", message);
				std::for_each(sessions.begin(), sessions.end(), [&message](Session* s) {s->addMessage(MT_DATA, message); });
			}
			else if (h.addr == 0)
			{
				SafeWrite("Main received data: ", message);
			}
			else
				for (Session* s : sessions)
				{
					if (s->sessionID == h.addr)
					{
						s->addMessage(MT_DATA, message);
						break;
					}
				}
			break;
		}
		default:

			std::cout << "There was an error" << std::endl;
			return ;
		}
		::SetEvent(confirmEvent);
	}

	WaitForMultipleObjects((DWORD)hThreads.size(), hThreads.data(), TRUE, INFINITE);

	CloseHandle(confirmEvent);
	CloseHandle(startEvent);
	CloseHandle(stopEvent);
	CloseHandle(sendEvent);
}


int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {

        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
			start();
        }
    }
    else
    {
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
