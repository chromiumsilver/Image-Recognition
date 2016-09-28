#include"main.h"
int check_shape(char c)
{
	//����ͼ����ʾ��ת��Ϊ�Ҷ�ͼ
	Mat trainImage = imread("fenda.jpg"), trainImage_gray;

	imshow("ԭʼͼ", trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	//���Surf�ؼ��㡢��ȡѵ��ͼ��������
	vector<KeyPoint> train_keyPoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainImage_gray, train_keyPoint);
	SurfDescriptorExtractor featureExtractor;
	featureExtractor.compute(trainImage_gray, train_keyPoint, trainDescriptor);

	//��������FLANN��������ƥ�����
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	//������Ƶ���󡢶���֡��
	VideoCapture cap(1);
	int count;
	unsigned int frameCount = 0;//֡��

								//��5������ѭ����ֱ��q��������
	while (char(waitKey(1)) != 'q')
	{
		//��������
		count = 0;
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;//�ɼ���Ƶ��testImage��
		if (testImage.empty())
			continue;

		//ת��ͼ�񵽻Ҷ�
		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);

		//���S�ؼ��㡢��ȡ����ͼ��������
		vector<KeyPoint> test_keyPoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keyPoint);
		featureExtractor.compute(testImage_gray, test_keyPoint, testDescriptor);

		//ƥ��ѵ���Ͳ���������
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		//���������㷨��Lowe's algorithm�����õ������ƥ���
		vector<DMatch> goodMatches;
		for (unsigned int i = 0; i < matches.size(); i++)
		{
			if (matches[i][0].distance < 0.6 * matches[i][1].distance)
			{
				goodMatches.push_back(matches[i][0]);
				count++;
				cout << count<<endl;
			}
		}
		if (count > 20)
		{
			cout << "send!!!!!!!!!!!!!!" << endl;
			c_coms();
			c_comn();
			return 1;
		}
		//<6>����ƥ��㲢��ʾ����
		Mat dstImage;
		drawMatches(testImage, test_keyPoint, trainImage, train_keyPoint, goodMatches, dstImage);
		imshow("ƥ�䴰��", dstImage);
	}

	return 0;
}
