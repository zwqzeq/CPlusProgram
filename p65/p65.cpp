//Windows.h�ļ��а���Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include <windows.h>
#include <stdio.h>
#include <string.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); //���ں���˵��
WINDOWPLACEMENT m_WindowPlacement,m_NewWindowPlacement;
HINSTANCE hInst;
//------------ ���³�ʼ��������----------------
int WINAPI WinMain(	HINSTANCE	hInstance,		//WinMain����˵��
					HINSTANCE	hPrevInst,
					LPSTR		lpszCmdLine,
					int			nCmdShow)
{
		HWND hwnd ;
		MSG Msg ;
		WNDCLASS wndclass ;
		char lpszClassName[] = "����";		//��������
		char lpszTitle[]= "My_Windows";		//���ڱ�����
		hInst = hInstance;
        //������Ķ���
		wndclass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS|CS_SAVEBITS;	//��������Ϊȱʡ����
		wndclass.lpfnWndProc = WndProc ;		//���ڴ�����ΪWndProc
		wndclass.cbClsExtra	= 0 ;			//����������չ
		wndclass.cbWndExtra	= 0 ;			//����ʵ������չ
		wndclass.hInstance = hInstance ;		//��ǰʵ�����
		wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION) ;
											//���ڵ���С��ͼ��Ϊȱʡͼ��
		wndclass.hCursor = LoadCursorFromFile("horse.ani");
								// LoadCursor( NULL, IDC_ARROW) ;//���ڲ��ü�ͷ���
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH) ;
											//���ڱ���Ϊ��ɫ
		wndclass.lpszMenuName = NULL ;		//�������޲˵�
		wndclass.lpszClassName = lpszClassName ;
											//��������Ϊ"����ʾ��"
 //--------------- ���½��д������ע�� -----------------
	    if( !RegisterClass( &wndclass))		//���ע��ʧ���򷢳���������
		{
			MessageBeep(0) ;
			return FALSE ;
		}
 
        //��������
		hwnd=CreateWindow(lpszClassName,		//��������
						lpszTitle,			//����ʵ���ı�����
						WS_OVERLAPPEDWINDOW,	//���ڵķ��
						CW_USEDEFAULT,
						CW_USEDEFAULT,		//�������Ͻ�����Ϊȱʡֵ
						CW_USEDEFAULT,
						CW_USEDEFAULT,,		//���ڵĸߺͿ�Ϊȱʡֵ
						NULL,			//�˴����޸�����
						NULL,			//�˴��������˵�
						hInstance,		//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
						NULL) ;			//��ʹ�ø�ֵ
 
		//��ʾ����
		ShowWindow( hwnd, nCmdShow) ;
		//�����û���
		UpdateWindow(hwnd);
		//��Ϣѭ�� 
		while( GetMessage(&Msg, NULL, 0, 0))
		{
			TranslateMessage( &Msg) ;
			DispatchMessage( &Msg) ;
		}
 
		return Msg.wParam;	//��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}
 
//���ں���
LRESULT CALLBACK WndProc(	HWND hwnd,
								UINT message,
								WPARAM  wParam,
								LPARAM  lParam)
{
	HCURSOR hc;
	switch(message){
	case WM_DESTROY:
		PostQuitMessage(0);	//����PostQuitMessage����WM_QUIT��Ϣ
		break;
	case WM_LBUTTONDOWN:
//		hc = (HCURSOR)LoadImage(hInst,"hnwse.cur",IMAGE_CURSOR,0,0,LR_DEFAULTSIZE);
//		SetCursor(hc);
		break;
 
	default:				//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return  DefWindowProc(hwnd,message,wParam,lParam);
	}
	return (0);
}
