#pragma once
#include<afxsock.h>
class CSererSocket :
	public CAsyncSocket
{
public:
	CSererSocket();
	virtual	~CSererSocket();
	virtual	void OnAccept(int nErrorCode);
};

