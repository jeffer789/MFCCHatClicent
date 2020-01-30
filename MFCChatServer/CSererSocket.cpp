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
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));
	
	/*CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str=dlg->m_tm.Format("%X");
	str += _T("客户端连接成功");*/

	CString strShow;
	CString strInfo = _T("客户端连接成功 ");
	CString strMsg = _T("");

	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);//更新数据

	CAsyncSocket::OnAccept(nErrorCode);//调用本体


}
