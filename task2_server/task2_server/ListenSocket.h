#pragma once
#include "afxsock.h"
#include "ServerSocket.h"
class CListenSocket :
	public CSocket
{
public:
	CServerSocket *m_serversocket;
	CListenSocket(void);
	~CListenSocket(void);

public:
	virtual void OnAccept(int nErrorCode);
	
};

