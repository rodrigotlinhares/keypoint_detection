#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <getopt.h>
#include "detector.h"
#include "descriptor_generator.h"
#include "descriptor_matcher.h"
#include "utils.h"
#include "mouse_selector.h"

#define STATE_IDLE 0
#define STATE_DETECTING 1

class Controller {
public:
  Controller();
  void parseArguments(int argc, char** argv);
  void run();

private:
  void drawHomography(cv::Mat target, cv::Mat image, KeyPointVector targetKeyPoints,
                      KeyPointVector imageKeyPoints, MatchVector matches);
  void handleKeyboardInput(char input);

  Detector detector;
  DescriptorGenerator generator;
  DescriptorMatcher matcher;
  cv::VideoCapture capture;
  cv::Mat frame, target, targetDescriptors;
  KeyPointVector targetKeyPoints;
  int state;
  std::string detectionMethod, descriptionMethod, matchingMethod;
};
