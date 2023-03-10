
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GDI_도형.h"
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

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 30;
	wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));

	CFont NewFont;
	NewFont.CreateFontIndirectW(&lf);
	CFont* pOldFont = dc.SelectObject(&NewFont);

	//dc.TextOutW(10, 10, _T("Test String!!"));
	//dc.TextOutW(10, 50, _T("테스트 문자열입니다."));
	
	int arnTabStop[2] = {10,40};
	CSize size = dc.TabbedTextOutW(10,10, _T("\t\t테스트 문자열입니다."), 2, arnTabStop,10);// 탭 구현하는 코드. 다채로운 색깔을 구현하려면 TabbedTextOutW을 써야 한다!!

	dc.SelectObject(pOldFont);//마지막에 출력해주어야 함.
	//CRect Rect;
	//GetClientRect(&Rect);

	//dc.FillSolidRect(&Rect, RGB(0, 0, 255));

	//CPen NewPen(PS_SOLID, 1, RGB(0,0,0));
	//CPen* pOldPen = dc.SelectObject(&NewPen);
	//
	//Rect -= CRect(10,10,10,10);
	//dc.RoundRect(Rect, CPoint(30, 30)); //Rect를 넣어도 됨.
	//dc.SelectObject(pOldPen);
	
	//CBrush* pOldBrush = dc.SelectObject(&NewBrush); 

	//dc.Rectangle(20, 20, 140, 140);
	//dc.Ellipse(20, 20, 140, 140);

	//dc.BeginPath();// 삼각형 그릴 때 무조건 있어야함! 단순히 선만 긋는다고 삼각형이 되는 것이 아니다!! 두깨가 20픽셀인 선을 세 번 그어 삼각형을 만든다.//사각형도 비슷하다.
	//dc.MoveTo(20, 20);
	//dc.LineTo(140, 20);
	//dc.LineTo(140, 140);
	//dc.LineTo(20, 140);
	//dc.LineTo(20, 20);
	//dc.EndPath();// 삼각형 그릴 때 무조건 있어야함!
	//dc.StrokeAndFillPath();// 삼각형 그릴 때 무조건 있어야함! 자동으로 렌더링해줌!!

	//삼각형 그리는 다른 방법
	//POINT arPt[3] = { {190,43}, {290,190}, {90, 190} };
	//dc.Polygon(arPt, 3);

	//dc.SelectObject(pOldBrush); //브러시
	//dc.SelectObject(pOldPen); //펜

	//기본 펜으로 삼각형을 겹쳐 그린다.
	//dc.MoveTo(20, 20);
	//dc.LineTo(140, 20);
	//dc.LineTo(140, 140);
	//dc.LineTo(20, 140);
	//dc.LineTo(20, 20);
}

