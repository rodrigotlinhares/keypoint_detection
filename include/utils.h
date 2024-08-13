#ifndef UTILS_H_
#define UTILS_H_

#include <cv.h>
#include "config.h"

class Utils {
public:
  static void drawContours(cv::Mat image, std::vector<std::vector<cv::Point> > contours,
                           cv::Scalar color);
  static std::string toUpper(std::string s);
};

#endif
