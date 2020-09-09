#ifndef KNUROTATERATE_H
#define KNUROTATERATE_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>
#include <sstream>
#include "KnuFileList.h"

#define PI 3.1415926535897932

struct Rect {
	int num;
	float cx;
	float cy;
	float width;
	float height;
};

class KnuRotateRate {
	private:
		float min_angle;
		float max_angle;
		float angle_level;
	protected:
		std::string Extension(std::string s);
		std::string ExtensionErase(std::string s);
		bool ImageRotate(cv::Mat* src, cv::Mat* dst, float degree);
		bool ImageWrite(cv::Mat* src, std::string path);
		bool ImageGenerate(cv::Mat* img, std::string path);
		bool RectRead(std::string rect_line, Rect* rect);
		bool RectBounding(cv::Mat* img, Rect* rect, Rect* bound_rect, float angle);
		bool RectGenerate(cv::Mat* img, Rect* rect, Rect* bound_rect, std::string path);
	public:
		KnuRotateRate(float min_angle, float max_angle, float angle_level);
		virtual ~KnuRotateRate();

		bool changeRotate(const std::string& path, KnuFileList* pKnuFileList);
};

#endif
