#include "ui.h"
#include "lab_processing.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <opencv2/opencv.hpp>

extern size_t pointsCounter;
bool isSelectPointsAllowed = false;
bool isImageDisplayed = false;

extern cv::Mat src;
extern cv::Mat originalSrc;
extern cv::Mat graySrc;
extern cv::Mat circlesDetectionSrc;
extern cv::Mat contoursDetectionSrc;

extern cv::RotatedRect box;
extern std::vector<cv::Point> transformPoints;

ImGuiWindowFlags window_flags = 0;

void set_window_flags()
{
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	//window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

static void lab2_ui()
{
	if (!ImGui::CollapsingHeader("Lab2 - Normalization, Equalization and Histograms"))
		return;

	if (ImGui::Button("Original image"))
	{
		cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Original image", graySrc);
	}
	ImGui::SameLine();
	if (ImGui::Button("Original image histogram"))
	{
		cv::Mat imageHist = getOpencvHistImg(graySrc);

		cv::namedWindow("Original image histogram", cv::WINDOW_AUTOSIZE);
		cv::imshow("Original image histogram", imageHist);
	}

	if (ImGui::Button("Normalized image"))
	{
		cv::Mat normalizedImg;
		normalizeImg(graySrc, normalizedImg);

		cv::namedWindow("Normalized image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Normalized image", normalizedImg);
	}
	ImGui::SameLine();
	if (ImGui::Button("Normalized image histogram"))
	{
		cv::Mat normalizedImg;
		normalizeImg(graySrc, normalizedImg);

		cv::Mat normalizedImgHist = getOpencvHistImg(normalizedImg);

		cv::namedWindow("Normalized image histogram", cv::WINDOW_AUTOSIZE);
		cv::imshow("Normalized image histogram", normalizedImgHist);
	}

	if (ImGui::Button("Equalized image"))
	{
		cv::Mat equalizedImg;
		cv::equalizeHist(graySrc, equalizedImg);

		cv::namedWindow("Equalized image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Equalized image", equalizedImg);
	}
	ImGui::SameLine();
	if (ImGui::Button("Equalized image histogram"))
	{
		cv::Mat equalizedImg;
		cv::equalizeHist(graySrc, equalizedImg);

		cv::Mat equalizedImgHist = getOpencvHistImg(equalizedImg);

		cv::namedWindow("Equalized image histogram", cv::WINDOW_AUTOSIZE);
		cv::imshow("Equalized image histogram", equalizedImgHist);
	}
}

static void lab3_ui()
{
	if (!ImGui::CollapsingHeader("Lab3 - Transforming and Morphological operations"))
		return;

	if (ImGui::TreeNode("Transforming"))
	{
		if (ImGui::Button("Show image"))
		{
			cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
			cv::setMouseCallback("Image", imageCallback);
			cv::imshow("Image", src);

			isImageDisplayed = true;
		}

		if (isImageDisplayed)
		{
			ImGui::Text("Add point to transform image");
			if (ImGui::Button("Add points"))
			{
				isSelectPointsAllowed = true;
			}
			ImGui::SameLine();
			ImGui::Text("points: %d", pointsCounter);

			if (ImGui::Button("Transform area"))
			{
				cv::Mat transformedImg = transformArea(originalSrc, src, transformPoints, box);

				cv::namedWindow("Transformed image", cv::WINDOW_AUTOSIZE);
				cv::imshow("Transformed image", transformedImg);
			}

			if (ImGui::Button("Reset points"))
			{
				originalSrc.copyTo(src);
				pointsCounter = 4;
				cv::imshow("Image", src);
			}
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Morphological operations"))
	{
		if (ImGui::Button("Show image"))
		{
			cv::namedWindow("proc image", cv::WINDOW_AUTOSIZE);
			cv::imshow("proc image", originalSrc);
		}

		ImGui::Text("Morphological operations");

		if (ImGui::Button("erosion"))
		{
			cv::Mat eroded = erosion(originalSrc, 2, cv::MORPH_RECT);

			cv::namedWindow("eroded image", cv::WINDOW_AUTOSIZE);
			cv::imshow("eroded image", eroded);
		}

		if (ImGui::Button("dilatation"))
		{
			cv::Mat dilated = dilatation(originalSrc, 2, cv::MORPH_RECT);

			cv::namedWindow("dilated image", cv::WINDOW_AUTOSIZE);
			cv::imshow("dilated image", dilated);
		}

		if (ImGui::Button("revelation"))
		{
			cv::Mat revealed = erosion(originalSrc, 2, cv::MORPH_CROSS);
			revealed = dilatation(revealed, 1, cv::MORPH_CROSS);

			cv::namedWindow("revealed image", cv::WINDOW_AUTOSIZE);
			cv::imshow("revealed image", revealed);
		}

		if (ImGui::Button("locking"))
		{
			cv::Mat locked = dilatation(originalSrc, 2, cv::MORPH_CROSS);
			locked = erosion(locked, 1, cv::MORPH_CROSS);

			cv::namedWindow("locked image", cv::WINDOW_AUTOSIZE);
			cv::imshow("locked image", locked);
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Diafilm"))
	{
		ImGui::Text("Gaussian blur processing");
		if (ImGui::Button("blur diafilm"))
		{
			cv::Mat diafilmImg;
			for (int i = 1, k = 1; i < 201; i += 2, ++k)
			{
				cv::GaussianBlur(originalSrc, diafilmImg, cv::Size(i, i), 0, 0);
				char file_name[22];

				sprintf_s(file_name, "outcomes/diafilm/image%d%d%d.bmp", i / 100, i / 10, i % 10);
				cv::imwrite(file_name, diafilmImg);
			}
		}

		ImGui::TreePop();
	}
}

static void lab4_ui()
{
	if (!ImGui::CollapsingHeader("Lab4 - Medals recognition"))
		return;

	if (ImGui::Button("Original image"))
	{
		cv::namedWindow("Medals detection", cv::WINDOW_AUTOSIZE);
		cv::imshow("Medals detection", circlesDetectionSrc);
	}

	if (ImGui::Button("Medals detection algorithm"))
	{
		cv::Mat detectedMedals = circlesDetection(circlesDetectionSrc);

		cv::namedWindow("Medals detection", cv::WINDOW_AUTOSIZE);
		cv::imshow("Medals detection", detectedMedals);
	}
}

static void lab5_ui()
{
	if (!ImGui::CollapsingHeader("Lab5 - Contours detection"))
		return;

	if (ImGui::TreeNode("Original image"))
	{
		if (ImGui::Button("Original image"))
		{
			cv::namedWindow("Contours detection", cv::WINDOW_AUTOSIZE);
			cv::imshow("Contours detection", contoursDetectionSrc);	
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Contour detection algorithms"))
	{
		if (ImGui::Button("Sobel contour selection"))
		{
			cv::Mat Sobel = SobelContourSelection(contoursDetectionSrc);
			cv::namedWindow("Sobel contour selection", cv::WINDOW_AUTOSIZE);
			cv::imshow("Sobel contour selection", Sobel);
		}

		if (ImGui::Button("Canny algorithm"))
		{
			cv::Mat Canny = CannyThreshold(contoursDetectionSrc);
			cv::namedWindow("Canny algorithm", cv::WINDOW_AUTOSIZE);
			cv::imshow("Canny algorithm", Canny);
		}

		if (ImGui::Button("Tracing contour algorithm"))
		{
			cv::Mat Canny = CannyThreshold(contoursDetectionSrc);
			cv::Mat tracedContour = traceContour(contoursDetectionSrc, Canny);

			cv::namedWindow("Tracing contour algorithm", cv::WINDOW_AUTOSIZE);
			cv::imshow("Tracing contour algorithm", tracedContour);
		}
		ImGui::TreePop();
	}	
}

void draw_ui()
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

	if (!ImGui::Begin("AI", 0, window_flags))
	{
		ImGui::End();
		return;
	}

	lab2_ui();
	lab3_ui();
	lab4_ui();
	lab5_ui();

	ImGui::Separator();

	if (ImGui::Button("Close all windows"))
	{
		cv::destroyAllWindows();
	}

	ImGui::End();
}