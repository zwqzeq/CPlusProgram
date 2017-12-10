#include <windows.h>
#include<stdio.h>
#define DIVISIONS 5
#include <math.h>
#define Pi 3.1415926
#define R 50		//�糵�뾶
#define NUM 3		//�Ӵ��ڸ���
int nMaxNum = 20;	//nMaxNum��¼��ҶƬѭ��һ���л�ͼ�Ĵ���.

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM) ;
TCHAR szChildClass[] = TEXT ("ChildWindow") ;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Checker3") ;
	HWND hwnd ;
	MSG msg ;
	WNDCLASS wndclass ;
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc = WndProc ;
	wndclass.cbClsExtra = 0 ;
	wndclass.cbWndExtra = 0 ;
	wndclass.hInstance = hInstance ;
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,0));//(HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName = NULL ;
	wndclass.lpszClassName = szAppName ;
	if (!RegisterClass (&wndclass))
	{
		MessageBox ( NULL, TEXT ("Program requires Windows NT!"),szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	wndclass.lpfnWndProc = ChildWndProc ;
	wndclass.cbWndExtra = 2*sizeof (long) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (NULL_BRUSH) ;//���Ӵ��ڵı���Ϊ͸��
	wndclass.lpszClassName = szChildClass ;
	RegisterClass (&wndclass) ;						//ע���Ӵ�������
	hwnd = CreateWindow (szAppName, TEXT ("���������Ӵ���"),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL) ;
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}

//��������Ϣ������.
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
{
	static HWND hwndChild[NUM] ;
	static int cxBlock, cyBlock;
	static POINT ps;
	int i;
	switch (message)
	{
	case WM_CREATE :
		for( i = 0; i < NUM; i++)
		{
			hwndChild[i] = CreateWindow (szChildClass, NULL,
				WS_CHILDWINDOW | WS_VISIBLE/* | WS_SYSMENU| WS_CAPTION*/ ,
				0, 0, 0, 0,
				hwnd, (HMENU)i,					//�Ӵ��ڵ�IDֵ
				(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL) ;
			SetWindowLong(hwndChild[i],0,i);	//�趨���ڵ�һ��������Ϣ���������
			SetWindowLong(hwndChild[i],4,0);	//�趨���ڵڶ���������Ϣ�����ڷ糵ת������
			SetTimer(hwndChild[i],i,(i+1)*30,0);
		}
		return 0 ;
	case WM_SIZE :	//���Ӵ��ڰ����ʵĳߴ��λ��������������
		cxBlock = LOWORD (lParam) / 2 ;
		cyBlock = HIWORD (lParam) / 2 ;
		for( i=0; i<NUM;i++)
			MoveWindow ( hwndChild[i],R+i*(2*R+20), cyBlock-R,2*R, 2*R, TRUE) ;
		return 0 ;
	case WM_LBUTTONDOWN :
		MessageBeep (0) ;
		return 0 ;
	case WM_DESTROY :
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

//�Ӵ�����Ϣ������.
long WINAPI ChildWndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;				//�����豸�������.
	HBRUSH hBrush;			//���廭ˢ���
	HPEN hPen;				//���廭�ʾ��
	PAINTSTRUCT PtStr;		//���������ͼ��Ϣ�Ľṹ�����
	int nCentreX,nCentreY;	//����3��ҶƬ��Բ�ĵ�����.
	int nNum;				//��ǰ������.
	double fAngle;

	switch(iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		KillTimer(hWnd,GetWindowLong(hWnd,0));
		break;
	case WM_PAINT:							//�����ͼ��Ϣ.
		nNum = GetWindowLong (hWnd, 4);
		hDC=BeginPaint(hWnd,&PtStr);		//����豸����ָ��.
		SetMapMode(hDC,MM_ANISOTROPIC);		//����ӳ��ģʽ.
		SetViewportOrgEx(hDC,R,R,NULL);	//�����ӿ�ԭ������Ϊ(300,200).����λ.
		//������Բ��
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		Ellipse(hDC,-R,-R,R,R);
		//���Ʒ糵��ҶƬ��

		hBrush = CreateSolidBrush(RGB(255,0,0));		//����ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		fAngle = 2*Pi/nMaxNum*nNum;						//����ҶƬ�Ƕ�
		nCentreX = (int)(R/2*cos(fAngle));
		nCentreY = (int)(R/2*sin(fAngle));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle)),(int)(nCentreY+R/2*sin(fAngle)),
			(int)(nCentreX+R/2*cos(fAngle+Pi)),(int)(nCentreY+R/2*sin(fAngle+Pi)));

		hBrush = CreateSolidBrush(RGB(255,255,0));		//������ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(R/2*cos(fAngle+2*Pi/3));
		nCentreY = (int)(R/2*sin(fAngle+2*Pi/3));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle+2*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+2*Pi/3)),
			(int)(nCentreX+R/2*cos(fAngle+Pi+2*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+Pi+2*Pi/3)));

		hBrush = CreateSolidBrush(RGB(0,255,255));		//����ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(R/2*cos(fAngle+4*Pi/3));
		nCentreY = (int)(R/2*sin(fAngle+4*Pi/3));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle+4*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+4*Pi/3)),
			(int)(nCentreX+R/2*cos(fAngle+Pi+4*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+Pi+4*Pi/3)));
		
		EndPaint(hWnd,&PtStr);		//�ͷŻ���ָ�롣
		nNum++;						//��ǰ������1.
		SetWindowLong(hWnd,4,nNum);	//���ô��ڷ糵��ת���������ڴ��ڸ�����Ϣ��

		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,1);	//�ػ洰������.
		break;
	case WM_DESTROY:	//�رմ���.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return DefWindowProc (hWnd, iMessage, wParam, lParam) ;
}