#include <cv.h>
#include <opencv2/nonfree/features2d.hpp> // Workaround. Without this, OpenCV can't find SURF.
#include <iostream> //TODO remove
#include "config.h"
#include "utils.h"

class Detector {
public:
  KeyPointVector findKeyPoints(cv::Mat image, std::string method);
  void runMSER(cv::Mat image);
};
