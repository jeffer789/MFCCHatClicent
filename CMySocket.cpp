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
#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("与服务器链接成功");
#endif//这是注释
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("与服务器链接成功");

	strShow=dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnSend(nErrorCode);
}
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####OnReceive");
	CMFCCHatClicentDlg* dlg = (CMFCCHatClicentDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuff[SEND_MAX_BUFF] = { 0 };
	Receive(szRecvBuff, SEND_MAX_BUFF, 0);
	TRACE("####Server szRecvBuff", szRecvBuff);

	//2.显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuff);
	//3显示到列表框
#if 0
	CString strShow = _T("服务端");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	strShow = strTime + _T(":") + strShow;
	strShow += strRecvMsg;
#endif
	CString strShow;
	CString strInfo = _T("服务端:");
	//CString strMsg = _T("与服务器链接成功");

	strShow = dlg->CatShowString(strInfo,strRecvMsg);

	dlg->m_list.AddString(strShow);
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);

}
