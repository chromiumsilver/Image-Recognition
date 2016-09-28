#include "check_color.h"
int check_color(char c)
{
	//������ͷ
	VideoCapture cap(1);
	int count;
	//����Ƿ�ɹ���
	if (!cap.isOpened())
	{
		cout << "Can not open the web cam" << endl;
		return -1;
	}
	//�������ƴ��ڣ��ɿ��Ƶ�ǰʶ�����ɫ��
	namedWindow("Control", CV_WINDOW_AUTOSIZE);

	int iLowH;
	int iHighH;
	int iLowS = 90;
	int iHighS = 255;
	int iLowV = 90;
	int iHighV = 255;
	switch (c)
	{
	case'r':iLowH = 100;
		iHighH = 140;
		break;
	case'y':iLowH = 100;
		iHighH = 140;
		break;
	case'b':iLowH = 100;
		iHighH = 140;
		break;
	default:
		return -1;
	}

	//��������̨
	cvCreateTrackbar("LowH", "Control", &iLowH, 179);//ɫ�� (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255);//���Ͷ�
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255);//����
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal);//��һ֡

		if (!bSuccess)//����Ƿ��ȡ�ɹ�

		{
			cout << "Can not read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);//ͼƬת����BGR to HSV��

													 //ֱ��ͼ���⻯
		split(imgHSV, hsvSplit);
		equalizeHist(hsvSplit[2], hsvSplit[2]);
		merge(hsvSplit, imgHSV);
		Mat imgThresholded;
		//��ɫ���
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

		//��������ȥ��һЩ��㣩
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

		//�ղ���������һЩ��ͨ��
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		imshow("Thresholded Image", imgThresholded);
		imshow("Original", imgOriginal);
		count = 0;
		for (int i = 0; i < imgThresholded.rows; ++i)
		{
			for (int j = 0; j < imgThresholded.cols; ++j)
			{
				if (imgThresholded.at<uchar>(i, j) != 0)
				{
					count++;
					cout << count << endl;
				}
				if (count > 100)
					break;
			}
			if (count > 100)
				break;
		}
		if (count > 10)
		{
			cout << "send!!!!!!!!!!!!!!" << endl;
			c_coms();
			c_comn();
			destroyAllWindows();
			return 0;
		}

		char key = (char)waitKey(300);
		if (key == 27)
			break;
	}
	return 0;
}
