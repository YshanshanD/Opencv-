
// MFCtest3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core\core.hpp>


// CMFCtest3Dlg �Ի���
class CMFCtest3Dlg : public CDialogEx
{
// ����
public:
	CMFCtest3Dlg(CWnd* pParent = NULL);	// ��׼���캯��
//    static int OSTUthred(MatND disHist);
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	//double threshold;//��ֵ������ֵ
	
public:
	afx_msg void OnBnClickedStart();
	CStatic picture_show;
	
private:
	CRect rect;
	CStatic* pStc; //��ʶͼ����ʾ��Picture�ؼ�  
	CDC* pDC; //��Ƶ��ʾ�ؼ��豸������  
	HDC hDC; //��Ƶ��ʾ�ؼ��豸���  
	CvCapture* capture; //��Ƶ��ȡ�ṹ  

public:
	CButton StopButton;
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	CWinThread *playThread;
	static int playFlag;
	static UINT PlayVideo(LPVOID pParam);
	int blockSize = 5;
	int constValue = 10;
	//int maxVal = 255;
private:
	int picture_x;
	int picture_y;
	int thresholdm;
public:
	CEdit show_value;

	 

};
