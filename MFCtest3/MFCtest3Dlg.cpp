
// MFCtest3Dlg.cpp : ʵ���ļ�
//
// <opencv2/opencv2.hpp>
#include "stdafx.h"
#include "MFCtest3.h"
#include "MFCtest3Dlg.h"
#include "afxdialogex.h" 
#include <string>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core\core.hpp>
using namespace cv;

using namespace std;
//using namespace cv;
CEvent start_event;
int terminate_flag;
//float hranges[] = { 0,255 };
//float *ranges[] = { hranges };
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	//ON_WM_TIMER()
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

	namedWindow("view", WINDOW_NORMAL);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

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
/*
int CMFCtest3Dlg::OSTUthred(MatND disHist) {
	    float  disArray[256];
	    for (int i = 0; i < 256; i++) 
		disArray[i] = disHist.at < float >(i);
		disArray[0]= 1;
		float u0, u1;
		float w0, w1;
		int count0;
		int t, maxT;
		float devi, maxDevi = 0;
		float  sum;
		int j;
		for ( j = 0; j < 256; j++)
		{
			sum = sum + disArray[j];

		}
		for (t = 0; t < 255; t++) {
			u0 = 0;
			count0 = 0;
			for (j = 0; j<=t; j++) {
				u0 += j* (disArray[j]);
				count0 = j*(disArray[j]);

			}
			u0 = u0 / count0;
			w0 = (float)count0 / sum;
			u1 = 0;
			for (j = t + 1; j < 256; j++) 
				u1 += j*(disArray[j]);
			u1 = u1 / (sum - count0);
			w1 = 1 - w0;
			devi = w0*w1*(u1 - u0)*(u1 - u0);
			if (devi > maxDevi) {
				maxDevi = devi;
				maxT=t;
			}
			
	   }
		return maxT;
	}

*/

UINT CMFCtest3Dlg::PlayVideo(LPVOID lpParam) {

	VideoCapture capture("D:\\MFC\\MFCtest3\\MFCtest3\\beijingcar.mp4");
	CMFCtest3Dlg* this_back = (CMFCtest3Dlg*)lpParam;
	//VideoCapture capture(0);
	Mat backgrpund;
	Mat temp;
	capture >> backgrpund;
	absdiff(backgrpund, backgrpund,backgrpund);
	cvtColor(backgrpund,backgrpund,CV_BGR2GRAY);
	capture.set(CV_CAP_PROP_POS_FRAMES, 0);
	for (int i = 0; i < 100; i++) {
		if(!capture.read(temp)) break;
		cvtColor(temp, temp, CV_BGR2GRAY);
		addWeighted(backgrpund, 1, temp, 0.01, 0, backgrpund);
	}
	//imshow("background", backgrpund);
	imwrite("back.jpg", backgrpund);
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
				
				//���ô�С����������
				
				cvtColor(frame, frame, CV_RGB2GRAY);//�Ҷȴ���
				subtract(frame, backgrpund, frame);//��ǰ֡�뱳�����в��
				Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
			    resize(frame, des, des.size());
				
				/*Mat disHist;
				int dims = 1;
				float hranges[] = { 0,255 };
				float *ranges[] = { hranges };
				int size = 256;
				int channels = 0;
				
				calcHist(&des, 1, &channels, Mat(), disHist, dims, &size, ranges);
				int scale = 1;
				Mat dis(size*scale, size, CV_8U, Scalar());
				int thresholdm = OSTUthred( disHist);
				if (thresholdm < 20) {
					thresholdm= 20;
				}*/
				
				threshold(des, des, 0, 255,CV_THRESH_OTSU);
			

				imshow("view", des );
				CString a;
				a.Format(_T("%d"), hold_value);
				this_back->show_value.SetWindowText(a);
				hold_value++;
			}
			if (CMFCtest3Dlg::playFlag == 3)
			{
				break;
			}
			waitKey(30);
		}
	}
	capture.release();
	return 0;

}


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


void CMFCtest3Dlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMFCtest3Dlg::playFlag = 3;
	::PostThreadMessage(playThread->m_nThreadID, WM_QUIT, 0, 0);

}

int CMFCtest3Dlg::playFlag = 2;