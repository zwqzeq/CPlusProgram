// exer_9_17Dlg.h : header file
//

#if !defined(AFX_EXER_9_17DLG_H__9F9E1DFC_4A91_4BED_92E6_2C967EA34234__INCLUDED_)
#define AFX_EXER_9_17DLG_H__9F9E1DFC_4A91_4BED_92E6_2C967EA34234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExer_9_17Dlg dialog

class CExer_9_17Dlg : public CDialog
{
// Construction
public:
	COLORREF m_crBrushColor;
	COLORREF m_crPenColor;
	int m_nBrushStyle;
	int m_nPenStyle;
	CExer_9_17Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExer_9_17Dlg)
	enum { IDD = IDD_EXER_9_17_DIALOG };
	CComboBox	m_ComboBrushColor;
	CComboBox	m_ComboPenColor;
	CListBox	m_ListShape;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExer_9_17Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExer_9_17Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadioSolid();
	afx_msg void OnRadioDash();
	afx_msg void OnRadioDot();
	afx_msg void OnRadioDashdot();
	afx_msg void OnRadioSolidbrush();
	afx_msg void OnRadioCross();
	afx_msg void OnRadioFdiagonal();
	afx_msg void OnRadioBdiagonal();
	afx_msg void OnSelendokComboPencolor();
	afx_msg void OnSelendokComboBrushcolor();
	afx_msg void OnBtnDraw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXER_9_17DLG_H__9F9E1DFC_4A91_4BED_92E6_2C967EA34234__INCLUDED_)
