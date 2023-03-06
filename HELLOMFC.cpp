#include<afxwin.h>

//응용프로그램 클래스 선언
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();//메인 함수의 시작

};

// 메인 윈도우 클래스 선언
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};

// 응용 프로그램 객체 선언.함수 단독 실행과 동일한 원리. ex) RunByFrame()과 동일한 방식임. 이러한 전역 객체는 1개만 존재해야 함!! 
CHelloApp theApp;

//응용 프로그램 클래스 정의
BOOL CHelloApp::InitInstance() {
	m_pMainWnd = new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}
 
//메인 윈도우 클래스 정의
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
	MessageBox(_T("마우스 클릭!"), _T("마우스 메세지"));
}

//메세지 맵 선언
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT() 
	ON_WM_LBUTTONDOWN()

END_MESSAGE_MAP()