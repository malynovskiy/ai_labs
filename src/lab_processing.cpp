#include "lab_processing.h"

#include <opencv2/opencv.hpp>

size_t pointsCounter = 4;
extern bool isSelectPointsAllowed;

cv::Mat src;
cv::Mat originalSrc;
cv::Mat graySrc;
cv::Mat circlesDetectionSrc;
cv::Mat contoursDetectionSrc;

cv::RotatedRect box;
std::vector<cv::Point> transformPoints(4);

const int histWidth = 256;
const int histHeight = 64;

void init_resources()
{
	// images loading
	originalSrc = cv::imread("resources/images/laptop.jpg", cv::IMREAD_COLOR);
	circlesDetectionSrc = cv::imread("resources/images/medals.jpg", cv::IMREAD_COLOR);
	contoursDetectionSrc = cv::imread("resources/images/capu.jpg", cv::IMREAD_COLOR);

	if (originalSrc.empty() || circlesDetectionSrc.empty() || contoursDetectionSrc.empty())
	{
		std::cout << "Couldn't load image!" << std::endl;
		exit(-1);
	}

	// lab2 and lab3 images init
	cv::resize(originalSrc, originalSrc, cv::Size(), 0.6, 0.6);
	cv::cvtColor(originalSrc, graySrc, cv::COLOR_BGR2GRAY);
	originalSrc.copyTo(src);

	// lab4 image init
	cv::resize(circlesDetectionSrc, circlesDetectionSrc, cv::Size(), 0.8, 0.8);

	// lab5 image init 
	resize(contoursDetectionSrc, contoursDetectionSrc, cv::Size(), 0.7, 0.7);
}

void imageCallback(int event, int x, int y, int flags, void* userData)
{
	if (event == cv::EVENT_LBUTTONDOWN && pointsCounter >= 1 && isSelectPointsAllowed)
	{
		std::cout << "point[" << pointsCounter << "] at: " << x << ", " << y << '\n';

		cv::circle(src, cv::Point(x, y), 4, cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_8);
		transformPoints[pointsCounter - 1] = cv::Point(x, y);

		cv::imshow("Image", src);

		pointsCounter--;
	}
}

cv::Mat transformArea(const cv::Mat& originalSrc, const cv::Mat& src, std::vector<cv::Point>& transformationPoints, cv::RotatedRect& transformationBox)
{
	transformationBox = cv::minAreaRect(cv::Mat(transformationPoints));

	cv::Point2f pts[4];
	transformationBox.points(pts);

	const cv::Point* point = &transformationPoints[0];
	int n = (int)transformationPoints.size();
	cv::polylines(src, &point, &n, 1, true, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
	cv::imshow("Image", src);

	cv::Point2f src_vertices[4];
	src_vertices[0] = transformationPoints[0];
	src_vertices[1] = transformationPoints[1];
	src_vertices[2] = transformationPoints[2];
	src_vertices[3] = transformationPoints[3];

	cv::Point2f dst_vertices[4];
	dst_vertices[2] = cv::Point(0, 0);
	dst_vertices[3] = cv::Point(0, transformationBox.boundingRect().height - 1);
	dst_vertices[0] = cv::Point(transformationBox.boundingRect().width - 1, transformationBox.boundingRect().height - 1);
	dst_vertices[1] = cv::Point(transformationBox.boundingRect().width - 1, 0);

	cv::Mat warpMatrix = getPerspectiveTransform(src_vertices, dst_vertices);

	cv::Mat rotated;

	cv::Size size(transformationBox.boundingRect().width, transformationBox.boundingRect().height);
	warpPerspective(originalSrc, rotated, warpMatrix, size, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

	return rotated;
}

cv::Mat erosion(const cv::Mat& src, unsigned erosion_size, cv::MorphShapes morp_shape)
{
	cv::Mat erosed;
	cv::Mat element = cv::getStructuringElement(morp_shape,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));
	cv::erode(src, erosed, element);

	return erosed;
}

cv::Mat dilatation(const cv::Mat& src, unsigned dilatation_size, cv::MorphShapes morp_shape)
{
	cv::Mat dilated;
	cv::Mat element = cv::getStructuringElement(morp_shape,
		cv::Size(2 * dilatation_size + 1, 2 * dilatation_size + 1),
		cv::Point(dilatation_size, dilatation_size));
	cv::dilate(src, dilated, element);

	return dilated;
}

// custom function that create histogram of given img
cv::Mat getHistImg(const cv::Mat& img, float scaleX, float scaleY)
{
	std::vector<int> histData(histWidth, 0);

	// algorithm that calculate histogram
	for (int y = 0, h = img.rows; y < h; ++y)
	{
		for (int x = 0, w = img.cols; x < w; ++x)
		{
			int color = img.at<uchar>(y, x);
			histData[color]++;
		}
	}

	cv::Mat histogram = cv::Mat(cv::Size(histWidth * scaleX, histHeight * scaleY), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
	int histMax = *(std::max_element(histData.begin(), histData.end()));

	for (int i = 0; i < 255; ++i)
	{
		int currVal = histData[i];
		int nextVal = histData[i + 1];

		cv::Point p1 = cv::Point(i * scaleX, histHeight * scaleY);
		cv::Point p2 = cv::Point(i * scaleX + scaleX, histHeight * scaleY);
		cv::Point p3 = cv::Point(i * scaleX + scaleX, (histHeight - nextVal * histHeight / histMax) * scaleY);
		cv::Point p4 = cv::Point(i * scaleX, (histHeight - currVal * histHeight / histMax) * scaleY);

		cv::Point points[] = { p1, p2, p3, p4, p1 };
		cv::fillConvexPoly(histogram, points, 5, cv::Scalar(255, 255, 255));
	}
	return histogram;
}

cv::Mat getOpencvHistImg(const cv::Mat& img, float scaleX, float scaleY)
{
	float range[] = { 0, histWidth };
	const float* histRange = { range };

	cv::Mat hist;
	cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histWidth, &histRange);

	cv::Mat histImage = cv::Mat(cv::Size(histWidth * scaleX, histHeight * scaleY), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));

	double histMax;
	cv::minMaxLoc(hist, 0, &histMax);

	for (int i = 0; i < 255; ++i)
	{
		float currVal = hist.at<float>(i);
		float nextVal = hist.at<float>(i + 1);

		cv::Point p1 = cv::Point(i * scaleX, histHeight * scaleY);
		cv::Point p2 = cv::Point(i * scaleX + scaleX, histHeight * scaleY);
		cv::Point p3 = cv::Point(i * scaleX + scaleX, (histHeight - nextVal * histHeight / histMax) * scaleY);
		cv::Point p4 = cv::Point(i * scaleX, (histHeight - currVal * histHeight / histMax) * scaleY);

		cv::Point points[] = { p1, p2, p3, p4, p1 };
		cv::fillConvexPoly(histImage, points, 5, cv::Scalar(255, 255, 255));
	}
	return histImage;
}

