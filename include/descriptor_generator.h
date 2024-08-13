#include <cv.h>
#include <opencv2/nonfree/features2d.hpp> // Workaround. Without this, OpenCV can't find SURF.
#include "config.h"

class DescriptorGenerator {
public:
  cv::Mat generate(cv::Mat image, KeyPointVector keyPoints, std::string method);
};
