#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void init_resources();

void imageCallback(int event, int x, int y, int flags, void* userData);

cv::Mat transformArea(const cv::Mat&, const cv::Mat&, std::vector<cv::Point>&, cv::RotatedRect&);
cv::Mat erosion(const cv::Mat& src, unsigned erosion_size, cv::MorphShapes morp_shape);
cv::Mat dilatation(const cv::Mat& src, unsigned dilatation_size, cv::MorphShapes morp_shape);

cv::Mat getHistImg(const cv::Mat& img, float scaleX = 2.5, float scaleY = 2.5);
cv::Mat getOpencvHistImg(const cv::Mat& img, float scaleX = 2.5, float scaleY = 2.5);
void normalizeImg(const cv::Mat& img, cv::Mat& norm);

cv::Mat circlesDetection(const cv::Mat& src);

cv::Mat SobelContourSelection(const cv::Mat& src);
cv::Mat CannyThreshold(const cv::Mat& src);
cv::Mat traceContour(const cv::Mat& src, const cv::Mat& edges);
