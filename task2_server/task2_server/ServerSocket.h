#pragma once
#include "afxsock.h"
class CServerSocket :
	public CSocket
{
public:
	CServerSocket(void);
	~CServerSocket(void);
	CServerSocket *m_serversocket;
	virtual void OnReceive(int nErrorCode);
};

