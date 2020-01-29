#include "pch.h"
#include "CSererSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"



CSererSocket::CSererSocket()
{

}

CSererSocket::~CSererSocket()
{

}

void CSererSocket::OnAccept(int nErrorCode)
{
	TRACE("####OnAccept");
	CMFCChatServerApp* dlg = (CMFCChatServerApp*)AfxGetApp()->GetMainWnd();

}
