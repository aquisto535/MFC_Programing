
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "BitMap2.h"
#include "ChildView.h"
#include <atlimage.h>

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

	CDC MemDC;//메모리 DC: 윈도우 없이 DC만 있음. CPaintDC dc와 반대.
	BITMAP bmpInfo; // 화면 DC와 호환되는 메모리 DC를 생성한다.

	//직접 비트맵 출력(전통적 방법)
	MemDC.CreateCompatibleDC(&dc); 
	// 비트맵 리소스를 로딩한다.
	CBitmap bmp; 
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(IDB_BITMAP1);
	// 로딩된 비트맵의 정보를 알아본다.
	bmp.GetBitmap(&bmpInfo);
	// 메모리 DC에 선택한다.
	pOldBmp = MemDC.SelectObject(&bmp);
	//메모리 DC에 들어있는 비트맵을 화면 DC로 복사하여 출력한다. 
	//dc.BitBlt(0, 0, bmpInfo, bmpWidth, &MemDC, 0(대상의 시작 x좌표. 원하는 위치에 일부 출력 가능), 0(대상의 시작 y좌표), SRCCOPY);
	//dc.FillSolidRect(10,10,100,100,RGB(192,192,192)); 사각형을 단색으로 채웁니다

	//dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);

	//dc.StretchBlt(200, 200, 250 * 2, 300 * 2, &MemDC, 350, 200, 250, 300, SRCCOPY); // 메모리 dc의 이미지를 두 배 확대하여 출력한다.
	//dc.TransparentBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, 0, 0, RGB(255,0,0));
	
	//마지막 인자를 제외하면 StretchBlt과 거의 동일
	//BLENDFUNCTION bf;
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.SourceConstantAlpha = 100;
	//bf.AlphaFormat = 0;

	////반투명 이미지를 출력한다.
	//dc.AlphaBlend(20, 100, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, bmpInfo.bmWidth ,bmpInfo.bmHeight, bf);
	//
	//MemDC.SelectObject(pOldBmp);

	//CImage를 활용한 비트맵 출력
	CImage Image;
	CString strImagePath = _T("45908.jpg");

	HRESULT hResult = Image.Load(strImagePath);

	if (FAILED(hResult))
	{
		CString strtmp = _T("ERROR: Failed to Load");
		strtmp += strImagePath + _T("\n");
		TRACE(strtmp);
		return;
	}

	Image.BitBlt(dc.m_hDC, 0, 0);
}

