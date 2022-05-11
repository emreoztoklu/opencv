#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//********************** IMAGES **********************
int main(void) {

	string path = "Resources/test.jpg";
	Mat img = imread(path);
	imshow("BGR_Image", img);

/////////////////////GRAY IMAGE//////////////////////////
	Mat imgGray;
	ColorConversionCodes color = COLOR_BGR2GRAY;

	cvtColor(img, imgGray, color);
	imshow("GRAY_Image", imgGray);

////////////////////BLUR IMAGE////////////////////////////
	Mat imgBlur;

	GaussianBlur(imgGray, imgBlur,Size(3,3),5,0);
	imshow("BLUR_Image", imgBlur);

////////////////////EDGE DETECTOR//////////////////////////
	Mat imgCanny;

	Canny(img, imgCanny, 80, 120);
	imshow("EDGE_Canny_Detect", imgCanny);

////////////////////IMAGE _DILATE/////////////////////////////
	Mat imgDila, imgErode;
	MorphShapes shape = MORPH_RECT;
	Mat kernel = getStructuringElement(shape, Size(3, 3));   // use in size odd numbers

	dilate(imgCanny, imgDila, kernel);
	erode(imgDila, imgErode, kernel);

	imshow("Dilation_Image", imgDila);
	imshow("Erode_Image", imgErode);

///////////////////////////////////////////////////////////

	waitKey(0);
}

