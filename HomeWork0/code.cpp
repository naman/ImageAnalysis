/*
 * code.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: Naman Gupta
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int add(Mat img1, Mat img2);
int adi(Mat img1, Mat img2);
int complement(Mat img1);
int div_by_const(Mat img1, int constant);
int div_by_img(Mat img1, Mat img2);
int lin_com(Mat img1, Mat img2, int lambda1, int lambda2);
int mul_by_const(Mat img1, int constant);
int mul_by_img(Mat img1, Mat img2);
int sub_from_const(int constant, Mat img1);

int main(int argc, char** argv) {
  string imageName1("..\\sampleimages\\lena_color_512.tif");
  string imageName2("..\\sampleimages\\mandril_color.tif");

  //    string imageName1(argv[1]);
  //    string imageName2([argv[2]);

  //Change the above params for diff images. (Could also use runtime args :P)
  // argv[1] is image1, argv[2]
  //    if( argc != 3)
  //      {cout << "Usage: display_image Image_1 Image_2" << endl; return -1;}

  Mat image1;
  image1 = imread(imageName1.c_str(), IMREAD_COLOR);

  Mat image2;
  image2 = imread(imageName2.c_str(), IMREAD_COLOR);

  if (image1.empty() || image2.empty()) {
    cout << "404" << endl;
    return -1;
  }
  add(image1, image2);
  adi(image1, image2);
  complement(image2);
  div_by_const(image1, 10);
  div_by_img(image1, image2);
  mul_by_const(image1, 10);
  mul_by_img(image1, image2);
  lin_com(image1, image2, 20, 18);
  sub_from_const(89, image1);

  waitKey(0);
  destroyAllWindows();
  return 0;
}

int add(Mat img1, Mat img2) {
  Size s1, s2;
  int value_B, value_G, value_R;
  s1 = img1.size();
  s2 = img2.size();
  if (!(s1.height == s2.height && s1.width == s2.width)) {
    cout << "Incompatible images for arithmetic operations" << endl;
    return -1;
  }

  Mat img3(s1.height, s1.width, CV_8UC3);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p2 = img2.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = p1->x + p2->x;
      value_G = p1->y + p2->y;
      value_R = p1->z + p2->z;

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-add.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);

  return 0;
}

int adi(Mat img1, Mat img2) {
  Size s1, s2;
  int value_B, value_G, value_R;
  s1 = img1.size();
  s2 = img2.size();
  if (!(s1.height == s2.height && s1.width == s2.width)) {
    cout << "Incompatible images for arithmetic operations" << endl;
    return -1;
  }

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p2 = img2.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = fabs(p1->x - p2->x);
      value_G = fabs(p1->y - p2->y);
      value_R = fabs(p1->z - p2->z);

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }
  imwrite("final-adi.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int complement(Mat img1) {
  Size s1;
  int value_B, value_G, value_R;
  s1 = img1.size();

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = fabs(255 - p1->x);
      value_G = fabs(255 - p1->y);
      value_R = fabs(255 - p1->z);

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-compl.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int div_by_const(Mat img1, int constant) {
  Size s1;
  double value_B, value_G, value_R;
  s1 = img1.size();

  Mat img3(s1.height, s1.width, CV_8UC3);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = (double) p1->x / constant;
      value_G = (double) p1->y / constant;
      value_R = (double) p1->z / constant;

      if (fabs((int) value_B - value_B) >= 0.5) {
        value_B = ceil(value_B);
      } else {
        value_B = floor(value_B);
      }
      if (fabs((int) value_G - value_G) >= 0.5) {
        value_G = ceil(value_G);
      } else {
        value_G = floor(value_G);
      }
      if (fabs((int) value_R - value_R) >= 0.5) {
        value_R = ceil(value_R);
      } else {
        value_R = floor(value_R);
      }

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      if (constant > value_B) {
        value_B = 1;
      }
      if (constant > value_G) {
        value_G = 1;
      }
      if (constant > value_R) {
        value_R = 1;
      }

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;

    }
  }

  imwrite("final-div_by_const.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int div_by_img(Mat img1, Mat img2) {
  Size s1, s2;
  double value_B, value_G, value_R;
  s1 = img1.size();
  s2 = img2.size();
  if (!(s1.height == s2.height && s1.width == s2.width)) {
    cout << "Incompatible images for arithmetic operations" << endl;
    return -1;
  }

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p2 = img2.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = (double) p1->x / p2->x;
      value_G = (double) p1->y / p2->y;
      value_R = (double) p1->z / p2->z;

      if (fabs((int) value_B - value_B) >= 0.5) {
        value_B = ceil(value_B);
      } else {
        value_B = floor(value_B);
      }
      if (fabs((int) value_G - value_G) >= 0.5) {
        value_G = ceil(value_G);
      } else {
        value_G = floor(value_G);
      }
      if (fabs((int) value_R - value_R) >= 0.5) {
        value_R = ceil(value_R);
      } else {
        value_R = floor(value_R);
      }

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-div_by_img.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int mul_by_const(Mat img1, int constant) {
  Size s1;
  int value_B, value_G, value_R;
  s1 = img1.size();

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = p1->x * constant;
      value_G = p1->y * constant;
      value_R = p1->z * constant;

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-mul_by_const.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int mul_by_img(Mat img1, Mat img2) {
  Size s1, s2;
  int value_B, value_G, value_R;
  s1 = img1.size();
  s2 = img2.size();
  if (!(s1.height == s2.height && s1.width == s2.width)) {
    cout << "Incompatible images for arithmetic operations" << endl;
    return -1;
  }

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {

        Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
        Point3_<uchar>* p2 = img2.ptr<Point3_<uchar> >(i, j);
        Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);

        value_B = p1->x * p2->x;
        value_G = p1->y * p2->y;
        value_R = p1->z * p2->z;

        if (value_B < 0)
          value_B = 0;
        if (value_B > 255)
          value_B = 255;
        if (value_G < 0)
          value_G = 0;
        if (value_G > 255)
          value_G = 255;
        if (value_R < 0)
          value_R = 0;
        if (value_R > 255)
          value_R = 255;

        p3->x = value_B;
        p3->y = value_G;
        p3->z = value_R;
      }

    }


  imwrite("final-mul_by_img.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int lin_com(Mat img1, Mat img2, int lambda1, int lambda2) {
  Size s1, s2;
  int value_B, value_G, value_R;
  s1 = img1.size();
  s2 = img2.size();
  if (!(s1.height == s2.height && s1.width == s2.width)) {
    cout << "Incompatible images for arithmetic operations" << endl;
    return -1;
  }

  Mat img3(s1.height, s1.width, CV_8UC3);
  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p2 = img2.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = p1->x * lambda1 + p2->x * lambda2;
      value_G = p1->y * lambda1 + p2->y * lambda2;
      value_R = p1->z * lambda1 + p2->z * lambda2;

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-lin_com.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}

int sub_from_const(int constant, Mat img1) {
  Size s1;
  int value_B, value_G, value_R;
  s1 = img1.size();

  Mat img3(s1.height, s1.width, CV_8UC3);

  for (int i = 0; i < s1.height; ++i) {
    for (int j = 0; j < s1.width; ++j) {
      Point3_<uchar>* p1 = img1.ptr<Point3_<uchar> >(i, j);
      Point3_<uchar>* p3 = img3.ptr<Point3_<uchar> >(i, j);
      value_B = fabs(constant - p1->x);
      value_G = fabs(constant - p1->y);
      value_R = fabs(constant - p1->z);

      if (value_B < 0)
        value_B = 0;
      if (value_B > 255)
        value_B = 255;
      if (value_G < 0)
        value_G = 0;
      if (value_G > 255)
        value_G = 255;
      if (value_R < 0)
        value_R = 0;
      if (value_R > 255)
        value_R = 255;

      p3->x = value_B;
      p3->y = value_G;
      p3->z = value_R;
    }
  }

  imwrite("final-sub_from_const.jpg", img3);
  namedWindow("Screen", WINDOW_AUTOSIZE);
  imshow("Screen", img3);

  waitKey(0);
  return 0;
}
