#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define BLUE	255,0,0
#define PINK	255,0,255
#define WHITE	255,255,255
#define BLACK	0,0,0
#define ORANGE  0,69,255


///////////  Warp Images ////////////
float w = 250, h = 350;
Mat matrix, imgWarp;


int main(void) {

	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	Point2f src_king[4] = {{529,142},  {771,190},{405,395},{674,457}};
	Point2f dst_king[4] = {{0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h}};

	Point2f src_joker[4] = { {778,108},  {1016,84},{844,359},{1116,331} };
	Point2f dst_joker[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };

	Point2f src_queen[4] = { {64,324},  {336,280},{93,634},{400,570} };
	Point2f dst_queen[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };

	Point2f src_diamond9[4] = { {744,386},  {1021,440},{649,709},{966,782} };
	Point2f dst_diamond9[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };


	matrix = getPerspectiveTransform(src_king, dst_king);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	//imshow("Warp_Image_King", imgWarp);

	matrix = getPerspectiveTransform(src_joker, dst_joker);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	//imshow("Warp_Image_Joker", imgWarp);

	matrix = getPerspectiveTransform(src_queen, dst_queen);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	//imshow("Warp_Image_Queen", imgWarp);

	matrix = getPerspectiveTransform(src_diamond9, dst_diamond9);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	//imshow("Warp_Image_Diamond9", imgWarp);


	for (int i = 0; i < 4; i++) {
		circle(img, src_king[i], 10, Scalar(ORANGE), FILLED);
		circle(img, src_joker[i], 10, Scalar(ORANGE), FILLED);
		circle(img, src_queen[i], 10, Scalar(ORANGE), FILLED);
		circle(img, src_diamond9[i], 10, Scalar(ORANGE), FILLED);
	}


	imshow("image", img);
	waitKey(0);
}

