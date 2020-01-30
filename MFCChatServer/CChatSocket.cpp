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
	//1.�������ݵ�szRecvBuff
	TRACE("####server OnReceive");
	//CMFCChatServerApp* dlg = (CMFCChatServerApp*)AfxGetApp()->GetMainWnd();
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuff[SEND_MAX_BUFF] = {0};
	Receive(szRecvBuff, SEND_MAX_BUFF, 0);
	TRACE("####Server szRecvBuff",szRecvBuff);

	//2.��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuff);
	//3��ʾ���б��
	/*CString strShow = _T("�ͻ���");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	strShow = strTime + _T(":") + strShow;
	strShow += strRecvMsg;*/

	CString strShow;
	CString strInfo = _T("�ͻ���: ");
	//CString strMsg = _T("��������");

	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);


}
