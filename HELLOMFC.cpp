#include<afxwin.h>

//�������α׷� Ŭ���� ����
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();//���� �Լ��� ����

};

// ���� ������ Ŭ���� ����
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};

// ���� ���α׷� ��ü ����.�Լ� �ܵ� ����� ������ ����. ex) RunByFrame()�� ������ �����. �̷��� ���� ��ü�� 1���� �����ؾ� ��!! 
CHelloApp theApp;

//���� ���α׷� Ŭ���� ����
BOOL CHelloApp::InitInstance() {
	m_pMainWnd = new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}
 
//���� ������ Ŭ���� ����
CMainFrame::CMainFrame()
{
	Create(NULL, _T("HELLOMFC"));
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	const TCHAR* msg = _T("Hello, MFC");
	dc.TextOutW(100, 100, msg, lstrlen(msg));
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MessageBox(_T("���콺 Ŭ��!"), _T("���콺 �޼���"));
}

//�޼��� �� ����
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT() 
	ON_WM_LBUTTONDOWN()

END_MESSAGE_MAP()