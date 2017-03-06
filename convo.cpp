//g++ histo.cpp -o histo `pkg-config --cflags --libs`

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img,dest,dest2,h;

	img = imread(argv[1],0);
	imwrite("output0.bmp", img);
	dest = imread(argv[1],0);

	img.convertTo(img,CV_32F);
	img.convertTo(dest,CV_32F);

	int nl = img.rows;
	int nc = img.cols;
	printf("nb ligne=%i nb col=%i",nl,nc);
	float conv=0.;

	float hh[9]={0,1,0,1,2,1,0,1,0};

	h = Mat(3, 3, CV_32F, hh);

	cout << img << endl;
	cout << h << endl;

	for(int x=1;x<(nc-1);x++)
	{
		for(int y=1;y<(nc-1);y++)
		{
			for(int i=-1;i<2;i++)
			{
				for(int j=-1;j<2;j++)
				{
					conv=conv + h.at<float>(i,j)*img.at<float>((x)-i,(y)-j);
					//printf("x=%i y=%i i=%i j=%i conv=%f\n",x,y,i,j,conv);
				}
			}
		dest.at<float>(x,y)=conv;
		conv=0.;
		}
	}
cout << dest << endl;
printf("cc");
normalize(dest,dest,0,255,NORM_MINMAX,CV_8UC1);
printf("cc");
imwrite("output.bmp", dest);
}
