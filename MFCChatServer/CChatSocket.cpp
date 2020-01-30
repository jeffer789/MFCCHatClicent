#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1.接受数据到szRecvBuff
	TRACE("####server OnReceive");
	//CMFCChatServerApp* dlg = (CMFCChatServerApp*)AfxGetApp()->GetMainWnd();
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuff[SEND_MAX_BUFF] = {0};
	Receive(szRecvBuff, SEND_MAX_BUFF, 0);
	TRACE("####Server szRecvBuff",szRecvBuff);

	//2.显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuff);
	//3显示到列表框
	/*CString strShow = _T("客户端");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	strShow = strTime + _T(":") + strShow;
	strShow += strRecvMsg;*/

	CString strShow;
	CString strInfo = _T("客户端: ");
	//CString strMsg = _T("建立服务");

	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);


}
