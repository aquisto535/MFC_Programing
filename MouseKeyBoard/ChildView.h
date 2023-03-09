
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "CtrackWnd.h"


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	int m_xPos{}, m_yPos{}; //도형의 현재 위치
	int m_xMax{}, m_yMax{}; // 클라이언트 영역의 크기
	BOOL m_bFill{}; // 도형의 내부를 채울지 여부
	CArray<TCHAR, TCHAR> m_str;

// 작업입니다.
public:
	//쓰고 싶은 클래스나 변수를 여기에서 앞서 선언.
	CWnd m_wndchild;
	CPoint m_ptMouse;
	CPoint m_ptItemText;
	BOOL   m_bDragFlag;
	BOOL m_bMouseIn;
	CtrackWnd m_wndTrack;
	BOOL m_bDrawMode; // 그리기 작업이 진행 중임을 나타낸다
	int m_x1, m_y1, m_x2, m_y2; // 타원에 외접하는 직사각형의 좌상단/우상단 좌표


// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseLeave();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

