//g++ sobel.cpp -o sobel `pkg-config opencv --cflags --libs`

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img,dest,dest2,h1,h2;

	img = imread(argv[1],0);
	imwrite("output0.bmp", img);
	dest = imread(argv[1],0);

	img.convertTo(img,CV_32F);
	img.convertTo(dest,CV_32F);

	int nl = img.rows;
	int nc = img.cols;
	printf("nb ligne=%i nb col=%i",nl,nc);
	float conv1=0.;
	float conv2=0.;
	float gradient=0.;
	float seuil=atof(argv[2]);

	float hh1[9]={-1,0,1,-2,0,2,-1,0,1};
	float hh2[9]={-1,-2,-1,0,0,0,1,2,1};

	h1 = Mat(3, 3, CV_32F, hh1);
	h2 = Mat(3, 3, CV_32F, hh2);


	//cout << img << endl;
	//cout << h1 << endl;
	//cout << h2 << endl;

	for(int x=1;x<(nl-1);x++)
	{
		for(int y=1;y<(nc-1);y++)
		{
			for(int i=-1;i<2;i++)
			{
				for(int j=-1;j<2;j++)
				{
					conv1=conv1 + h1.at<float>(i+1,j+1)*img.at<float>((x)-i,(y)-j);
					conv2=conv2 + h2.at<float>(i+1,j+1)*img.at<float>((x)-i,(y)-j);
					//printf("x=%i y=%i i=%i j=%i ",x,y,i,j);
					//printf("c1=%f [%f:%f]",conv1, h1.at<float>(i+1,j+1), img.at<float>((x)-i,(y)-j));
					//printf("c2=%f [%f:%f]\n",conv2, h2.at<float>(i+1,j+1), img.at<float>((x)-i,(y)-j));

				}
			}
		//dest.at<float>(x,y)=conv;
		gradient=sqrt((conv1*conv1)+(conv2*conv2));
		//printf("g=%f \n",gradient);
		if(gradient>seuil)
			dest.at<float>(x,y)=255.;
			else dest.at<float>(x,y)=0.;
		conv1=0.;conv2=0.;
		}
	}
//cout << dest << endl;
printf("\n");
cout << h1 << endl;
printf("\n");
cout << h2 << endl;
printf("\n");
printf("seuil = %f",seuil);
normalize(dest,dest,0,255,NORM_MINMAX,CV_8UC1);
printf("cc");
imwrite("output.bmp", dest);
}
