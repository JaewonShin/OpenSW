#include "KnuRotateRate.h"

KnuRotateRate::KnuRotateRate(float min_angle, float max_angle, float angle_level) {
	KnuRotateRate::min_angle = min_angle;
	KnuRotateRate::max_angle = max_angle;
	KnuRotateRate::angle_level = angle_level;
}

KnuRotateRate::~KnuRotateRate() {
}

std::string KnuRotateRate::Extension(std::string s) {
	return s.substr(s.find_last_of("."));
}

std::string KnuRotateRate::ExtensionErase(std::string s) {
	return s.substr(0, s.find_last_of("."));
}

bool KnuRotateRate::ImageRotate(cv::Mat* src, cv::Mat* dst, float degree) {
	cv::Point2d base(src->cols / 2.0, src->rows / 2.0);
	cv::Mat rot = cv::getRotationMatrix2D(base, degree, 1.0);
	cv::warpAffine(*src, *dst, rot, src->size());

	return true;
}

bool KnuRotateRate::ImageWrite(cv::Mat* src, std::string path) {
	cv::imwrite(path, *src);

	return true;
}

bool KnuRotateRate::ImageGenerate(cv::Mat* img, std::string path) {
	cv::Mat img_rotate;

	for (float j = KnuRotateRate::min_angle; j <= KnuRotateRate::max_angle; j += KnuRotateRate::angle_level) {
		if (!ImageRotate(img, &img_rotate, j)) {
			std::cout << "image " + std::to_string(j) + "Rotate Error!" << std::endl;
			return false;
		}
		if (!ImageWrite(&img_rotate, ExtensionErase(path) + "_rotate_" + std::to_string(j) + Extension(path))) {
			std::cout << "image " + ExtensionErase(path) + "_rotate_" + std::to_string(j) + Extension(path) + " Write Error!" << std::endl;
			return false;
		}
	}

	return true;
}

bool KnuRotateRate::RectRead(std::string rect_line, Rect* rect) {
	std::stringstream stream(rect_line);

	stream >> rect->num;
	stream >> rect->cx;
	stream >> rect->cy;
	stream >> rect->width;
	stream >> rect->height;

	return true;
}

bool KnuRotateRate::RectBounding(cv::Mat* img, Rect* rect, Rect* bound_rect, float angle) {
	double rX =  (rect->cx * img->cols - img->cols / 2) * cos(angle * PI / 180) + (rect->cy * img->rows - img->rows / 2) * sin(angle * PI / 180) + img->cols / 2;
	double rY = -(rect->cx * img->cols - img->cols / 2) * sin(angle * PI / 180) + (rect->cy * img->rows - img->rows / 2) * cos(angle * PI / 180) + img->rows / 2;

	cv::RotatedRect rot_rect(cv::Point(rX, rY), cv::Size(rect->width * img->cols, rect->height * img->rows), -angle);
	cv::Rect bounding_rect = rot_rect.boundingRect();

	bound_rect->num = rect->num;
	bound_rect->cx = ((float)bounding_rect.x + ((float)bounding_rect.width / 2)) / ((float)img->cols);
	bound_rect->cy = ((float)bounding_rect.y + ((float)bounding_rect.height / 2)) / ((float)img->rows);
	bound_rect->width = (float)bounding_rect.width / ((float)img->cols);
	bound_rect->height = (float)bounding_rect.height / ((float)img->rows);

	return true;
}

bool KnuRotateRate::RectGenerate(cv::Mat* img, Rect* rect, Rect* bound_rect, std::string path) {
	std::string rect_line;
	std::ifstream in;
	std::ofstream out;

	in.open(path);
	for (float j = KnuRotateRate::min_angle; j <= KnuRotateRate::max_angle; j += KnuRotateRate::angle_level) {
		out.open(ExtensionErase(path) + "_rotate_" + std::to_string(j) + ".txt");

		while (!in.eof()) {
			getline(in, rect_line);

			if (!rect_line.compare(""))
				break;

			if (!RectRead(rect_line, rect)) {
				std::cout << "RectRead Error!" << std::endl;
				return false;
			}

			if (!RectBounding(img, rect, bound_rect, j)) {
				std::cout << "RectBounding Error!" << std::endl;
				return false;
			}

			out << bound_rect->num << " " << bound_rect->cx << " " << bound_rect->cy << " " << bound_rect->width << " " << bound_rect->height << '\n';
		}
		in.clear();
		in.seekg(0, std::ios_base::beg);
		out.close();
	}
	in.close();

	return true;
}

bool KnuRotateRate::changeRotate(const std::string& path, KnuFileList* pKnuFileList) {
	std::ifstream rect_info;
	std::string rect_line;
	cv::Mat img;
	Rect rect, bound_rect;

	img = cv::imread(path, cv::IMREAD_COLOR);
	if (img.empty()) {
		std::cout << path + " imread Error!" << std::endl;
		return false;
	}

	if (!ImageGenerate(&img, path)) {
		std::cout << path + " ImageGenerate Error!" << std::endl;
		return false;
	}

	for (float j = KnuRotateRate::min_angle; j <= KnuRotateRate::max_angle; j += KnuRotateRate::angle_level) {
		if (!pKnuFileList->saveNewFileName(ExtensionErase(path) + "_rotate_" + std::to_string(j) + Extension(path))) {
			std::cout << ExtensionErase(path) + "_rotate_" + std::to_string(j) + Extension(path) + " saveNewFileName Error!" << std::endl;
			return false;
		}
	}

	rect_info.open(ExtensionErase(path) + ".txt");
	if (!rect_info.is_open()) {
		std::cout << ExtensionErase(path) + ".txt Open Error!" << std::endl;
		return false;
	}
	rect_info.close();

	if (!RectGenerate(&img, &rect, &bound_rect, ExtensionErase(path) + ".txt")) {
		std::cout << path + " RectGenerate Error!" << std::endl;
		return false;
	}

	return true;
}
