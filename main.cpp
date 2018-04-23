//#include <stdio.h>
//#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

//using namespace std;
using namespace cv;

//Algorithm explained at: https://en.wikipedia.org/wiki/Lyapunov_fractal
double lyapunov(double a, double b, double x0, int N) {
    int abSize = 2;
	//double ab[abSize] = { b, a, a, b, a, b, b, a, a, b, b, a, b, a, a, b};
    double ab[abSize] = { b, a};
	double xn = b*x0*(1 - x0);
	double sum = 0;
	for (int i = 1; i < N; i++) {
		xn = ab[i % abSize] * xn*(1 - xn);
		sum += log2(fabs(ab[i % abSize]*(1 - 2 * xn)));
	}
	return sum / (double)N;
}

int main() {

	//view ini:
    int screenWidth = 1280;
    int screenHeight = 720;
	Mat image(screenHeight, screenWidth, CV_64FC3);
	std::vector<Mat> image_vec;
	cv::split(image, image_vec);

	//algorithmus
	double chaos;
	for (double y = 0; y < screenHeight; y++) {
		for (double x = 0; x < screenWidth; x++) {
            //the algorithm calculates the chaos value of one specific pixel
			chaos = lyapunov(x/400.+2, y/400.+2, 0.5, 100);
			if (chaos < 0)
                //draw "order" on blue channel
				image_vec.at(0).at<double>(y, x) = -chaos;
			else
                //draw "chaos" on red channel
				image_vec.at(2).at<double>(y, x) = chaos;
		}
	}

	//view:
	merge(image_vec, image);
	cv::imshow("Display Image", image);
	cv::waitKey(0);
	return 0;
}