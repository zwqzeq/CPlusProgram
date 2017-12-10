#include<windows.h>
#include<tchar.h>
#include<math.h>
typedef struct Time
{
	int hour, minute, second;
}TimeStructure;
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AdjustTime(TimeStructure *x);
//������
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	if(!InitWindowClass(hInstance, nCmdShow))
	{
		MessageBox(NULL, _T("��������ʧ�ܣ�"), _T("��������"),NULL);
		return 1;
	}
	while(GetMessage(&Message,0,0,0))	//��Ϣѭ��
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//��Ϣ������ 
LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,UINT wParam,LONG lParam)
{
	HDC hDC;   			//����ָ���豸�����ĵľ��
	PAINTSTRUCT ps; 	//����ָ�������ͼ��Ϣ�Ľṹ�����
	static HBRUSH hBrush, hOldBrush;  		//����ָ��ˢ�ľ��
	static HPEN hPenSecond, hPenMinute, hPenHour, hPenRed, hOldPen,hPen;	//����ָ�򻭱ʵľ��
	RECT clientRect;
	static TimeStructure x;
	float sita = 0;
	int xOrg, yOrg, rSec, rMin, rHour, rClock, xBegin,yBegin,xEnd,yEnd, i;
	switch(Message)  //������Ϣ
	{
	case WM_CREATE:
		hBrush = CreateSolidBrush(RGB(255,220,220));//�ۺ�ɫ
		hPenSecond = CreatePen(PS_SOLID, 2, RGB(255,0,0));
		hPenMinute = CreatePen(PS_SOLID, 5, RGB(0,0,0));
		hPenHour = CreatePen(PS_SOLID, 10, RGB(0,0,0));
		SetTimer(hWnd, 9999,1000,NULL);
		hPenRed = CreatePen(PS_SOLID, 5, RGB(255,0,0));
		break;
	case WM_PAINT:    							//�����ͼ��Ϣ
//		x.second++;
		AdjustTime(&x);
		hDC=BeginPaint(hWnd,&ps);
		GetClientRect(hWnd, &clientRect);
		hPen=(HPEN)GetStockObject(BLACK_PEN);//���û���ΪϵͳԤ������ĺ�ɫ����
		hOldPen = (HPEN)SelectObject(hDC,hPen);    			//ѡ�񻭱�
		hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		xOrg = (clientRect.left + clientRect.right)/2;
		yOrg = (clientRect.top + clientRect.bottom)/2;

		rClock = min(xOrg, yOrg) - 50;
		rSec = rClock * 6 / 7;
		rMin = rClock * 5 / 6;
		rHour = rClock * 2 / 3;
		Ellipse(hDC, xOrg - rClock, yOrg - rClock, xOrg + rClock, yOrg + rClock);
		DeleteObject(hPen);	//

		for(i=0; i<60; i++)
		{
			if(i%5)
			{
				SelectObject(hDC, hPenSecond);
				xBegin = xOrg + rClock*sin(2*3.14159*i/60);
				yBegin = yOrg + rClock*cos(2*3.14159*i/60);
				xEnd = xOrg + (rClock-20)*sin(2*3.14159*i/60);
				yEnd = yOrg + (rClock-20)*cos(2*3.14159*i/60);
			}
			else
			{
//				hPen = CreatePen(PS_SOLID, 5, RGB(255,0,0));
				SelectObject(hDC, hPenRed);
				xBegin = xOrg + rClock*sin(2*3.14159*i/60);
				yBegin = yOrg + rClock*cos(2*3.14159*i/60);
				xEnd = xOrg + (rClock-25)*sin(2*3.14159*i/60);
				yEnd = yOrg + (rClock-25)*cos(2*3.14159*i/60);
			}
			MoveToEx(hDC, xBegin, yBegin, NULL);
			LineTo(hDC, xEnd, yEnd);
		}

		sita = 2*3.14159*x.second/60;
		xBegin = xOrg + (int)(rSec * sin(sita));
		yBegin = yOrg - (int)(rSec * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(��+��)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
		SelectObject(hDC, hPenSecond);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);

		sita = 2*3.14159*x.minute/60;
		xBegin = xOrg + (int)(rMin * sin(sita));
		yBegin = yOrg - (int)(rMin * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(��+��)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 5, RGB(0,0,0));
		SelectObject(hDC, hPenMinute);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);
		
		sita = 2*3.14159*x.hour/12;
		xBegin = xOrg + (int)(rHour * sin(sita));
		yBegin = yOrg - (int)(rHour * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(��+��)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 10, RGB(0,0,0));
		SelectObject(hDC, hPenHour);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);
		EndPaint(hWnd,&ps);  				//������ͼ
		break;
	case WM_TIMER:
		if(wParam == 9999)
			InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY: 						//����Ӧ�ó���
		DeleteObject(hPenRed);
		DeleteObject(hPenSecond);
		DeleteObject(hPenMinute);
		DeleteObject(hPenHour);
		DeleteObject(hPen);
		DeleteObject(hBrush);

		PostQuitMessage(0);
		return 0;
	default:									//������Ϣ�������
		return(DefWindowProc(hWnd, Message,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
void AdjustTime(TimeStructure *x)
{
/*	if(x->second==60)
	{
		x->second = 0;
		x->minute++;
		if(x->minute==60)
		{
			x->minute = 0;
			x->hour++;
			if(x->hour==12)
				x->hour=0;
		}
	}*/
	SYSTEMTIME st;
	GetLocalTime(&st);
	x->hour = (st.wHour)%12;
	x->minute = st.wMinute;
	x->second = st.wSecond;
	
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//���崰����
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("����ʾ��");
	TCHAR *szTitle = _T("ģ��ʱ��");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;						//��������Ϊȱʡ����
	wcex.lpfnWndProc = WndProc ;		//���ڴ�����ΪWndProc
	wcex.cbClsExtra	= 0 ;				//����������չ
	wcex.cbWndExtra	= 0 ;				//����ʵ������չ
	wcex.hInstance = hInstance ;		//��ǰʵ�����
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_APPLICATION) ) ;
											//���ڵ���С��ͼ��Ϊȱʡͼ��
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW) ;
											//���ڲ��ü�ͷ���
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH) ;
											//���ڱ���Ϊ��ɫ
	wcex.lpszMenuName = NULL ;			//�������޲˵�
	wcex.lpszClassName = szWindowClass ;//��������Ϊ"����ʾ��"
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION) ) ;
	if( !RegisterClassEx( &wcex))		//���ע��ʧ���򷵻�
		return FALSE ;
	hWnd=CreateWindow(szWindowClass,  						//���ɴ���
						szTitle,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						0,
						CW_USEDEFAULT,
						0,
						NULL,
						NULL,
						hInstance,
						NULL);
	if(!hWnd)
			return FALSE;
	ShowWindow(hWnd,nCmdShow);					//��ʾ����
	UpdateWindow(hWnd);
	return TRUE;
}
