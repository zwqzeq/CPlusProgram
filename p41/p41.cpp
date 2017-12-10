#include<windows.h>
#include<tchar.h>
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
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;   			//����ָ���豸�����ĵľ��
	PAINTSTRUCT PtStr; 	//����ָ�������ͼ��Ϣ�Ľṹ�����
	HBRUSH hBrush;  		//����ָ��ˢ�ľ��
	HPEN hPen;			//����ָ�򻭱ʵľ��
	static int dispMode = -1;
	LPCTSTR str;
	switch(iMessage)  //������Ϣ
	{
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:    							//�����ͼ��Ϣ
		hDC=BeginPaint(hWnd,&PtStr);
		dispMode = (dispMode+1)%6;
		switch(dispMode)
		{
		case 0:
			str = _T("ӳ�䷽ʽMM_TEXT��ȱʡ��ӳ�䷽ʽ");
			SetMapMode(hDC,MM_TEXT);  		//����ӳ��ģʽ
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 1:
			str = _T("ӳ�䷽ʽMM_ISOTROPIC����������Ϊ20��20��ӳ��Ϊ�ӿڳߴ�Ϊ10��10��ͼ����С1��");
			SetMapMode(hDC,MM_ISOTROPIC);  		
			SetWindowExtEx(hDC,20,20,NULL);		//���ھ���Ϊ20��20
			SetViewportExtEx(hDC, 10, 10, NULL);//ӳ��Ϊ�ӿڵľ���Ϊ10��10
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 2:
			str = _T("ӳ�䷽ʽMM_ISOTROPIC����������Ϊ10��10��ӳ��Ϊ�ӿڳߴ�Ϊ20��20��ͼ�ηŴ�1��");
			SetMapMode(hDC,MM_ISOTROPIC);  		
			SetWindowExtEx(hDC,10,10,NULL);		//���ھ���Ϊ10��10
			SetViewportExtEx(hDC, 20, 20, NULL);//ӳ��Ϊ�ӿڵľ���Ϊ20��20
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 3:
			str = _T("ӳ�䷽ʽMM_ANISOTROPIC����������Ϊ10��10��ӳ��Ϊ�ӿڳߴ�Ϊ20��10��ͼ�κ���Ŵ�1�������򲻱�");
			SetMapMode(hDC,MM_ISOTROPIC);  		//����ӳ��ģʽ
			SetWindowExtEx(hDC,10,10,NULL);		//���ھ���Ϊ10��10
			SetViewportExtEx(hDC, 20, 10, NULL);//ӳ��Ϊ�ӿڵľ���Ϊ20��10
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 4:
			str = _T("ӳ�䷽ʽMM_ANISOTROPIC����������Ϊ10��10��ӳ��Ϊ�ӿڳߴ�Ϊ20��5��ͼ�κ���Ŵ�1����������С1��");
			SetMapMode(hDC,MM_ANISOTROPIC);  		//����ӳ��ģʽ
			SetWindowExtEx(hDC,10,10,NULL);		//���ھ���Ϊ10��10
			SetViewportExtEx(hDC, 20, 5, NULL);//ӳ��Ϊ�ӿڵľ���Ϊ20��5
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 5:
			str = _T("ӳ�䷽ʽMM_ISOTROPIC����������Ϊ10��10��ӳ��Ϊ�ӿڳߴ�Ϊ20��5��ͼ��Ϊ�˱����ݺ�ȣ�ϵͳ�����ӳ�����");
			SetMapMode(hDC,MM_ISOTROPIC);  		//����ӳ��ģʽ
			SetWindowExtEx(hDC,10,10,NULL);		//���ھ���Ϊ10��10
			SetViewportExtEx(hDC, 20, 5, NULL);//ӳ��Ϊ�ӿڵľ���Ϊ20��5
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		}
		hPen=(HPEN)GetStockObject(BLACK_PEN);//���û���ΪϵͳԤ������ĺ�ɫ����
		hBrush=(HBRUSH)GetStockObject(DKGRAY_BRUSH); //����ϵͳԤ��������ɫ��ˢ
		SelectObject(hDC,hBrush);  			//ѡ��ˢ
		SelectObject(hDC,hPen);    			//ѡ�񻭱�
		RoundRect(hDC,50,120,100,200,15,15); //Բ�Ǿ���
		hBrush=(HBRUSH)GetStockObject(LTGRAY_BRUSH); //����ϵͳԤ���������ɫ��ˢ
		SelectObject(hDC,hBrush);  			//ѡ��ˢ
		Ellipse(hDC,150,50,200,150); 		//��Բ
		hBrush=(HBRUSH)GetStockObject(HOLLOW_BRUSH); //����ϵͳԤ������黭ˢ
		SelectObject(hDC,hBrush);  			//ѡ��ˢ
		Pie(hDC,250,50,300,100,250,50,300,50);  	//����
		EndPaint(hWnd,&PtStr);  				//������ͼ
		return 0;
	case WM_DESTROY: 						//����Ӧ�ó���
		PostQuitMessage(0);
		return 0;
	default:									//������Ϣ�������
		return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//���崰����
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("����ʾ��");
	TCHAR *szTitle = _T("ӳ��ģʽ�����ʾ��ͼ");
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
