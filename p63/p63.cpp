#include<windows.h>
#include<tchar.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT WINAPI WndProc(HWND,UINT,UINT,LONG);
HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic);

//������
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
long WINAPI WndProc(HWND hWnd,UINT message,UINT wParam,LONG lParam)
{
	HDC hDC;
	HFONT hF;
	PAINTSTRUCT ps; //����ָ�������ͼ��Ϣ�Ľṹ�����
	wchar_t str[] = L" ��ã���ӭѧϰVC ";//" Hello VC  ";
	int i = 0;
	static int x[11], y[11];
	static int color[11];
	POINT pt;
	switch(message)  //������Ϣ
	{
		case WM_CREATE:
			SetTimer(hWnd,1111,200,NULL);
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);	//����Ļ����ת��Ϊ��������
			for(i = 0; i < 11; i++)
			{
				x[i] = pt.x + (i-1)*40;
				y[i] = pt.y;
				color[i] = 25 * (i-1);
			}
			break;
		case WM_PAINT: //�����ػ���Ϣ
			hDC=BeginPaint(hWnd,&ps);
			hF = CreateFont(hDC,40,0);
			SelectObject(hDC,hF);
			for(i = 10; i > 1; i--)
			{
				x[i] = x[i-1] + 40;
				y[i] = y[i-1];
			}
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);	//����Ļ����ת��Ϊ��������

			x[1] = pt.x;
			y[1] = pt.y;
			for(i = 1; i < 11; i++)
			{
				SetTextColor(hDC,RGB(255-color[i],color[i],255));
				TextOutW(hDC,x[i],y[i],&str[i],1);
			}
			color[1] = color[10];
			for(i = 10; i > 1; i--)
				color[i] = color[i-1];
			DeleteObject(hF);
			EndPaint(hWnd,&ps);
			break;
		case WM_TIMER:
			if(wParam==1111)
				InvalidateRect(hWnd, NULL,1);
			break;
		case WM_DESTROY: //�������Ӧ�ó�����Ϣ
			KillTimer(hWnd,1);
			PostQuitMessage(0);//����Ӧ�ó���
			break;
		default://������Ϣ�������
			return(DefWindowProc(hWnd, message, wParam, lParam)) ;
	}
	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//���崰����
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("����ʾ��");
	TCHAR *szTitle = _T("����Ӧ��ʾ��");
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

HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic)
{
	HFONT hFont;
	hFont = CreateFont(
		nCharHeight,
		0,
		0,
		0,
		400,
		bItalic,
		0,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Arial");
	return hFont;
}