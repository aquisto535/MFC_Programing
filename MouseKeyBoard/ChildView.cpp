
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
	m_ptItemText = CPoint(10, 30);
	m_bDragFlag = FALSE;
	m_bDrawMode = FALSE;
	m_bMouseIn = FALSE;
	m_xPos = 60; // 임의값으로 초기화
	m_yPos = 60; // 임의값으로 초기화
	m_bFill = FALSE; // 도형 내부를 채우지 않음
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
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHWHEEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSELEAVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
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

	/*CString strTmp = _T("");
	strTmp.Format(_T("%03d, %03d"), m_ptMouse.x, m_ptMouse.y);
	dc.TextOut(10, 10, strTmp);*/

	//드래그 이벤트 구현방법 시연
	if (m_bDragFlag)
		dc.TextOutW(10, 10, _T("DRAG"));
	else
		dc.TextOutW(10, 10, _T("----"));

	dc.TextOutW(m_ptItemText.x, m_ptItemText.y, _T("내 컴퓨터야!"));

	dc.SelectStockObject(LTGRAY_BRUSH);
	dc.Ellipse(10, 10, 400, 100);

	if (m_bFill == TRUE)
	{
		dc.SelectStockObject(BLACK_BRUSH);
	}

	dc.Ellipse(m_xPos - 20, m_yPos - 20, m_xPos + 20, m_yPos + 20);

	// 화면 출력용 폰트를 선택한다.
	CFont font;
	font.CreatePointFont(150, _T("궁서"));
	dc.SelectObject(&font);

	// 현재까지 입력된 글자들을 화면에 출력한다.
	CRect rect;
	GetClientRect(&rect);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &rect, DT_LEFT);

}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	//m_wndchild.Create(_T("STATIC"), _T("KeyMove"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(100, 100, 200, 200), this, 1234);

	m_wndTrack.Create(_T("STATIC"), _T("KeyMove"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_NOTIFY, CRect(100, 10, 250, 160), this, 1234);

	return 0;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);

	CPoint ptChild; // 차일드 윈도우의 좌표
	CRect Rect; // 차일드 윈도우의 좌표 및 크기
	CPaintDC dc(this);

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

	switch (nChar)
	{
	case VK_LEFT :
		m_xPos -= 20;
		break;
	case VK_RIGHT:
		m_xPos += 20;
		break;
	case VK_UP:
		m_yPos -= 20;
		break;
	case VK_DOWN:
		m_yPos += 20;
		break;
	case VK_SPACE:
		m_bFill = !m_bFill;
	}

	m_xPos = min(max(20, m_xPos), m_xMax - 20);
	m_yPos = min(max(20, m_yPos), m_yMax - 20);
	Invalidate();
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CString strTmp = _T("");
	strTmp.Format(_T("%c"), nChar);
	m_wndchild.SetWindowText(strTmp);


	if (nChar == _T('\b'))
	{
		if (m_str.GetSize() > 0)
			m_str.RemoveAt(m_str.GetSize()-1);
	}
	else
	{
		m_str.Add(nChar);
	}

	Invalidate();

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


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//그리기 모드이면 타원을 지우고 그리기를 반복한다.
	if (m_bDrawMode) 
	{
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		//이전에 그린 타원을 지운다
		dc.SetROP2(R2_NOT);
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
		//새로운 타원을 그린다.
		dc.SetROP2(R2_NOT);
		m_x2 = point.x;
		m_y2 = point.y;
		dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}

	//m_ptMouse = point; 
	//Cchildview 클래스에서 미리 선언한 객체 사용
	if (m_bDragFlag)
	{
		m_ptItemText = point;
		if (m_ptItemText.x < 0)	m_ptItemText.x = 0;
		RedrawWindow();
	}

	if (m_bMouseIn == FALSE)
	{	
		// 마우스 커서 추적을 요청한다.
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;
		::TrackMouseEvent(&tme);
	}

	// 메인 윈도우 크기를 300*150으로 변경한다.

	CWnd* pMainWnd = AfxGetMainWnd();
	CRect rect;
	pMainWnd->GetWindowRect(&rect);
	rect.right = rect.left + 300;
	rect.bottom = rect.top + 150;
	pMainWnd->MoveWindow(&rect);

	// 마우스 커서가 클라이언트 영역에 있음을 기억해둔다.
	m_bMouseIn = TRUE;

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CString strTmp = _T("");
	//strTmp.Format(TEXT("OnMouseWheel() zDelta : %\n"), zDelta);
	//TRACE(strTmp);

	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//AfxMessageBox(_T("TEST"));

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//클릭할 때마다 직사각형 그리기
	//CClientDC dc(this);
	//dc.SetMapMode(MM_LOMETRIC);
	//CPoint pt = point;
	//dc.DPtoLP(&pt);
	//dc.Rectangle(pt.x - 100, pt.y + 100, pt.x + 100, pt.y - 100);

	//if (point.x >= m_ptItemText.x && point.x <= m_ptItemText.x + 16 && point.y - 16 && point.y <= m_ptItemText.y + 16)
	//{
	//	m_bDragFlag = true;
	//	RedrawWindow();
	//	SetCapture();
	//}

	//if (nFlags & MK_SHIFT)
	//{
	//	AfxMessageBox(_T("TEST"));
	//}

	//그리기 모드를 시작한다.
	m_bDrawMode = TRUE;
	
	//좌표를 저장한다.
	m_x1 = m_x2 = point.x;
	m_y1 = m_y2 = point.y;

	SetCapture();

	

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bDragFlag)
	{
		m_bDragFlag = false;
		m_ptItemText = point;
		RedrawWindow();
		ReleaseCapture();
	}

	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);

	//최종적인 타원을 그린다.
	dc.SetROP2(R2_COPYPEN);
	m_x2 = point.x;
	m_y2 = point.y;
	dc.Ellipse(m_x1, m_y1, m_x2, m_y2);

	//그리기 모드를 끝낸다.
	m_bDrawMode = FALSE;

	::ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 클라이언트 영역이면 커서를 변경한다.
	if (nHitTest == HTCLIENT)
	{
		CPoint point;
		::GetCursorPos(&point); // 커서 위치(스크린 좌표)를 얻는다.
		ScreenToClient(&point); // 스크린 좌표를 클라이언트 좌표로 변환한다.
		CRgn rgn;
		rgn.CreateEllipticRgn(10, 10, 400, 100); // 타원형 리전을 생성한다.
		if (rgn.PtInRegion(point)) // 커서가 리전 안쪽에 있는지 확인한다.
			//사용자 정의 커서로 변경한다.
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
		else
		{
			//표준커서 중 하나로 변경한다.
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		}
	}

	//클라이언트 영역이 아니면 운영체제가 자동으로 처리한다.
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CChildView::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//마우스 커서가 클라이언트 영역 밖에 있음을 기억해둔다.
	m_bMouseIn = FALSE;

	//메인 윈도우 크기를 200*100으로 변경한다.
	CWnd* pMainWnd = AfxGetMainWnd();
	CRect rect;
	pMainWnd->GetWindowRect(&rect);
	rect.right = rect.left + 200;
	rect.bottom = rect.top + 100;
	pMainWnd->MoveWindow(&rect);

	CWnd::OnMouseLeave();
}


void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CreateSolidCaret(20, 20); // 캐럿(네모)을 생성한다.
	SetCaretPos(CPoint(50, 50));// 캐럿의 위치를 설정한다.
	ShowCaret(); // 캐럿을 화면에 보인다.
}


void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	HideCaret(); // 캐럿을 숨긴다.
	::DestroyCaret; // 캐럿을 파괴한다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	m_xMax = cx;
	m_yMax = cy;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
