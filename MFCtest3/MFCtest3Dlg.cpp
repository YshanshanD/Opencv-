
// MFCtest3Dlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "MFCtest3.h"
#include "MFCtest3Dlg.h"
#include "afxdialogex.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CMFCtest3Dlg::playFlag = 2;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCtest3Dlg �Ի���



CMFCtest3Dlg::CMFCtest3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMFCtest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHARE, picture_show);
	DDX_Control(pDX, IDC_PAUSE, StopButton);
	DDX_Control(pDX, IDC_EDIT1, show_value);
}

BEGIN_MESSAGE_MAP(CMFCtest3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMFCtest3Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_PAUSE, &CMFCtest3Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_STOP, &CMFCtest3Dlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CMFCtest3Dlg ��Ϣ�������

int CMFCtest3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		int bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//�õ�������Ϣ
	namedWindow("view", WINDOW_NORMAL);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

    //����ʾ����picture�ؼ���
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_SHARE);//IDC_PIC_2DΪ�ؼ�ID
	pWnd->GetClientRect(&rc);//rcΪ�ؼ��Ĵ�С��
	picture_x = rc.Height();
	picture_y = rc.Width();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCtest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCtest3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCtest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

  //���Ŵ�����Ƶ
UINT CMFCtest3Dlg::PlayVideo(LPVOID lpParam) {

	VideoCapture capture("D:\\MFC\\�½��ļ���\\US-101-ProcessedVideo-0805am-0820am-Cam1234\\guangguang.avi");
	CMFCtest3Dlg* this_back = (CMFCtest3Dlg*)lpParam;//ǿ��ת��
	Mat background;
	Mat temp;
	capture >> background;
	absdiff(background, background,background);//
	cvtColor(background,background,CV_BGR2GRAY);
	capture.set(CV_CAP_PROP_POS_FRAMES, 0);//��Ƶ֡���´ӿ�ͷ��
	//��ǰ100֡����ȡ����
	for (int i = 0; i < 100; i++) {
		if(!capture.read(temp)) break;
		cvtColor(temp, temp, CV_BGR2GRAY);
		addWeighted(background, 1, temp, 0.01, 0, background);//����Ȩ�ؼ��㵱ǰ֡
	}
	//imwrite("back.jpg", background);

	//imshow("����",background);
	capture.set(CV_CAP_PROP_POS_FRAMES, 0);
	int hold_value = 1;
	while (1)
	{
		MSG my_msg;
		if (PeekMessage(&my_msg, 0, 0, 0, PM_REMOVE))
		{
			if (my_msg.message == WM_QUIT)
			{
				capture.release();
				return 0;
			}
		}
		else
		{
			Mat frame;
			if (CMFCtest3Dlg::playFlag == 1)
			{
				capture.set(CV_CAP_PROP_POS_FRAMES, 0);
				CMFCtest3Dlg::playFlag = 0;
			}
			if (CMFCtest3Dlg::playFlag == 0)
			{
				capture >> frame;
				if (!capture.read(frame)) break;
				//�˲�����

				cvtColor(frame, frame, CV_RGB2GRAY);//�Ҷȴ���
				medianBlur(frame, frame, 3);
				subtract(frame, background, frame);//��ǰ֡�뱳�����в��

	            //���ô�С����������
				//Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
			   // resize(frame, des, des.size());
				//threshold(frame, frame, 0, 255,CV_THRESH_OTSU);//��ֵ����
				//int g_nStructElementSize = 1;
		     	//Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1));
			    //erode(des,des,element);//��ʴ����
				imshow("view", frame );

				CString a;
				a.Format(_T("%d"), hold_value);
				this_back->show_value.SetWindowText(a);
				hold_value++;
			}
			if (CMFCtest3Dlg::playFlag == 3)
			{
				break;
			}
			waitKey(90);
		}
	}
	capture.release();
	return 0;

}

//�����¼�
void CMFCtest3Dlg::OnBnClickedStart()
{

	LPVOID param;
	int mid = CMFCtest3Dlg::playFlag;
	CMFCtest3Dlg::playFlag = 1;
	if (mid != 2 || playThread == NULL)
	{
		playThread = AfxBeginThread(PlayVideo, this, 0, 0, 0, 0);
	}
}
	
	
//��ͣ�¼�
void CMFCtest3Dlg::OnBnClickedPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString buttonText;
	StopButton.GetWindowText(buttonText);

	if (CMFCtest3Dlg::playFlag != 0)
	{
		CMFCtest3Dlg::playFlag = 0;
		StopButton.SetWindowTextW(_T("����"));

	}
	else
	{
		CMFCtest3Dlg::playFlag = 2;
		StopButton.SetWindowText(_T("��ͣ"));
	}
}

//ֹͣ�¼�
void CMFCtest3Dlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMFCtest3Dlg::playFlag = 3;
	::PostThreadMessage(playThread->m_nThreadID, WM_QUIT, 0, 0);

}
