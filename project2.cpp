#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*My globals*/
Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThreshold, imgDil, imgErode;



cv::Mat preProcessing(cv::Mat img) {

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);

	return imgDil;
}

/*çevre, þekil 'i al */
std::vector<Point> getContours(cv::Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	string objectType;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(BLACK), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	vector<Point>biggest;

	for (int i = 0; i < contours.size(); i++) {
		auto area = contourArea(contours[i]);  //Shape area
		cout << "Object_Area: " << area << endl;

		if (area > 1000) {
			//drawContours(img, contours, i, Scalar(BLUE), 2);

			auto peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			drawContours(imgOriginal, conPoly, i, Scalar(RED), 2);
			
		}
	}
	return biggest;
}



void main(void) {

	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	/*	1.Pre-processing
		2.Get contours-biggest
		3.warp 
	*/

	//1
	imgThreshold = preProcessing(imgOriginal);
	

	//2
	//getContours(imgThreshold);


	imshow("image_Original", imgOriginal);
	imshow("image_Dilation", imgThreshold);
	waitKey(0);
}
