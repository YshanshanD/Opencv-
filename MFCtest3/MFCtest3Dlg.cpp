
// MFCtest3Dlg.cpp : 实现文件
#include "stdafx.h"
#include "MFCtest3.h"
#include "MFCtest3Dlg.h"
#include "afxdialogex.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CMFCtest3Dlg::playFlag = 2;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCtest3Dlg 对话框



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


// CMFCtest3Dlg 消息处理程序

int CMFCtest3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//得到窗口信息
	namedWindow("view", WINDOW_NORMAL);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

    //将显示框与picture控件绑定
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_SHARE);//IDC_PIC_2D为控件ID
	pWnd->GetClientRect(&rc);//rc为控件的大小。
	picture_x = rc.Height();
	picture_y = rc.Width();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCtest3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCtest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

  //播放处理视频
UINT CMFCtest3Dlg::PlayVideo(LPVOID lpParam) {

	VideoCapture capture("D:\\MFC\\新建文件夹\\US-101-ProcessedVideo-0805am-0820am-Cam1234\\guangguang.avi");
	CMFCtest3Dlg* this_back = (CMFCtest3Dlg*)lpParam;//强制转换
	Mat background;
	Mat temp;
	capture >> background;
	absdiff(background, background,background);//
	cvtColor(background,background,CV_BGR2GRAY);
	capture.set(CV_CAP_PROP_POS_FRAMES, 0);//视频帧重新从开头来
	//用前100帧来获取背景
	for (int i = 0; i < 100; i++) {
		if(!capture.read(temp)) break;
		cvtColor(temp, temp, CV_BGR2GRAY);
		addWeighted(background, 1, temp, 0.01, 0, background);//根据权重计算当前帧
	}
	//imwrite("back.jpg", background);

	//imshow("背景",background);
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
				//滤波处理

				cvtColor(frame, frame, CV_RGB2GRAY);//灰度处理
				medianBlur(frame, frame, 3);
				subtract(frame, background, frame);//当前帧与背景进行差分

	            //重置大小，满足需求
				//Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
			   // resize(frame, des, des.size());
				//threshold(frame, frame, 0, 255,CV_THRESH_OTSU);//阈值处理
				//int g_nStructElementSize = 1;
		     	//Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1));
			    //erode(des,des,element);//腐蚀操作
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

//启动事件
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
	
	
//暂停事件
void CMFCtest3Dlg::OnBnClickedPause()
{
	// TODO:  在此添加控件通知处理程序代码
	CString buttonText;
	StopButton.GetWindowText(buttonText);

	if (CMFCtest3Dlg::playFlag != 0)
	{
		CMFCtest3Dlg::playFlag = 0;
		StopButton.SetWindowTextW(_T("继续"));

	}
	else
	{
		CMFCtest3Dlg::playFlag = 2;
		StopButton.SetWindowText(_T("暂停"));
	}
}

//停止事件
void CMFCtest3Dlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCtest3Dlg::playFlag = 3;
	::PostThreadMessage(playThread->m_nThreadID, WM_QUIT, 0, 0);

}
