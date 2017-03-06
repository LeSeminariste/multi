//g++ histo.cpp -o histo `pkg-config --cflags --libs`

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat img;
	img = imread(argv[1],1); //CV_LOAD_IMAGE_GRAYSCALE
	int nl = img.rows;
	int nc = img.cols * img.channels();
	int histo[nl*nc] = {0};
	for(int i=0;i<nl;i++)
	{
		for(int j=0;j<nc;j++)
		{
			histo[(int)img.at<uchar>(i,j)]++;
			//printf("%i ",histo[i,j]);
		}
	//printf("\n");
	}
	for(int z=0;z<nl*nc;z++)
	{
		printf("%i ",histo[z]);
	
	}
}
