#include "pch.h"
#include "CtrackWnd.h"
BEGIN_MESSAGE_MAP(CtrackWnd, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CtrackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	SetWindowText(_T("TRACK TEST"));
	m_bTrack = false;

	CWnd::OnMouseLeave();
}
