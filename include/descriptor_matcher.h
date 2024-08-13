#include <cv.h>
#include "config.h"

class DescriptorMatcher {
public:
  MatchVector match(cv::Mat targetDescriptors, cv::Mat imageDescriptors, std::string method);
  MatchVector goodMatches(MatchVector matches);
};