void normalizeImg(const cv::Mat& img, cv::Mat& norm)
{
	img.copyTo(norm);

	double imgMax, imgMin;
	cv::minMaxLoc(norm, &imgMin, &imgMax);

	for (int y = 0, h = norm.rows; y < h; ++y)
		for (int x = 0, w = norm.cols; x < w; ++x)
			norm.at<uchar>(y, x) = 255 * ((norm.at<uchar>(y, x) - imgMin) / (imgMax - imgMin));
}

cv::Mat circlesDetection(const cv::Mat& src)
{
	cv::Mat src_gray, result;
	src.copyTo(result);

	cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(src_gray, src_gray, cv::Size(3, 3), 0, 0);

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(src_gray, circles, cv::HOUGH_GRADIENT, 1, src_gray.rows / 16, 100, 30, 1, 30);
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Vec3i c = circles[i];
		cv::Point center = cv::Point(c[0], c[1]);
		// circle center
		circle(result, center, 1, cv::Scalar(0, 100, 100), 2, cv::LINE_AA);
		// circle outline
		int radius = c[2];
		circle(result, center, radius, cv::Scalar(255, 0, 255), 2, cv::LINE_AA);
	}
	return result;
}

cv::Mat SobelContourSelection(const cv::Mat& src)
{
	cv::Mat imgDx, imgDy;
	cv::Sobel(src, imgDx, CV_32F, 1, 0, 3, 1.0 / 255.0);
	cv::Sobel(src, imgDy, CV_32F, 0, 1, 3, 1.0 / 255.0);

	cv::cvtColor(imgDx, imgDx, cv::COLOR_BGR2GRAY);
	cv::cvtColor(imgDy, imgDy, cv::COLOR_BGR2GRAY);

	cv::pow(imgDx, 2, imgDx);
	cv::pow(imgDy, 2, imgDy);

	cv::Mat combinedImg = imgDx + imgDy;
	cv::sqrt(combinedImg, combinedImg);

	cv::Mat contour;
	cv::threshold(combinedImg, contour, 0.38, 1.0, cv::THRESH_BINARY);

	return contour;
}

cv::Mat CannyThreshold(const cv::Mat& src)
{
	cv::Mat imageGray, edges;
	cv::cvtColor(src, imageGray, cv::COLOR_RGB2GRAY);
	cv::Canny(imageGray, edges, 75, 150);

	return edges;
}

cv::Mat traceContour(const cv::Mat& src, const cv::Mat& edges)
{
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(edges, contours, cv::RETR_LIST, cv::CHAIN_APPROX_TC89_L1);
	cv::Mat draw = src.clone();
	cv::drawContours(draw, contours, -1, cv::Scalar(255, 0, 255));

	return draw;
}
