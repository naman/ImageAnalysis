/*
 * question3.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: Naman, Srishti
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
 */

#include <core/mat.hpp>
#include <dirent.h>
#include <highgui.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <string>

#include "../../helpers/helpers.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

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
  if (dir != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      imgName = ent->d_name;
      if (imgName.compare(".") != 0 && imgName.compare("..") != 0) {
        string aux;
        aux.append(dirName);
        aux.append(imgName);

        Mat image = imread(aux, IMREAD_COLOR);
        Mat i2 = LBP_PatternImage(image);

        score = chi_square_distance(i1, i2);
        cout << "Score: " << score << endl;
        v.push_back(score);

        imshow("Template", image1);
        imshow("Pattern Image", i1);
        imshow("Query Sample", image);
        waitKey(0);
      }
    }
    closedir(dir);
  }

  auto result = min_element(begin(v), end(v));
  if (end(v) != result)
    cout << "Best Match: " << *result << endl;

  /*
   Mat image1 = imread("../../sampleimages/ForQ3andQ4/FaceImages/1_1.jpg",
   IMREAD_COLOR);
   Mat image2 = imread("../../sampleimages/ForQ3andQ4/FaceImages/1_2.jpg",
   IMREAD_COLOR);

   */
}
