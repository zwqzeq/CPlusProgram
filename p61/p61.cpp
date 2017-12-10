#include<windows.h>
#include<stdlib.h>
#include<string.h>
void WINAPI CaretPos(HWND hWnd,int nArrayPos,char *cCharBuf,int *xCaret,int *yCaret,int nCharWidth);
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;

//������
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
		if(!InitWindowsClass(hInstance))
			return FALSE;
	if(!InitWindows(hInstance,nCmdShow))
			return FALSE;
	while(GetMessage(&Message,0,0,0))//��Ϣѭ��
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		return Message.wParam;
}

//��Ϣ������
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
#define BufSize 30					//���ô���ַ��Ļ�������С		
	static char cCharBuf[BufSize];	//���þ�̬�ַ����飬���������ַ����ַ��������ܳ�����������С
	static int nNumChar=0;		//�����ַ�����
	static int nArrayPos=0;		//�ַ���λ��
	static int nLnHeight;
	static int nCharWidth;
	static int xCaret,yCaret;
	int x;
	HDC hDC;
		TEXTMETRIC tm;
	PAINTSTRUCT PtStr; //����ָ�������ͼ��Ϣ�Ľṹ�����
		switch(iMessage)  //������Ϣ
		{
			case WM_CHAR:				//������ϵͳ�ַ������Ĵ���
			{
				if(wParam==VK_BACK)  	//����"�������˼�����Ϣ"
			 	{
					if(nArrayPos==0) //����Ѿ���һ�����ֵĿ�ʼ��������ʾ�û�"���ܻ���"
						MessageBox(hWnd,"��ǰλ�����ı�����ʼλ�ã����ܻ���",NULL,MB_OK);
					else
					{
						nArrayPos=nArrayPos-1; //ÿ��һ�λ��˼��ͻ���һ���ַ���λ��
						for(x=nArrayPos;x<nNumChar-1;x++)
							cCharBuf[x]=cCharBuf[x+1];
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						nNumChar=nNumChar-1;	//�������ַ��������м���
						InvalidateRect(hWnd,NULL,TRUE);	//ˢ���û���������Ӧ�ó�����WM_PAINT��Ϣ
					}
					break;
				}
				if(wParam<=VK_ESCAPE) //������Escape����Ϣ
				{
					MessageBox(hWnd,"�����ڲ��ܰ�ESC�����������������",NULL,MB_OK);
					break;
				}
				if(nNumChar>=BufSize) //���д����ַ���������������С���򱨾�
				{
					MessageBox(hWnd,"�����������������������ַ���\n����Ҫɾ���ַ�������BackSpace��",NULL,MB_OK);
					break;
				}
				for(x=nNumChar;x>nArrayPos;x=x-1)
					cCharBuf[x]=cCharBuf[x-1];
				cCharBuf[nArrayPos]=(unsigned char)wParam;
				nArrayPos=nArrayPos+1;
				nNumChar=nNumChar+1;
				CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
				InvalidateRect(hWnd,NULL,TRUE);
			}
			break;

		case WM_CREATE: //�����ڴ�����Ϣ
			{
				hDC=GetDC(hWnd);
				GetTextMetrics(hDC,&tm); //��ȡ������Ϣ
				nLnHeight=tm.tmHeight+tm.tmExternalLeading;
				nCharWidth=tm.tmAveCharWidth;
				yCaret=nLnHeight;
				ReleaseDC(hWnd,hDC);
			}
			break;
		case WM_SETFOCUS: //����������Ϣ
			{
				CreateCaret(hWnd,0,0,nLnHeight);
				CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
				ShowCaret(hWnd); //�ڻ����Ĵ�������ʾ���ַ�
			}
			break;
		case WM_KILLFOCUS: //����ʧȥ������Ϣ
			DestroyCaret();
			break;
		case WM_KEYDOWN: //�����¼���Ϣ
			{
				switch(wParam)
				{
					case VK_END: //�����¼�ΪEndʱ����Ϣ
						nArrayPos=nNumChar;	//����λ�ôӱ��е�ĩβ��ʼ
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						break;
					case VK_HOME:	//�����¼�ΪHomeʱ����Ϣ
						nArrayPos=0;	//����λ��Ϊ���е���ʼλ��
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						break;
					case VK_DELETE://�����¼�ΪDeleteʱ����Ϣ
						if(nArrayPos==nNumChar)  //����λ�ô��ڱ��е�ĩβ
							MessageBox(hWnd,"���λ���Ѿ�����β��û���ַ��ɹ�ɾ��",NULL,MB_OK);
						else
						{
							for(x=nArrayPos;x<nNumChar-1;x=x+1)
								cCharBuf[x]=cCharBuf[x+1];	//ÿɾ��һ���ַ��������������ַ�����1
							nNumChar=nNumChar-1;
							InvalidateRect(hWnd,NULL,TRUE); //�û���ˢ��
						}
						break;
					case VK_LEFT: //�����������ʱ����Ϣ
						if(nArrayPos>0)
						{
							nArrayPos=nArrayPos-1;  //��ǰ����λ����ǰ��һ��λ�ã��������ַ�ʱ�����ڲ����ַ�
							CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						}
						else	//�Ѿ��Ƶ���ʼ����λ�ã���������ǰ��
							MessageBox(hWnd,"���Ѿ��ƶ�����ʼλ�ã������������ƶ���",NULL,MB_OK);
						break;
					case VK_RIGHT://�������ҷ����ʱ����Ϣ
						if(nArrayPos<nNumChar)	//�����ǰλ��û�е������������λ�ã����������ƶ�	
						{
							nArrayPos=nArrayPos+1;
							CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						}
						else
							MessageBox(hWnd,"�Ѿ�����������ĩβ,�����������ƶ���",NULL,MB_OK);
						break;
				}
			}
			break;
		case WM_PAINT: //�����ػ���Ϣ
			{
				hDC=BeginPaint(hWnd,&PtStr);
				TextOut(hDC,nCharWidth,nLnHeight,cCharBuf,nNumChar); //����������е��ı�
				EndPaint(hWnd,&PtStr);
			}
			break;
	case WM_DESTROY: //�������Ӧ�ó�����Ϣ
			PostQuitMessage(0);//����Ӧ�ó���
			break;
	default://������Ϣ�������
			return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		}
		return 0;
}

