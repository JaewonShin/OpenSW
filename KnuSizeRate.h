#pragma once

#include <string>
#include <list>
#include <vector>
#include <opencv2/opencv.hpp>
#include "KnuFileList.h"

#include <fstream>
#include <iostream>


class ImageScale {
	private:
	protected:
	public:
		ImageScale();
		virtual ~ImageScale();
		
<<<<<<< HEAD
		bool changeSize(const std::string &name);
=======
		bool changeSize(const std::string &name, KnuFileList *pDtEditor);
>>>>>>> 108b5d793ccb1a7014a8fdf536b4313a5447356d
};



