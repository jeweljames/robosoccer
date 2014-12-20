/*
 * pose_est.cpp
 *
 *  Created on: 18-Sep-2014
 *      Author: Jewel James
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;
  double t = (double)getTickCount();     //start time

  /// Read the image

  VideoCapture cap(0);
  // Check if we can use this device at all:
  if (!cap.isOpened()) {
    cerr << "Capture Device ID cannot be opened." << endl;
    return -1;
  }



  //for(;;)

{
  src=imread("../data/iph.jpg", 1);

/*  cap>>src;


   namedWindow( "Hough Circle Transform Demo", WINDOW_AUTOSIZE );
    imshow( "Hough Circle Transform Demo", src );
    waitKey(0);*/
  /// Convert it to gray
  //cvtColor( src, src_gray, CV_BGR2GRAY );
  cvtColor(src, src_gray, COLOR_BGR2GRAY);

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
  namedWindow( "blurred", WINDOW_NORMAL );
  imshow( "blurred", src_gray );
cvWaitKey(1000);
  //erode( src_gray,src_gray, Mat());
  //dilate( src_gray,src_gray, Mat());
  Canny(src_gray,src_gray, 250.0,255.0 );
  namedWindow( "canny", WINDOW_NORMAL );
  imshow( "canny", src_gray );


GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

namedWindow( "eroded", WINDOW_NORMAL );
  imshow( "eroded",src_gray );
  cvWaitKey(1000);
  //GaussianBlur( src_gray, src_gray, Size(3, 3), 5, 5 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  //HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

  HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100 );
  Point indi[2];


  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      indi[i] = Point(cvRound(circles[i][0]), cvRound(circles[i][1]));

      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, indi[i], 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, indi[i], radius, Scalar(0,0,255), 3, 8, 0 );
   }

Point centroid;
centroid.x = (indi[0].x+indi[1].x+indi[2].x)/3;
centroid.y = (indi[0].y+indi[1].y+indi[2].y)/3;
circle(src, centroid , 3 , Scalar(0,255,0),-1,8,0);

double theta = atan((double)(-centroid.y + indi[0].y)/(centroid.x - indi[0].x)) ;
double theta_degree = theta*180/M_PI;

if (indi[0].x>centroid.x&&indi[0].y<centroid.y)
 {
 //nothing happens here,dumbo !
 }
else if (indi[0].x<centroid.x&&indi[0].y<centroid.y)
 {
  theta_degree= theta_degree +180; //second quadrant
 }
else if (indi[0].x<centroid.x&&indi[0].y>centroid.y)
 {
  theta_degree=theta_degree+ 180; //third quadrant
 }
else if (indi[0].x>centroid.x&&indi[0].y>centroid.y)
{
  theta_degree=theta_degree+ 360; // fourth quadrant
}


line(src,indi[0],indi[1],Scalar( 0, 0, 0 ),2,8 );
line(src,indi[1],indi[2],Scalar( 0, 0, 0 ),2,8 );
line(src,indi[2],indi[0],Scalar( 0, 0, 0 ),2,8 );



t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t << endl;
cout << "orientation" << theta_degree << endl;

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", WINDOW_NORMAL );
  imshow( "Hough Circle Transform Demo", src );

  waitKey(0);

}
  return 0;
}
