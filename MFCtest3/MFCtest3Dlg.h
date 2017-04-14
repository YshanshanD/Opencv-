
// MFCtest3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\core\core.hpp>


// CMFCtest3Dlg 对话框
class CMFCtest3Dlg : public CDialogEx
{
// 构造
public:
	CMFCtest3Dlg(CWnd* pParent = NULL);	// 标准构造函数
//    static int OSTUthred(MatND disHist);
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	//double threshold;//二值化的阈值
	
public:
	afx_msg void OnBnClickedStart();
	CStatic picture_show;
	
private:
	CRect rect;
	CStatic* pStc; //标识图像显示的Picture控件  
	CDC* pDC; //视频显示控件设备上下文  
	HDC hDC; //视频显示控件设备句柄  
	CvCapture* capture; //视频获取结构  

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
