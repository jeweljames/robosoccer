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
  Mat src, src_gray,channels[3] ;
  double t = (double)getTickCount();     //start time

  /// Read the image

  VideoCapture cap(0);
  // Check if we can use this device at all:
  if (!cap.isOpened()) {
    cerr << "Capture Device ID cannot be opened." << endl;
    return -1;
  }

  src=imread("../data/circles.jpg", 1);

  split(src,channels);

  namedWindow( "ch_b", WINDOW_NORMAL );
  imshow( "ch_b", channels[0] );

  waitKey(1000);

namedWindow( "ch_g", WINDOW_NORMAL );
  imshow( "ch_g", channels[1] );

  waitKey(1000);
namedWindow( "ch_r", WINDOW_NORMAL );
  imshow( "ch_r", channels[2] );

  waitKey(1000);


  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( channels[0], channels[0], Size(9, 9), 2, 2 );
  GaussianBlur( channels[1], channels[1], Size(9, 9), 2, 2 );
  GaussianBlur( channels[2], channels[2], Size(9, 9), 2, 2 );
  GaussianBlur( channels[0], channels[0], Size(9, 9), 2, 2 );
  GaussianBlur( channels[1], channels[1], Size(9, 9), 2, 2 );
  GaussianBlur( channels[2], channels[2], Size(9, 9), 2, 2 );

  Canny(channels[0],channels[0], 250.0,255.0 );
  Canny(channels[1],channels[1], 250.0,255.0 );
  Canny(channels[2],channels[2], 250.0,255.0 );

 
  namedWindow( "ch_b", WINDOW_NORMAL );
  imshow( "ch_b", channels[0] );

  waitKey(1000);

namedWindow( "ch_g", WINDOW_NORMAL );
  imshow( "ch_g", channels[1] );

  waitKey(1000);
namedWindow( "ch_r", WINDOW_NORMAL );
  imshow( "ch_r", channels[2] );

  waitKey(1000);


 /* vector<Vec3f> circles;

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
*/
  /// Show your results
  namedWindow( "Hough Circle Transform Demo", WINDOW_NORMAL );
  imshow( "Hough Circle Transform Demo", src );

  waitKey(0);


  return 0;
}
