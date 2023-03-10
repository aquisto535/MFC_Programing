
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GDI_Basic.h"
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
	ON_WM_LBUTTONDOWN()
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.dc()는 dc가 어느 위치에서 호출되는지 알려주는 역할을 한다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.

	//CDC* pDC = GetDC(); 동적 생성

	//CPen NewPen(PS_SOLID, 3, RGB(192, 0, 0));
	//CPen* pOldPen = dc.SelectObject(&NewPen); //dc가 내가 정한 펜을 선택하도록 설정한 펜의 주소를 기존 펜의 값에 대입.
	//CBrush NewBrush(RGB(192, 192,192));
	//CBrush *pOldBrush = dc.SelectObject(&NewBrush);

	//dc.Rectangle(10,10,110,110);

	//dc.SelectObject(pOldPen);//지금까지 그린 직사각형 대상을 반환. dc.SelectObject()는 반드시 본래의 객체에 대한 주소를 리턴한다.
	//dc.SelectObject(pOldBrush);

	//dc.Rectangle(10, 10, 110, 110);

	//ReleaseDC(pDC); 동적 생성 후 해제

/*	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(192,0 , 0);
	DWORD style[] = { 1,1 };*/ // 픽셀의 길이, 빈 공간의 길이(lpStyle). 배열의 선언방식으로 지정.
/*
	CPen NewPen;
	NewPen.CreatePen( PS_USERSTYLE | PS_GEOMETRIC | PS_ENDCAP_FLAT, 1, &lb, 2, style);*/// nStyleCount= 항의 갯수. lpStyle은 이중 단어 값 배열을 가리킵니다. 첫 번째 값은 사용자 정의 스타일에서 첫 번째 대시의 길이를 지정하고, 두 번째 값은 첫 번째 공간의 길이 등을 지정합니다.이 포인터는 NULL 그렇지 않은 PS_USERSTYLE경우 nPenStyle 여야 합니다.

	//CPen NewPen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_FLAT , 10(두께),  &lb);// 미리 지정된 속성값을 또 대입하면 오류가 날 수 있다!! ex) RGB(192, 192, 192) 중복 대입.
	//CPen* pOldPen = dc.SelectObject(&NewPen);  
	//CBrush NewBrush(HS_CROSS ,RGB(0, 192, 0));
	//CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	//dc.FillSolidRect(20,20, 100, 100, RGB(0,0,0));//사각형을 단색으로 채웁니다.펜을 사용하지 않고도 도형을 그릴 수 있음.
	//dc.SetBkMode(TRANSPARENT);
	//dc.Rectangle(20, 20, 120, 120);

	//for (int i = 0; i < 10; i++) //반복문을 통해 화면 전체를 그릴 수도 있다!!
	//{
	//	dc.MoveTo(40, 12* i + 40);
	//	dc.LineTo(240, 12 * i + 40);

	//}

	CBrush NewBrush;
	CBitmap Bmp;
	Bmp.LoadBitmap(IDB_BITMAP1);
	NewBrush.CreatePatternBrush(&Bmp);
	CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	CRect Rect; 
	GetClientRect(&Rect);
	dc.Rectangle(&Rect);

	//dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,255));
	dc.TextOutW(100, 100, _T("TEST STRING"));

	//dc.MoveTo(40, 40);//본래 속성으로 돌아감
	//dc.LineTo(240, 40);//본래 속성으로 돌아감
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CDC* pDC = GetDC();
	//pDC->Rectangle(10,10,110,110);
	//ReleaseDC(pDC);

	CWnd::OnLButtonDown(nFlags, point);
}
