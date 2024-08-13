#include "controller.h"

Controller::Controller() {
  state = STATE_IDLE;
//  capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280); //TODO remove
//  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1024); //TODO remove
  detectionMethod = DEFAULT_DETECTION;
  descriptionMethod = DEFAULT_DESCRIPTION;
  matchingMethod = DEFAULT_MATCHING;
}

void Controller::run() {
  char keyboardInput = 0;
  cv::namedWindow("", CV_WINDOW_NORMAL);

  while(capture.read(frame) && keyboardInput != 'q') {
    cv::Mat grayFrame;
    cvtColor(frame, grayFrame, CV_BGR2GRAY);
    switch(state) {
      case STATE_IDLE:
        cv::imshow("", frame);
        break;
      case STATE_DETECTING:
        KeyPointVector frameKeyPoints = detector.findKeyPoints(frame, detectionMethod);
        cv::Mat frameDescriptors = generator.generate(frame, frameKeyPoints, descriptionMethod);
        MatchVector matches = matcher.match(targetDescriptors, frameDescriptors, matchingMethod);

        cv::Mat result;
        drawMatches(target, targetKeyPoints, frame, frameKeyPoints, matches, result, GREEN, RED);
        if(matches.size() >= 4)
          drawHomography(target, result, targetKeyPoints, frameKeyPoints, matches);
        cv::imshow("", result);
        break;
    }
    keyboardInput = cv::waitKey(10);
    handleKeyboardInput(keyboardInput);
  }
}

void Controller::handleKeyboardInput(char input) {
  if(input == 'w') {
    target = MouseSelector::select(frame);
    targetKeyPoints = detector.findKeyPoints(target, detectionMethod);
    targetDescriptors = generator.generate(target, targetKeyPoints, descriptionMethod);

    cv::imwrite("/home/rodrigolinhares/Desktop/ferns/retin_2.png", target);

    state = STATE_DETECTING;
  }
}

void Controller::drawHomography(cv::Mat target, cv::Mat image, KeyPointVector targetKeyPoints,
                                KeyPointVector imageKeyPoints, MatchVector matches) {
  std::vector<cv::Point2f> targetPoints;
  std::vector<cv::Point2f> imagePoints;
  for(MatchVector::iterator it = matches.begin(); it != matches.end(); it++) {
    targetPoints.push_back(targetKeyPoints[it->queryIdx].pt);
    imagePoints.push_back(imageKeyPoints[it->trainIdx].pt);
  }

  cv::Mat homography = findHomography(targetPoints, imagePoints, CV_RANSAC);

  std::vector<cv::Point2f> targetCorners;
  targetCorners.push_back(cv::Point(0, 0));
  targetCorners.push_back(cv::Point(target.cols, 0));
  targetCorners.push_back(cv::Point(target.cols, target.rows));
  targetCorners.push_back(cv::Point(0, target.rows));
  std::vector<cv::Point2f> imageCorners(4);
  perspectiveTransform(targetCorners, imageCorners, homography);

  cv::Point2f targetColShift(target.cols, 0);
  line(image, imageCorners[0] + targetColShift, imageCorners[1] + targetColShift, BLUE, 4);
  line(image, imageCorners[1] + targetColShift, imageCorners[2] + targetColShift, BLUE, 4);
  line(image, imageCorners[2] + targetColShift, imageCorners[3] + targetColShift, BLUE, 4);
  line(image, imageCorners[3] + targetColShift, imageCorners[0] + targetColShift, BLUE, 4);
}

void Controller::parseArguments(int argc, char** argv) {
  struct option parameters[] = {
    {"detection",   required_argument, 0, 'd'},
    {"description", required_argument, 0, 'g'},
    {"matching",    required_argument, 0, 'm'},
    {"target",      required_argument, 0, 't'},
    {"input",       required_argument, 0, 'i'},
    {0, 0, 0, 0}
  };

  int parameter = 0;
  while(parameter != -1) {
    parameter = getopt_long(argc, argv, "d:g:m:t:i:", parameters, 0);
    switch(parameter) {
      case 'd':
        detectionMethod = optarg;
        break;
      case 'g':
        descriptionMethod = optarg;
        break;
      case 'm':
        matchingMethod = optarg;
        break;
      case 't':
        target = cv::imread(optarg, CV_LOAD_IMAGE_GRAYSCALE);
        break;
      case 'i':
        capture.open(optarg);
        break;
    }
  }

  std::cout << "Detection method: " << Utils::toUpper(detectionMethod) << std::endl;
  std::cout << "Description method: " << Utils::toUpper(descriptionMethod) << std::endl;
  std::cout << "Descriptor matching method: " << Utils::toUpper(matchingMethod) << std::endl;
}
