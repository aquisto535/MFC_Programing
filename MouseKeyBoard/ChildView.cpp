
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MouseKeyBoard.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	m_wndchild.Create(_T("STATIC"), _T("KeyMove"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(100, 100, 200, 200), this, 1234);

	return 0;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);

	CPoint ptChild; // 차일드 윈도우의 좌표
	CRect Rect; // 차일드 윈도우의 좌표 및 크기

	//차일드 윈도우의 두 좌표 정보(스크린 기준)를 알아온다.
	m_wndchild.GetWindowRect(&Rect); //현재 차일드윈도우가 위치한 오른쪽 상단, 왼쪽 상단 좌표를 저장해줌.
	ptChild.x = Rect.left; 
	ptChild.y = Rect.top; 

	//스크린 기준 좌표를 클라이언트 뷰 기준의 좌표로 환산한다.
	ScreenToClient(&ptChild);

	switch (nChar)
	{

	//왼쪽 화살표를 누른 경우 10픽셀만큼 x좌표 값 감소.
	case VK_LEFT:
		ptChild.x -= 10;
		break;
	
	//오른쪽 화살표를 누른 경우 10픽셀만큼 x좌표 값 증가.
	case VK_RIGHT:
		ptChild.x += 10;
		break;
	}

	//변경된 새 좌표로 차일드 윈도우를 이동시킨다.
	m_wndchild.SetWindowPos(&CWnd::wndTop, ptChild.x, ptChild.y, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CString strTmp = _T("");
	strTmp.Format(_T("%c"), nChar);
	m_wndchild.SetWindowText(strTmp);

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

//사용자가 시스템키(Alt 키)를 누른 다음 다른 키를 누르면 프레임워크에서 멤버 함수가 호출됩니다.
void CChildView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CString strMesssage = TEXT("");

	WORD WResult = ::GetKeyState(VK_SPACE);
	BYTE byhigh = HIBYTE(WResult);

	if (byhigh & 0x01)
	{
		strMesssage += TEXT("Alt + Space, ");
		WResult = ::GetKeyState(VK_CAPITAL);

		BYTE byLow = LOBYTE(WResult);
		if (byLow & 0x01) strMesssage += TEXT("CAPS LOCK ON");
		else			  strMesssage += TEXT("CAP LOCK OFF");
		
		AfxMessageBox(strMesssage);
		
	}


	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
