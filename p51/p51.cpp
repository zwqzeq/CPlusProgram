#include<windows.h>
#include<tchar.h>
#include<math.h>
#define PI 3.1415926
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HFONT CreateMyFont(LPWSTR fontName,int height,int lean);
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
	HFONT font;
	HPEN hPen;		//����ָ�򻭱ʵľ��
	LPWSTR title = L"�Ǹ� �ơ��Ÿ�",
		poem[8] = {L"�缱���ԳХ��", L"���ɳ����ɻ�",
					L"�ޱ���ľ������", L"��������������", 
					L"���ﱯ�ﳣ����", L"����ಡ����̨",
					L"���ѿ�޷�˪��", L"�ʵ���ͣ�ǾƱ�"};
	LPCWSTR outInfo;
	int r, r0, i, j=-1, fontSize, fontSize0, color;
	RECT clientDimension;
	POINT begin, end, org;
	double sita;

	switch(Message)  //������Ϣ
	{
	case WM_PAINT:    							//�����ͼ��Ϣ
		hDC=BeginPaint(hWnd,&ps);
		hPen = CreatePen(PS_DASH, 1, RGB(127, 127, 127));
		SelectObject(hDC, hPen);
		GetClientRect(hWnd, &clientDimension);
		if( (clientDimension.right-clientDimension.left)<400 ||
			(clientDimension.bottom-clientDimension.top)<300 )
		{
			MessageBox(hWnd, _T("��Ļ�ߴ�̫С���޷���ͼ��"), _T("������Ϣ"),0);
			break;
		}
		r = (clientDimension.bottom-clientDimension.top)*8/10;
		org.x = (clientDimension.right-clientDimension.left)/2;
		org.y = (clientDimension.bottom-clientDimension.top)*9/10;
		Arc(hDC, org.x-r, org.y-r,org.x+r,org.y+r,
			org.x+(int)(r*sin(PI/3)),org.y-(int)(r*cos(PI/3)),
			org.x-(int)(r*sin(2*PI/3)),org.y+(int)(r*cos(2*PI/3)));
		for(sita=PI/6; sita<=PI*5/6; sita+=PI*2/27)
		{
			begin.x = org.x-(int)(r*cos(sita));
			begin.y = org.y-(int)(r*sin(sita));
			MoveToEx(hDC, begin.x,begin.y,NULL);
			end.x = org.x;
			end.y = org.y;
			LineTo(hDC,end.x,end.y);
		}
		r0 = r * 2 / 5;
		Arc(hDC, org.x-r0, org.y-r0,org.x+r0,org.y+r0,
			org.x+(int)(r0*sin(PI/3)),org.y-(int)(r0*cos(PI/3)),
			org.x-(int)(r0*sin(2*PI/3)),org.y+(int)(r0*cos(2*PI/3)));
		sita = PI/6 + PI*4/15/5;
		fontSize0 = fontSize = (r-r0)/7;
		r0 = r-20;
		for(i=0; i<7; i++)
		{
			outInfo = &title[i];
			fontSize -= 3;
			font = CreateMyFont(L"����_GB2312", fontSize-5,-(sita+PI/15)*1800/PI);
			SelectObject(hDC,font);
			begin.x = org.x + (int)(r0*cos(sita));
			begin.y = org.y - (int)(r0*sin(sita));
			TextOutW(hDC, begin.x, begin.y, outInfo,1);
			r0 -= fontSize;
			DeleteObject(font);
		}
		for(sita=PI/6+PI*4/27-PI/40; sita<PI*5/6; sita += PI*2/27)
		{
			fontSize = fontSize0;
			r0 = r-20;
			j++;
			color = 0;
			for(i=0; i<7; i++)
			{
				color += 255/7;
				SetTextColor(hDC, RGB(255-color,0,color));
				LPCWSTR outInfo = &poem[j][i];
				fontSize -= 3;
				font = CreateMyFont(L"�����п�",fontSize, (int)(((sita-PI/2)*1800/PI))%3600);
				SelectObject(hDC,font);
				begin.x = org.x + (int)(r0*cos(sita));
				begin.y = org.y - (int)(r0*sin(sita));
				TextOutW(hDC, begin.x,begin.y,outInfo,1);
				r0 -= fontSize;
				DeleteObject(font);
				Sleep(10);
			}
		}
		EndPaint(hWnd,&ps);  				//������ͼ
		break;
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
 
HFONT CreateMyFont(LPWSTR fontName, int height, int lean)
{
	return CreateFontW(
						height,				//����ĸ߶�
						0,				//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ
						lean,				//�ı�����б��Ϊ0����ʾˮƽ
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
						fontName				//��������
						);

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
