#include "descriptor_matcher.h"

MatchVector DescriptorMatcher::match(cv::Mat targetDescriptors, cv::Mat imageDescriptors,
                                     std::string method) {
  //TODO match? knnMatch? radiusMatch?
  MatchVector result;
  if(method.compare(METHOD_BRUTE_FORCE) == 0) {
    cv::BFMatcher brute; //TODO parameters
    brute.match(targetDescriptors, imageDescriptors, result);
  }

  else if(method.compare(METHOD_FLANN) == 0) {
    cv::FlannBasedMatcher flann; //TODO parameters
    flann.match(targetDescriptors, imageDescriptors, result);
  }
  return goodMatches(result);
}

MatchVector DescriptorMatcher::goodMatches(MatchVector matches) {
  double minimumDistance = DBL_MAX;
  for(MatchVector::iterator it = matches.begin(); it != matches.end(); it++)
    if(it->distance < minimumDistance)
      minimumDistance = it->distance;

  MatchVector result;
  for(MatchVector::iterator it = matches.begin(); it != matches.end(); it++)
    if(it->distance < minimumDistance * 2)
      result.push_back(*it);
  return result;
}
