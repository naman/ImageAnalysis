/*
 * question4.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: Naman, , Srishti
 *
 *
 *
 *
 *  Class 1: Less than 750 is similar!
 *  Class 2: Otherwise, different!
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include <core/mat.hpp>
#include <dirent.h>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "../../helpers/helpers.cpp"

using namespace std;
using namespace cv;

int main() {

  string dirName = "../../sampleimages/ForQ3andQ4/FaceImages/";
  Mat image1 = imread("../../sampleimages/ForQ3andQ4/FaceImages/1_1.jpg",
      IMREAD_COLOR);

  vector<double> v;
  DIR *dir;
  dir = opendir(dirName.c_str());
  string imgName;
  struct dirent *ent;

  double score;
  Mat i1 = LBP_PatternImage(image1);

  while ((ent = readdir(dir)) != NULL) {
    imgName = ent->d_name;
    if (imgName.compare(".") != 0 && imgName.compare("..") != 0) {
      string aux;
      aux.append(dirName);
      aux.append(imgName);

      Mat image = imread(aux, IMREAD_COLOR);
      double score = HOG_distance(image1, image);

      cout << "Cosine Distance: " << score << endl;
      v.push_back(score);

      imshow("Template", image1);
      imshow("Pattern Image", i1);
      imshow("Query Sample", image);
      waitKey(0);
    }
  }
  closedir(dir);

  auto result = min_element(begin(v), end(v));
  if (end(v) != result)
    cout << "Best Match: " << *result << endl;

  /*
   Mat img1 = imread("../../sampleimages/lena_color_256.tif", IMREAD_GRAYSCALE);
   Mat img2 = imread("../../sampleimages/lena_color_256.tif", IMREAD_GRAYSCALE);
   */

  return 0;
}
