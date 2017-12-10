#include<windows.h>
#include<tchar.h>
#include<math.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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
	HBRUSH hBrush;  		//����ָ��ˢ�ľ��
	HPEN hPen;			//����ָ�򻭱ʵľ��
	RECT clientRect,rc;
	static RECT oldClientRect = {0,0,0,0};
	float sita = 0;
	int a[4] = {75,50,60,90}, maxValue, i, xOrg, yOrg,
		deltaX,deltaY,xBegin,yBegin,xEnd,yEnd, s=0;
								/* /////	 \\\\\		 +++++		 xxxxx */
	int hatchBrushStyle[4] = {HS_BDIAGONAL, HS_FDIAGONAL,HS_CROSS, HS_DIAGCROSS};
								//red			green		blue		Violet
	COLORREF colorIndex[4] = {RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(255,0,255)};

	switch(Message)  //������Ϣ
	{
	case WM_PAINT:    							//�����ͼ��Ϣ
		maxValue = a[0];
		for(i=0; i<4; i++)
		{
			s+=a[i];
			if(a[i]>maxValue)
				maxValue = a[i];
		}
		hDC=BeginPaint(hWnd,&ps);
		GetClientRect(hWnd, &clientRect);
		if((clientRect.right-clientRect.left)<300 ||
			(clientRect.bottom-clientRect.top)<300)
		{
			MessageBox(hWnd, _T("��Ļ�ߴ�̫С���޷���ͼ��"), _T("������Ϣ"),0);
			EndPaint(hWnd, &ps);
			break;
		}
		hPen=(HPEN)GetStockObject(BLACK_PEN);//���û���ΪϵͳԤ������ĺ�ɫ����
		SelectObject(hDC,hPen);    			//ѡ�񻭱�
		Rectangle(hDC, clientRect.left + 10, clientRect.top + 10,
			clientRect.right - 10, clientRect.bottom -10);
		MoveToEx(hDC, (clientRect.left+clientRect.right)/2, clientRect.top + 10, NULL);
		LineTo(hDC,(clientRect.left+clientRect.right)/2, clientRect.bottom - 10);

		xOrg = clientRect.left + 60;
		yOrg = clientRect.bottom -60;
		xEnd = (clientRect.left+clientRect.right)/2 - 50;
		yEnd = yOrg;
		deltaX = (xEnd - xOrg - 100)/4;
		MoveToEx(hDC, xOrg, yOrg, NULL);
		LineTo(hDC, xEnd, yEnd);		//������
		xEnd = xOrg;
		yEnd = clientRect.top + 60;
		MoveToEx(hDC, xOrg, yOrg, NULL);
		LineTo(hDC, xEnd, yEnd);		//������
		deltaY = (yOrg - yEnd - 100)/maxValue;

		hPen = CreatePen(PS_SOLID,1,RGB(127,127,127));
		SelectObject(hDC, hPen);
		for(i=0; i<4; i++)	//��4������ͼ
		{
			hBrush = CreateHatchBrush(hatchBrushStyle[i], colorIndex[i]);
			SelectObject(hDC, hBrush);
			xBegin = xOrg + deltaX * i;
			yBegin = yOrg;
			xEnd = xBegin + deltaX;
			yEnd = yOrg - deltaY * a[i];
			Rectangle(hDC, xBegin, yBegin, xEnd, yEnd);
		}
		
		xOrg = clientRect.left + (clientRect.right-clientRect.left)*3/4 + 10;
		yOrg = clientRect.top + (clientRect.bottom - clientRect.top)/2 + 10;
		deltaX = deltaY = min((clientRect.right-clientRect.left)/4,
							(clientRect.bottom-clientRect.top)/2)-50;
		xBegin = xOrg + 10;
		yBegin = yOrg;
		for(i=0; i<4; i++)
		{
			hBrush = CreateSolidBrush(colorIndex[i]);
			SelectObject(hDC, hBrush);
			sita = sita-2*3.14159*a[i]/s;
			xEnd = xOrg + 10 * cos(sita);
			yEnd = yOrg + 10 * sin(sita);
			Pie(hDC, xOrg-deltaX,yOrg-deltaY, xOrg+deltaX,yOrg+deltaY,xBegin,yBegin,xEnd,yEnd);
			xBegin = xEnd;
			yBegin = yEnd;
		}
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd,&ps);  				//������ͼ
		return 0;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY: 						//����Ӧ�ó���
		PostQuitMessage(0);
		return 0;
	default:									//������Ϣ�������
		return(DefWindowProc(hWnd, Message,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//���崰����
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("����ʾ��");
	TCHAR *szTitle = _T("����ͼ����ͼ��ʾ����ͳ��");
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
	if( !RegisterClassEx( &wcex))		//���ע��ʧ���򷢳���������
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
