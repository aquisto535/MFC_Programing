#include "pch.h"
#include "CtrackWnd.h"
BEGIN_MESSAGE_MAP(CtrackWnd, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CtrackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_bTrack)
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = 0;
		m_bTrack = ::_TrackMouseEvent(&tme);

		if(m_bTrack)	SetWindowText(_T("Tracking!"));
	}


	CWnd::OnMouseMove(nFlags, point);
}


void CtrackWnd::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	SetWindowText(_T("TRACK TEST"));
	m_bTrack = false;

	CWnd::OnMouseLeave();
}
