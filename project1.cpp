#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//BGR Blue Green Red
#define BLUE	255,0,0
#define GREEN	0,255,0
#define RED		0,0,255
#define PINK	255,0,255
#define WHITE	255,255,255
#define BLACK	0,0,0
#define ORANGE  67,142,255
#define YELLOW  115,228,214

/********************** CAM: Project1 **********************/
Mat img;
vector<vector<int>>newPoints;   // {{x,y,color_val}, {x,y,color_val2}....


vector<vector<int>>myColors{{1,  211, 86, 178,  255, 255,},	//ORANGE
							{24, 32, 120, 45,  255, 255,},  //SARI
							{67, 72, 156, 102, 126, 255,},	//GREEN
						   };

vector<Scalar>myColorValues{{ORANGE}, {YELLOW}, {GREEN}, {PINK},
							{WHITE},  {BLACK},  {BLUE},  {RED}};

/*çevre, þekil 'i al */
Point getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	string objectType;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(BLACK), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {
		auto area = contourArea(contours[i]);  //Shape area
		cout << "Object_Area: " << area << endl;

		if (area > 1000) {
			//drawContours(img, contours, i, Scalar(BLUE), 2);

			auto peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << "Corner_Counts: " << conPoly[i].size() << endl;					//finding corners

			/********************************************************/
			boundRect[i] = boundingRect(conPoly[i]);

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(RED), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(GREEN), 3);
		}
	}
	return myPoint;
}


void findColor(Mat image) {
	Mat imgHSV;
	Mat mask;
	cvtColor(image, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		if(myPoint.x != 0 && myPoint.y !=0)
			newPoints.push_back({ myPoint.x, myPoint.y, i});
	}
}

void drawOnCanvas(vector<vector<int>> drawnPoints, vector<Scalar> drawnColor){

	int pen_ticknes = 10;

	for (int i = 0; i < drawnPoints.size(); i++) {
		circle(img, Point(drawnPoints[i][0], drawnPoints[i][1]), pen_ticknes, myColorValues[drawnPoints[i][2]], FILLED);
	}
}


void main(void) {

	VideoCapture cap(1);

	while (true) {

		cap.read(img);

		findColor(img);
		drawOnCanvas(newPoints, myColorValues);


		imshow("Camera_Image", img);
		waitKey(1);

	}
}
