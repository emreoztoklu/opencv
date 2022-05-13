#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

///////////////  Project 2 - Document Scanner  //////////////////////
// 
//BGR Blue Green Red
#define BLUE	255,0,0
#define GREEN	0,255,0
#define RED		0,0,255
#define PINK	255,0,255
#define WHITE	255,255,255
#define BLACK	0,0,0
#define ORANGE  67,142,255
#define YELLOW  115,228,214

/*My globals*/
Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThreshold, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;

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

	vector<Point>biggest;
	int maxArea = 0;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(BLACK), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());



	for (int i = 0; i < contours.size(); i++) {
		auto area = contourArea(contours[i]);  //Shape area
		cout << "Object_Area: " << area << endl;

		if (area > 1000) {
			//drawContours(img, contours, i, Scalar(BLUE), 2);

			auto peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(imgOriginal, conPoly, i, Scalar(PINK), 5);
				biggest = {conPoly[i][0], conPoly[i][1] ,conPoly[i][2], conPoly[i][3]};
				maxArea = area;
			}

			//drawContours(imgOriginal, conPoly, i, Scalar(RED), 2);

		}
	}
	return biggest;
}

void drawPoints(std::vector<Point> drawn_points, cv::Scalar drawn_color) {

	for (int i = 0; i < drawn_points.size(); i++) {
		circle(imgOriginal, drawn_points[i], 10, drawn_color, FILLED);
		putText(imgOriginal, to_string(i), drawn_points[i], FONT_HERSHEY_PLAIN, 3, drawn_color, 2);
	}

}

std::vector<Point> reorder(std::vector<Point>points) {
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	/*
	  0***********1
	  *			  *
	  *			  *
	  *           *
	  2***********3	
	*/

	//0.point
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	
	//1.point
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	
	//2.point
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	
	//3.point
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return newPoints;
}

cv::Mat getWarp(cv::Mat image, std::vector<Point> points, float w, float h) {
	
	Point2f src[4] = { points[0],  points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };

	cv::Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(image, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

void main(void) {

	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	/*	1.Pre-processing
		2.Get contours-biggest
		3.warp 
	*/

	//1.Pre-processing
	imgThreshold = preProcessing(imgOriginal);
	

	//2.Get contours-biggest
	initialPoints = getContours(imgThreshold);
	//drawPoints(initialPoints, Scalar(RED));
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(GREEN));

	//3.Warp

	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	int cropVal = 5; 
	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	imgCrop = imgWarp(roi);

	imshow("image_Original", imgOriginal);
	imshow("image_Dilation", imgThreshold);
	imshow("image_Warp", imgWarp);
	imshow("image_Crop", imgCrop);

	waitKey(0);
}
