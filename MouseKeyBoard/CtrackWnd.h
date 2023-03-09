#pragma once
#include <afxwin.h>
class CtrackWnd :
    public CWnd
{
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    
    BOOL m_bTrack{};
    afx_msg void OnMouseLeave();

  
};

