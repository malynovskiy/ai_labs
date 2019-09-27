#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

constexpr unsigned max_lenght = 30;

int main(int argc, char** argv)
{
	std::string picture;
	if (argc != 2)
		picture = "picture.jpg";
	else
		picture = argv[1];


	cv::Mat image = cv::imread(picture, cv::IMREAD_COLOR);

	if (image.empty())
	{
		std::cout << "Some error, couldn't read the file!" << std::endl;
		return -1;
	}

	cv::Mat resizedImg;
	cv::resize(image, resizedImg, cv::Size(), 0.3, 0.3, cv::INTER_AREA);
	
	cv::Mat gaussianBlur;
	for (int i = 51; i > 1; i -= 2)
	{
		cv::GaussianBlur(resizedImg, gaussianBlur, cv::Size(i, i), 0, 0);

		cv::imshow("Gaussian BLURRRRR!", gaussianBlur);

		cv::waitKey(10);
	}
	cv::imshow("Gaussian BLURRRRR!", resizedImg);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}