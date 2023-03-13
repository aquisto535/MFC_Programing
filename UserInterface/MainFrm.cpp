
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "UserInterface.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SYSCOMMAND()
	//ON_UPDATE_COMMAND_UI(ID_INDICATOR_POS, OnUpdatePos);
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,	
	//ID_INDICATOR_POS,
	ID_INDICATOR_SCRL,
};

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
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}

	// 툴바 생성하는 코드
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//CMenu menuMain; // 메뉴 객체 생성
	//menuMain.CreateMenu(); // 최상위 메뉴 생성

	//CMenu menuPopUp; // 메뉴 객체 생성
	//menuPopUp.CreateMenu(); // 메뉴 객체 생성

	// 팝업 메뉴에 메뉴 항목 세 개 추가
	//menuPopUp.AppendMenuW(MF_STRING, 201, _T("빨간색(&R)")); 
	//menuPopUp.AppendMenuW(MF_STRING, 202, _T("초록색(&R)"));
	//menuPopUp.AppendMenuW(MF_STRING, 203, _T("파란색(&R)"));

	//최상위 메뉴에 팝업 메뉴 추가
	//menuMain.AppendMenuW(MF_POPUP, (UINT)menuPopUp.Detach(), _T("색상(&C)"));

	//SetMenu(&menuMain); // 메뉴를 윈도우에 붙임
	//menuMain.Detach();  // 메뉴 객체와 메뉴를 분리


	// (1) '항목2'의 하위 메뉴를 생성한다.
	CMenu popUp1; // 메뉴 객체 생성
	popUp1.CreatePopupMenu(); // 팝업 메뉴 생성
	popUp1.AppendMenuW(MF_STRING, 301, _T("1"));
	popUp1.AppendMenuW(MF_STRING, 302, _T("2"));
	popUp1.AppendMenuW(MF_STRING, 303, _T("3"));
	popUp1.AppendMenuW(MF_STRING, 304, _T("4"));

	// (2) '테스트'메뉴를 생성한다.
	CMenu popUp2; // 메뉴 객체 생성
	popUp2.CreatePopupMenu(); // 팝업 메뉴 생성
	popUp2.AppendMenuW(MF_STRING | MF_CHECKED, 201, _T("항목&1"));
	popUp2.AppendMenuW(MF_STRING , (UINT)popUp1.Detach(), _T("항목&2"));
	popUp2.AppendMenuW(MF_STRING, 203, _T("항목&3"));

	// '테스트' 메뉴를 최상위 메뉴에 붙인다.
	CMenu* pTopLevel = GetMenu(); // 포인터로 최상위 메뉴의 값을 가져옴.
	pTopLevel->AppendMenuW(MF_POPUP, (UINT)popUp2.Detach(), _T("테스트(&T)"));

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	// '닫기' 메뉴 항목을 비활성화한다.
	pSysMenu->EnableMenuItem(SC_CLOSE, MF_GRAYED);
	// 분리자(separator)
	pSysMenu->AppendMenuW(MF_SEPARATOR);
	// ID가 16인 메뉴 항목을 추가한다.
	pSysMenu->AppendMenuW(MF_STRING, 16, _T("이 프로그램은..."));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
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


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	if ((nID & 0xFFF0) == 16)
	{
		MessageBox(_T("시스템 메뉴를 테스트합니다."), _T("이 프로그램은..."));

		return;
	}

	CFrameWnd::OnSysCommand(nID, lParam);
}


void CMainFrame::OnUpdatePos(CCmdUI* pCmdUI)
{
	// TODO: 여기에 구현 코드 추가.

	pCmdUI->Enable();
}
