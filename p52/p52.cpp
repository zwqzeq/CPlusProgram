#include <windows.h>
#include <tchar.h>
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
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,UINT wParam,LONG lParam)
{
	HDC hdc;
	HFONT hF_black,hF_big;	//��������������
	PAINTSTRUCT ps;
	TEXTMETRIC tm;			//����һ��TEXTMETRIC�ṹ�����Լ�¼������Ϣ
	LPCWSTR lpsz_1 = L"����һ�к�ɫ�ġ�����ΪSYSTEM_FONT�����֣���ɫ����δ����";
	LPCWSTR lpsz_2 = L"������ʾ�����Զ������壬��ɫΪ��ɫ����ɫ��������������";
	LPCWSTR lpsz_3 = L"����չ��������ǰ������ɫ�Ĵ����֣���ɫ��������ĺ������ա�";
	LPCWSTR lpsz_4 = L"��ǰ����Ϊ��š�б�岢�����»��ߵ����֡�";
	LPCWSTR lpsz_5 = L"����������������Ĳ�������?";
	LPCWSTR lpsz_6 = L"ף���ɹ�!";
	LPCWSTR lpsz_7 = L"VC2008��һ�ż����רҵ����Ҫ�γ�!";

	int X=0,Y=0;
	static RECT rect = {0,300,0,350};
	SIZE size;					//����һ��SIZE���͵Ľṹ

	switch(message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 9999, 50, NULL);
		break;
	case WM_TIMER:
		if(wParam==9999)
			InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		rect.right += 2;
		hdc=BeginPaint(hWnd,&ps);
		SetTextColor(hdc,RGB(255,0,0));	//�����ı���ɫΪ��ɫ
		GetTextMetrics(hdc,&tm);	//��ȡȱʡ���壬д��tm�ṹ��
		TextOutW(hdc,X,Y,lpsz_1, wcslen(lpsz_1));	//ʹ�õ�ǰ��������ı�
		Y=Y+tm.tmHeight+100*tm.tmExternalLeading;//���㻻��ʱ��һ���ı����������	
								
		//�����Զ�������
		hF_black=CreateFont(
				20,				//����ĸ߶�
				0,				//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ
				0,				//�ı�����б��Ϊ0����ʾˮƽ
				0,				//�������б��Ϊ0
				FW_HEAVY,		//����Ĵֶȣ�FW_HEAVYΪ���
				0,				//��б����
				0,				//���»���
				0,				//��ɾ����
				GB2312_CHARSET,	//��ʾ���õ��ַ���ΪANSI_CHARSET
				OUT_DEFAULT_PRECIS,	//�������Ϊȱʡ����
				CLIP_DEFAULT_PRECIS,	//���þ���Ϊȱʡ����
				DEFAULT_QUALITY,		//�������Ϊȱʡֵ
				DEFAULT_PITCH|FF_DONTCARE,//�ּ�������ϵ��ʹ��ȱʡֵ
				"������"				//��������
			);

		SetTextColor(hdc,RGB(0,255,0));	//�����ı���ɫΪ��ɫ
		SelectObject(hdc,hF_black);		//���Զ�������ѡ���豸����
		GetTextMetrics(hdc,&tm);		//��ȡ�������Ϣ����д��tm�ṹ��
		TextOutW(hdc,X,Y,lpsz_2,wcslen(lpsz_2));//ʹ�õ�ǰ��������ı�
		//���м�������ı����������е���ʼY����λ��
		Y=Y+tm.tmHeight+10*tm.tmExternalLeading;	
		GetTextExtentPoint32W(hdc,lpsz_2,wcslen(lpsz_2),&size);
													//��ȡ�ַ���/�Ŀ��
		SetTextColor(hdc,RGB(0,0,255));	//�����ı���ɫΪ��ɫ
		TextOutW(hdc,X,Y,lpsz_3,wcslen(lpsz_3));//�õ�ǰ��������ı�
		//X=0;					//������һ���ı��������ʼ����
		Y=Y+tm.tmHeight+20*tm.tmExternalLeading; 
		hF_big=CreateFont(		//����������
			30,					//����߶�
			0,
			0,
			0,
			FW_NORMAL,
			1,			//����б��
			1,			//�������ʱ���»���
			0,
			GB2312_CHARSET,	//��ʹ�õ��ַ���
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"�����"
		);

		SelectObject(hdc,hF_big);	//���ڶ����Զ�������ѡ���豸����
		SetTextColor(hdc,RGB(155,155,155));	//�����ı���ɫΪ��ɫ
		Y=Y+tm.tmHeight+5*tm.tmExternalLeading;	
 		TextOutW(hdc,X,Y,lpsz_4,wcslen(lpsz_4));//�Ե�ǰ��������ı�
		SetTextColor(hdc,RGB(255,0,0));	//�����ı���ɫΪ��ɫ

		Y=Y+tm.tmHeight+10*tm.tmExternalLeading;	
		TextOutW(hdc,X,Y,lpsz_5,wcslen(lpsz_5)); 	//����ı�
		//�ڸ��м�������ı�
		GetTextExtentPoint32W(hdc,lpsz_5,wcslen(lpsz_5),&size);//��ȡ�ַ����Ŀ��
		X=X+size.cx;							//��ȡ��ʼ����
		TextOutW(hdc,X,Y,lpsz_6,wcslen(lpsz_6)); 	//����ı�

		hF_big=CreateFont(		//����������
			48,					//����߶�
			0,
			0,
			0,
			FW_NORMAL,
			0,			//����б��
			0,			//�������ʱ���»���
			0,
			GB2312_CHARSET,	//��ʹ�õ��ַ���
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"����_GB2312"
		);
		SelectObject(hdc, hF_big);
		SetTextColor(hdc, RGB(0,0,0));
		SetBkColor(hdc, RGB(100,150,100));
		TextOutW(hdc, 0, 300, lpsz_7, wcslen(lpsz_7));
		SetTextColor(hdc, RGB(0,255,0));
		SetBkColor(hdc, RGB(150,50,50));
		DrawTextW(hdc, lpsz_7, wcslen(lpsz_7), &rect, DT_LEFT);
		GetTextExtentPoint32W(hdc,lpsz_7,wcslen(lpsz_7),&size);//��ȡ�ַ����Ŀ��
		if(rect.right>=size.cx)
			rect.right=0;
		EndPaint(hWnd,&ps);
		DeleteObject(hF_black);
		DeleteObject(hF_big);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return  DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//���崰����
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("����ʾ��");
	TCHAR *szTitle = _T("�ı����ʾ��");
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