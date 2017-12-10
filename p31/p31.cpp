//Windows.h�ļ��а���Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include <windows.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); //���ں���˵��
//------------ ���³�ʼ��������----------------
int WINAPI WinMain(	HINSTANCE	hInstance,		//WinMain����˵��
					HINSTANCE	hPrevInst,
					LPSTR		lpszCmdLine,
					int			nCmdShow)
{
		WNDCLASSEX wcex ;
		HWND hwnd ;
		MSG Msg ;
		TCHAR *szClassName = _T("����ʾ��");		//��������
		TCHAR *szTitle = _T("My_Windows");		//���ڱ�����
 
        //������Ķ���
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
		wcex.lpszClassName = szClassName ;//��������Ϊ"����ʾ��"
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION) ) ;
											
 //--------------- ���½��д������ע�� -----------------
	    if( !RegisterClassEx( &wcex))		//���ע��ʧ���򷢳���������
		{
			MessageBox(NULL, _T("������ע��ʧ�ܣ�"), _T("����ע��"),NULL) ;
			return 1 ;
		}
 
        //��������
		hwnd=CreateWindow(szClassName,		//��������
						szTitle,			//����ʵ���ı�����
						WS_OVERLAPPEDWINDOW,	//���ڵķ��
						CW_USEDEFAULT,CW_USEDEFAULT,//�������Ͻ�����Ϊȱʡֵ
						CW_USEDEFAULT,CW_USEDEFAULT,//���ڵĸߺͿ�Ϊȱʡֵ
						NULL,			//�˴����޸�����
						NULL,			//�˴��������˵�
						hInstance,		//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
						NULL) ;			//��ʹ�ø�ֵ
 
		if(!hwnd)
		{
			MessageBox(NULL, _T("��������ʧ�ܣ�"), _T("��������"),NULL) ;
			return 1 ;
		}
		ShowWindow( hwnd, nCmdShow) ;	//��ʾ����
		UpdateWindow(hwnd);				//�����û���
		while( GetMessage(&Msg, NULL, 0, 0))//��Ϣѭ��
		{
			TranslateMessage( &Msg) ;
			DispatchMessage( &Msg) ;
		}
 
		return (int)Msg.wParam;	//��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}
 
//���ں���
LRESULT CALLBACK WndProc(HWND hwnd,	UINT message,WPARAM  wParam,LPARAM  lParam)
{
	switch(message){
	case WM_DESTROY:
		PostQuitMessage(0);	//����PostQuitMessage����WM_QUIT��Ϣ
		break;
	default:				//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return  DefWindowProc(hwnd,message,wParam,lParam);
		break;
	}
	return (0);
}
