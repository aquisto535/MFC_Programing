
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "simple.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{	
	//확장 메타파일 객체를 생성하고 초기화한다.
	CMetaFileDC dc;
	dc.CreateEnhanced(NULL, NULL, NULL, NULL);

	//멤버함수를 호출하여 출력한다.
	dc.Rectangle(0, 0, 10, 10);
	dc.Ellipse(1, 1, 9, 9);

	//확장 메타파일 핸들을 얻는다.
	m_hmf = dc.CloseEnhanced();
}

CChildView::~CChildView()
{
	//확장 메타 파일을 삭제한다.
	::DeleteEnhMetaFile(m_hmf);
}

CWnd	m_wndChild;

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
//	ON_WM_NCPAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.

	
	/* 다양한 색상 표시 코드
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			dc.SetPixel(x, y, RGB(x, y, 0));*/

	//클라이언트 영역의 좌표를 얻는다.
	//CRect rect;
	//GetClientRect(&rect);

	////수평선과 수직선을 그린다.
	//dc.MoveTo(0, rect.bottom / 2);
	//dc.LineTo(rect.right, rect.bottom / 2);
	//dc.MoveTo(rect.right / 2, 0);
	//dc.LineTo(rect.right / 2, rect.bottom);



	////마름모꼴을 그린다.
	//POINT points[] = { {rect.right / 2, 0}, {rect.right, rect.bottom / 2}, {rect.right / 2, rect.bottom }, {0, rect.bottom / 2}, {rect.right / 2, 0} };

	//dc.Polyline(points, 5);

	//dc.SetTextColor(RGB(255, 0, 0));// 글자를 빨강색으로 설정
	//dc.SetBkColor(RGB(255, 255, 0));// 배경을 노란색으로 설정
	//dc.DrawText(CString("DrawText 함수를 연습합니다.[1]"), &rect, 0);
	//dc.DrawText(CString("DrawText 함수를 연습합니다.[2]"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//dc.SetTextAlign(TA_CENTER); // 가운데 정렬 방식으로 변경
	//dc.SetTextColor(RGB(0, 0, 255)); // 글자를 파란색으로 설정
	//dc.SetBkColor(RGB(0, 255, 0)); // 배경을 초록색으로 설정
	//dc.TextOut(rect.right / 2, 3 * rect.bottom / 4, CString("textout 함수를 연습합니다."));

	//dc.SetMapMode(MM_LOMETRIC); // 매핑모드 변경
	//dc.Rectangle(0, 0, 1000, -300);
	//dc.SetMapMode(MM_HIMETRIC); // 매핑모드 변경
	//dc.Ellipse(0, 0, 10000, -3000);

	/*dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(100, 100);
	dc.SetViewportExt(rect.Width(), rect.Height());
	dc.RoundRect(0, 0, 100, 100, 50, 50);
	dc.DrawEdge(CRect(20, 20, 80, 80), BDR_SUNKENINNER | BDR_RAISEDOUTER, BF_RECT);*/

	//dc.SetBkMode(OPAQUE);
	//dc.TextOut(100, 50, CString("OPAQUE 모드 [1]"));

	//dc.SetBkMode(TRANSPARENT);
	//dc.TextOutW(100, 100, CString("TRANSPARENT 모드 [2]"));

	//dc.SetBkMode(OPAQUE);
	//dc.SetBkColor(RGB(0, 255, 0));
	//dc.TextOutW(100, 150, CString("OPAQUE 모드 [2]"));



	//다양한 펜 종류를 연습한다.
	//int nPenStyle[] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT,PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME };

	//TCHAR* PenStyle[] = { _T("PS_SOLID"),_T("PS_DASH"),_T("PS_DOT"),_T("PS_DASHDOT"),_T("PS_DASHDOTDOT"),_T("PS_NULL"),_T("PS_INSIDEFRAME")};

	//dc.SetTextAlign(TA_BASELINE);

	//for (int i = 0; i < sizeof(nPenStyle) / sizeof(nPenStyle[0]); i++)
	//{
	//	CPen pen(nPenStyle[i], 1, RGB(0, 0, 255));
	//	dc.SelectObject(&pen);
	//	dc.TextOutW(50, 25 + i * 25, PenStyle[i], lstrlen(PenStyle[i]));
	//	dc.MoveTo(200, 25 + i * 25);
	//	dc.LineTo(500, 25 + i * 25);
	//}

	//CPen blackpen(PS_SOLID, 1, RGB(0, 0, 0));//폭 1, 검은색 PS_SOILD 펜

	//dc.SelectObject(&blackpen);
	//dc.Rectangle(50, 200, 150, 300); // 폭과 높이가 100인 직사각형
	//CPen pen1(PS_SOLID, 20, RGB(255, 0, 0));// 폭 20, 빨간색 PS_SOILD 펜
	//dc.SelectObject(&pen1);
	//dc.Ellipse(50, 200, 150, 300); //지름이100인 원

	//dc.SelectObject(&blackpen);
	//dc.Rectangle(250, 200, 350, 300); // 폭과 높이가 100인 직사각형
	//CPen pen2(PS_INSIDEFRAME, 20, RGB(255, 0, 0)); // 폭 20, 빨간색 PS_SOILD 펜
	//dc.SelectObject(&pen2);
	//dc.Ellipse(250, 200, 350, 300); // 지름이 100인 원


	//브러시 사용
	//CBrush brush1(RGB(255, 0, 0));
	//dc.SelectObject(&brush1);
	//dc.Rectangle(50, 50, 200, 200);


	//CBrush brush2(HS_DIAGCROSS, RGB(255, 0, 0));
	//dc.SelectObject(&brush2);
	//dc.Ellipse(250, 50, 400, 200);

	//CFont font;

	//font.CreatePointFont(400, _T("Arial"));
	//dc.SelectObject(&font);
	//dc.TextOutW(10, 10, CString("HELLO"));

	//클라이언트 영역을 초록색 해치 브러시로 채운다.
	//CRect rect;
	//GetClientRect(&rect);
	//CBrush brush(HS_CROSS, RGB(0, 255, 0));
	//dc.SelectObject(&brush);
	//dc.Rectangle(&rect);

	////경계선이 검은색이고 내부가 비어있는 타원을 그린다.
	//dc.SelectStockObject(BLACK_PEN);
	//dc.SelectStockObject(NULL_BRUSH);
	//dc.Ellipse(100, 50, 200, 200);

	////경계선이 없고 내부가 밝은 회색으로 채워진 다각형을 그린다.
	//dc.SelectStockObject(NULL_PEN);
	//dc.SelectStockObject(LTGRAY_BRUSH);
	//POINT points[] = { {250, 50}, {450,150}, {300,200}, {250, 150} };
	//dc.Polygon(points, 4);


}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	//m_wndChild.Create(_T("BUTTON"), _T("DEMO"),

	//	WS_CHILD | WS_VISIBLE | WS_BORDER,
	//	CRect(0, 0, 180, 180),this, 1234); 

	return 0;
}


void CChildView::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	

	CWnd::OnClose();
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);

	CRect rect(point.x - 20, point.y - 20, point.x + 20, point.y + 20);

	dc.PlayMetaFile(m_hmf, &rect);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);

	CRect rect(point.x - 20, point.y - 20, point.x + 50, point.y + 20);

	dc.PlayMetaFile(m_hmf, &rect);
}


//void CChildView::OnNcPaint()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	// 그리기 메시지에 대해서는 CWnd::OnNcPaint()을(를) 호출하지 마십시오.
//
//	wnd::
//
//
//}
