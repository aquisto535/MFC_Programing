
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "simple.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

// CMainFrame 생성/소멸


CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	//cs.style = WS_MINIMIZE;
	cs.cx = 1024;
	cs.cy = 768;

	cs.dwExStyle &= ~WS_EX_TOOLWINDOW; //타이틀 내 시스템 메뉴 지정 ex) 닫기 버든, 확대 버튼 등등
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	AfxMessageBox(_T("WM_COLSE 발생"));

	CFrameWnd::OnClose();
}


void CMainFrame::OnPaint()
{	
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFrameWnd::OnPaint()을(를) 호출하지 마십시오.

	 const char* msg = "hello, mfc";

	dc.TextOutW(100, 100, _T("msg"));//인수 목록이 일치하는 오버로드된 함수 오류는 프로젝트 환경이 유니코드 환경이기에 발생하는 에러이기 때문에 _T(" ")를 이용하여 수정해서 사용하면 된다.
	
	
}


void CMainFrame::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CFrameWnd::OnNcPaint()을(를) 호출하지 마십시오.

	//운영체제가 자동으로 비클라이언트 영역을 그리게 한다.
	CFrameWnd::OnNcPaint();


	//타이틀바에 직사각형을 그린다.
	CWindowDC dc(this); //객체 생성 시 대상이 되는 윈도우를 알려줌.

	int height = ::GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYSIZEFRAME);


	//메인(프레임) 윈도우 크기를 얻는다.
	CRect rect;

	GetWindowRect(&rect);

	//타이틀 바에 크기를 출력한다.
	CString str;

	str.Format(_T("Width=%4d, Height=%4d", ), rect.Width(), rect.Height());
	dc.TextOut(160, 7, str);

}