void WINAPI CaretPos(HWND hWnd,int nArrayPos,char *cCharBuf,int *xCaret,int *yCaret,int nCharWidth)					//������ַ�λ�õĺ���
{
	DWORD dWord; 
	SIZE size;
	HDC hDC;								//�����豸��������
	hDC=GetDC(hWnd);//ȡ�õ�ǰ�豸��������
	GetTextExtentPoint32(hDC,cCharBuf,nArrayPos,&size);//��ȡ���λ��
	dWord=size.cx;
	ReleaseDC(hWnd,hDC); 
	*xCaret=LOWORD(dWord)+nCharWidth;
	SetCaretPos(*xCaret,*yCaret);		//���ò��ַ�λ������
}

BOOL InitWindowsClass(HINSTANCE hInstance)//��ʼ��������
{
		WNDCLASS WndClass;
		WndClass.cbClsExtra=0;
		WndClass.cbWndExtra=0;
		WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
		WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
		WndClass.hIcon=LoadIcon(NULL,"END");
		WndClass.hInstance=hInstance;
		WndClass.lpfnWndProc=WndProc;
		WndClass.lpszClassName="WinKeyboard";
		WndClass.lpszMenuName=NULL;
		WndClass.style=CS_HREDRAW|CS_VREDRAW;
		return RegisterClass(&WndClass);
}

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow)//��ʼ������
{	
		HWND hWnd;
		hWnd=CreateWindow("WinKeyboard",  		//���ɴ���
						"���̲�������",
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
	hWndMain=hWnd;
	ShowWindow(hWnd,nCmdShow);	//��ʾ����
	UpdateWindow(hWnd);			//�����û���
		return TRUE;
}
