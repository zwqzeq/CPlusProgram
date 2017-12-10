// exer_9_17Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "exer_9_17.h"
#include "exer_9_17Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExer_9_17Dlg dialog

CExer_9_17Dlg::CExer_9_17Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExer_9_17Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExer_9_17Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExer_9_17Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExer_9_17Dlg)
	DDX_Control(pDX, IDC_COMBO_BRUSHCOLOR, m_ComboBrushColor);
	DDX_Control(pDX, IDC_COMBO_PENCOLOR, m_ComboPenColor);
	DDX_Control(pDX, IDC_LIST_SHAPE, m_ListShape);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExer_9_17Dlg, CDialog)
	//{{AFX_MSG_MAP(CExer_9_17Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SOLID, OnRadioSolid)
	ON_BN_CLICKED(IDC_RADIO_DASH, OnRadioDash)
	ON_BN_CLICKED(IDC_RADIO_DOT, OnRadioDot)
	ON_BN_CLICKED(IDC_RADIO_DASHDOT, OnRadioDashdot)
	ON_BN_CLICKED(IDC_RADIO_SOLIDBRUSH, OnRadioSolidbrush)
	ON_BN_CLICKED(IDC_RADIO_CROSS, OnRadioCross)
	ON_BN_CLICKED(IDC_RADIO_FDIAGONAL, OnRadioFdiagonal)
	ON_BN_CLICKED(IDC_RADIO_BDIAGONAL, OnRadioBdiagonal)
	ON_CBN_SELENDOK(IDC_COMBO_PENCOLOR, OnSelendokComboPencolor)
	ON_CBN_SELENDOK(IDC_COMBO_BRUSHCOLOR, OnSelendokComboBrushcolor)
	ON_BN_CLICKED(IDC_BTN_DRAW, OnBtnDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExer_9_17Dlg message handlers

BOOL CExer_9_17Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
   m_ListShape.AddString("Line");
   m_ListShape.AddString("Circle");
   m_ListShape.AddString("Rectangle");
   m_ListShape.AddString("RoundRectangle");

   m_crPenColor=RGB(0,255,0);       //Ĭ�ϱ���ɫ
   m_crBrushColor=RGB(255,0,0);       //Ĭ��ˢ����ɫ
   m_nPenStyle=PS_SOLID;             //Ĭ�ϱ���ʽ
   m_nBrushStyle=0;                  //Ĭ��ˢ��ʽΪSolid
   m_ComboPenColor.SetCurSel(0);      //����Pen��Ͽ�ĵ�ǰѡ��
   m_ComboBrushColor.SetCurSel(0);      //����Brush��Ͽ�ĵ�ǰѡ��
   m_ListShape.SetCurSel(0);            //����Ĭ�ϵ�Shape
//���õ�ѡ��ť�ĳ�ʼ״̬
CheckRadioButton(IDC_RADIO_SOLID,IDC_RADIO_DASHDOT,IDC_RADIO_SOLID);
CheckRadioButton(IDC_RADIO_SOLIDBRUSH,IDC_RADIO_BDIAGONAL,IDC_RADIO_SOLIDBRUSH);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExer_9_17Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExer_9_17Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExer_9_17Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExer_9_17Dlg::OnRadioSolid() 
{
	// TODO: Add your control notification handler code here
    m_nPenStyle=PS_SOLID;  
	
}

void CExer_9_17Dlg::OnRadioDash() 
{
	// TODO: Add your control notification handler code here
   m_nPenStyle=PS_DASH;       //����ʽΪ����
	
}

void CExer_9_17Dlg::OnRadioDot() 
{
	// TODO: Add your control notification handler code here
   m_nPenStyle=PS_DOT;     //����ʽΪ����
	
}

void CExer_9_17Dlg::OnRadioDashdot() 
{
	// TODO: Add your control notification handler code here
	m_nPenStyle=PS_DASHDOT;    //����ʽΪ�㻮��
}

void CExer_9_17Dlg::OnRadioSolidbrush() 
{
	// TODO: Add your control notification handler code here
   m_nBrushStyle=0;      //���ģʽΪʵ���
	
}

void CExer_9_17Dlg::OnRadioCross() 
{
	// TODO: Add your control notification handler code here
	m_nBrushStyle=HS_CROSS;      //���ģʽΪ������
}

void CExer_9_17Dlg::OnRadioFdiagonal() 
{
	// TODO: Add your control notification handler code here
	m_nBrushStyle=HS_FDIAGONAL;      //���ģʽΪ����45����
}

void CExer_9_17Dlg::OnRadioBdiagonal() 
{
	// TODO: Add your control notification handler code here
	m_nBrushStyle=HS_BDIAGONAL;      //���ģʽΪ����45����
}

void CExer_9_17Dlg::OnSelendokComboPencolor() 
{
	// TODO: Add your control notification handler code here
   int i;
   i=m_ComboPenColor.GetCurSel();  //������ɫ��Ͽ�ĵ�ǰѡ����
   if(i==0)
   {
    	m_crPenColor=RGB(255,0,0);  //��1��Ϊ��ɫ
   }
   else if(i==1)
   {
    	m_crPenColor=RGB(0,255,0);   //��2��Ϊ��ɫ
   }
   else if(i==2)
   {
 	m_crPenColor=RGB(0,0,255);   //��3��Ϊ��ɫ
   }
   else if(i==3)
   {
	m_crPenColor=RGB(255,255,0);   //��4��Ϊ��ɫ
   }
  else if(i==4)
  {
	m_crPenColor=RGB(0,255,255);   //��5��Ϊ����ɫ
  }

	
}

void CExer_9_17Dlg::OnSelendokComboBrushcolor() 
{
	// TODO: Add your control notification handler code here
  int i;
  i=m_ComboBrushColor.GetCurSel();  //��ˢ��ɫ��Ͽ�ĵ�ǰѡ����
  if(i==0)
  {
 	m_crBrushColor=RGB(255,0,0);  //��1��Ϊ��ɫ
  }
   else if(i==1)
  {
	m_crBrushColor=RGB(100,255,255);   //��2��Ϊ��ɫ
  }
  else if(i==2)
  {
	m_crBrushColor=RGB(0,0,255);   //��3��Ϊ��ɫ
  }
  else if(i==3)
  {
	m_crBrushColor=RGB(255,255,0);   //��4��Ϊ��ɫ
  }
  else if(i==4)
  {
	m_crBrushColor=RGB(0,255,255);   //��5��Ϊ����ɫ
  }
	
}

void CExer_9_17Dlg::OnBtnDraw() 
{
	// TODO: Add your control notification handler code here
    CClientDC dc(this);                     //�õ��豸����ָ��
	CPen *ppenOld,penNew;                    //����ʶ���
	CBrush *pbrushOld,brushNew,brushBack;    //���廭ˢ����
	CRect rectClient;                        //�����û������δ�С
	GetClientRect(&rectClient);              //�õ��û������δ�С

	  POINT pts[6];
	/*rectClient.rightΪ�����Ĵ��ڵ����½ǵĺ�����
	*ǰ��������rectClient.right-170,20�ֱ��ʾ�����Ĵ����еľ��������Ͻǵĺ����꣬��������
	*����������rectClient.right-20,170�ֱ��ʾ�����Ĵ����еľ��������½ǵĺ����꣬��������
	*/
	CRect rectDraw(rectClient.right-170,20,rectClient.right-20,170);//����ͼ������С

	//�ð�ɫ��ˢ��ͼ����
	brushBack.CreateSolidBrush(RGB(255,255,255));//��������ָ����ɫ������ɫΪ��ɫ���ĵ�ɫ��ˢ
	pbrushOld=dc.SelectObject(&brushBack);   //����ˢѡ���豸����
	dc.Rectangle(rectDraw);                  //��������

	if(m_nBrushStyle!=0)                     //���廭ˢ
	{
		brushNew.CreateHatchBrush(m_nBrushStyle,m_crBrushColor);//��������ָ����Ӱͼ������ɫ�Ļ�ˢ
	}
	else
	{
		brushNew.CreateSolidBrush(m_crBrushColor);//��������ָ����ɫ�ĵ�ɫ��ˢ
	}
	
	penNew.CreatePen(m_nPenStyle,1,m_crPenColor);    //���������ɫ����ʽ�ı�
	ppenOld=dc.SelectObject(&penNew);                //ѡ���豸����
	dc.SelectObject(&brushNew);//�������ʺ󣬱������SelectObject��������ѡ���豸����

	if(m_ListShape.GetSel(0))           //����
	{
		/**
		*MoveTo�������ܣ��������û��ʵĵ�ǰλ�ã�����Ϊ�ᣬ�����꣩
		*LineTo�������ܣ������ӵ�ǰλ����ָ�����������ֱ�ߣ���ֱ�ߵ�������MoveTo�����е������������յ����LineTo�����еĲ�����
		*/
		//��������������
		dc.MoveTo(rectDraw.left,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.right,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.MoveTo(rectDraw.left,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.bottom);
        dc.MoveTo(rectDraw.right,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.bottom);
	}
	else if(m_ListShape.GetSel(1))    //��Բ
	{
		/*
		*Pie���������ǻ��ƻ��ߣ������û����뾶��Χ�ɵ�����
		*Pie�����а˸�������ǰ���������ֱ��Ǿ��α߿�����Ͻ����꣬
		*�����ĸ������ֱ�Ϊ���α߿�����½����꣬
		*�������������ֱ�Ϊ��Բ����ʼ���ߵĺ������꣬
		*������������ֱ�Ϊ��Բ����ֹ���ߵĺ�������
		*ԭ������ʼ������ֹ����ʱ�뻭����
		*/
		//��1/4����Բ�������Զ���䣬���յõ��ľ���һ������������
		//dc.Pie(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2,rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.top);
		
		//��1/2����Բ��
		//dc.Pie(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2,rectDraw.left,(rectDraw.bottom+rectDraw.top)/2);


		//��3/4����Բ��
		//dc.Pie(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2,(rectDraw.right+rectDraw.left)/2,rectDraw.bottom);

		//��һ��������Բ�������Զ���䣬���յõ��ľ���һ��������Բ
		dc.Pie(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2);
	
		//��Բ�л�һ��������
		dc.MoveTo(rectDraw.left,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.right,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.MoveTo(rectDraw.left,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.bottom);
        dc.MoveTo(rectDraw.right,rectDraw.top+(rectDraw.bottom-rectDraw.top)/2);
		dc.LineTo(rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.bottom);
		/**
		*Arc�������ƻ��ߣ������
		*/
		//dc.Arc(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom,rectDraw.right,(rectDraw.bottom+rectDraw.top)/2,rectDraw.left+(rectDraw.right-rectDraw.left)/2,rectDraw.top);
	
		
   /**
	*Polyline�������ܣ�������Σ������
	*/
 /* pts[0].x = 510;
    pts[0].y = 120;
    pts[1].x = 510;
    pts[1].y = 180;
    pts[2].x = 560 ;
    pts[2].y = 180;
    pts[3].x = 510;
    pts[3].y = 120;
    pts[4].x = 560 ;
    pts[4].y = 120;
	pts[5].x = 560 ;
    pts[5].y = 180;
    dc.Polyline(pts,6); */


   /**
    *Polygon����������Σ����õ�ǰ��ˢ�����
	**/
   /* pts[0].x = 510;
    pts[0].y = 120;
    pts[1].x = 510;
    pts[1].y = 180;
    pts[2].x = 560 ;
    pts[2].y = 180; 
    dc.Polygon(pts,3); */


		/**
		* Ellipse�������ܣ�ʹ�õ�ǰ���ʻ���һ����Բ�����õ�ǰ��ˢ���
		*/
		//dc.Ellipse(rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);
	}
	else if(m_ListShape.GetSel(2))    //������
	{
		/**
		*Rectangle�������ܻ����Σ����õ�ǰ��ˢ���
		*/
		dc.Rectangle(rectDraw);
	}
	else if(m_ListShape.GetSel(3))     //��Բ�Ǿ���
	{
		/**
		*RoundRect���ܣ���Բ�Ǿ��β��õ�ǰ��ˢ���
		*/
		dc.RoundRect(rectDraw,CPoint(50,50));
	}
	dc.SelectObject(ppenOld);
	dc.SelectObject(pbrushOld);
}
