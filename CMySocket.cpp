#include "pch.h"
#include "CMySocket.h"
#include "MFCCHatClicent.h"
#include "MFCCHatClicentDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	CMFCCHatClicentDlg* dlg = (CMFCCHatClicentDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("与服务器链接成功");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnSend(nErrorCode);
}
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####OnReceive");
}
