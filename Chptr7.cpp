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
#define ORANGE  0,69,255

//********************** FINDING SHAPES, CORNER, OBJECT TYPES etc **********************
Mat imgGray, imgBlur, imgCanny, imgDil;

/*çevre, þekil 'i al */
void getContours(Mat imgDil, Mat img) {

/* Vector Structor
	{{Point(20,30),Point(50,60)},
	 {Point(10,70),Point(40,60)},
	 {Point(50,20),Point(80,60)}}
*/
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	string objectType;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(BLACK), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		auto area = contourArea(contours[i]);
		cout << "Object_Area: " << area << endl;

		if (area > 1000) {
			//drawContours(img, contours, i, Scalar(BLUE), 2);

			auto peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
	
			cout <<"Corner_Counts: " << conPoly[i].size() << endl;					//finding corners
		
			/********************************************************/
			boundRect[i]= boundingRect(conPoly[i]);
			int objCor = (int)conPoly[i].size();

			switch (objCor){
				case 0:
				case 1:
				case 2:
					objectType = "Not an object";
					break;
				case 3:
					objectType = "Triangel";
					break;
				case 4: {
					float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
					(aspRatio > 0.95 && aspRatio < 1.05) ? objectType = "Square" : objectType = "Rectangle";
					cout << "Asp_Ratio: " << aspRatio << endl;
				}
				break;
				default:
					objectType = "Circle";
					break;
			}

			drawContours(img, conPoly, i, Scalar(RED), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(GREEN), 2);
			putText(img, objectType, {boundRect[i].x,boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(BLACK), 1);

			cout << "\n" << endl;
		}


	}
}


int main(void) {

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	// Pre-processing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);

	//imshow("Image_Gray", imgGray);
	//imshow("Image_Blur", imgBlur);
	//imshow("Image_Canny", imgCanny);
	//imshow("Image_Dilate", imgDil);
	waitKey(0);

}