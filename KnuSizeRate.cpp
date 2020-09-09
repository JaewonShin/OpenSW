#include "KnuSizeRate.h"


ImageScale::ImageScale(){
}

ImageScale::~ImageScale(){
}


<<<<<<< HEAD
bool ImageScale::changeSize(const std::string &name)
=======
bool ImageScale::changeSize(const std::string &name, KnuFileList *pDtEditor)
>>>>>>> 108b5d793ccb1a7014a8fdf536b4313a5447356d
{
	std::ifstream readFile;	//square text파일 읽기
	float sqr[5];
	int i;

	float scale_max = 2;
	float scale_min = 0.5;
	float scale_level = 0.1;

    std::string imgName = name;
    std::string txtName = name;

	imgName += ".jpg";
    txtName += ".txt";

	readFile.open(txtName);	//square text파일 열기


	cv::Mat img = cv::imread(imgName, cv::IMREAD_COLOR);
	
	if(img.empty())
	{
		std::cout << "image open error" << std::endl;
		return 0;
	}


	//cv::imshow("class", test);
	//cv::waitKey(0);
	float scale_now = scale_min;

	cv::Mat resized_image;
	
	cv::resize(img, resized_image, cv::Size(), scale_now, scale_now, cv::INTER_CUBIC);
	cv::imwrite("asdasd.jpg", resized_image);

	//cv::imshow("resize_image", resized_image);
	//cv::waitKey(0);

	std::string new_fileName;
	std::string new_textName;

	//new_fileName = name + "_s";

	//std::cout << new_fileName << std::endl;
	int scale_percent = scale_now * 100;

	//new_fileName = new_fileName + std::to_string(scale_percent) + ".jpg";
	//std::cout << new_fileName << std::endl;

	while(scale_now < scale_max)
	{
		cv::resize(img, resized_image, cv::Size(), scale_now, scale_now, cv::INTER_CUBIC);
		
		int scale_percent = scale_now * 100;
		new_fileName = name + "_s";		//파일이름 초기화
		new_textName = name + "_s";
		new_fileName = new_fileName + std::to_string(scale_percent) + ".jpg";
		new_textName = new_textName + std::to_string(scale_percent) + ".txt";
		std::cout << "create : "  + new_fileName << std::endl;

<<<<<<< HEAD
=======
		if(!pDtEditor->saveNewFileName(new_fileName))    //새 파일명 전달

>>>>>>> 108b5d793ccb1a7014a8fdf536b4313a5447356d
		cv::imwrite(new_fileName, resized_image);  

	/////////////////////////////// 이미지 파일 생성 ////////////////////////////////////
		std::cout << "create : " + new_textName << std::endl;
<<<<<<< HEAD
=======


>>>>>>> 108b5d793ccb1a7014a8fdf536b4313a5447356d
		std::ofstream new_textFile(new_textName);		//이미지 파일 생성

		if(readFile.is_open())			//파일명 저장
		{
				while(!readFile.eof())
				{		
					//std::string str;
					//getline(readFile, str);
					for(i = 0; i < 5; i++){
						readFile >> sqr[i];
						sqr[i] *= scale_now;
						new_textFile << sqr[i] << " "; 
						std::cout << "sqr[" << i << "] =" << sqr[i] << std::endl; 
					}	

					new_textFile << std::endl;

				}
		}

	readFile.clear();
	readFile.seekg(0, std::ios::beg);
	//////////////////////////////// 텍스트 파일 생성 /////////////////////////////////////

		scale_now += scale_level;
		new_textFile.close();
	}
	

	readFile.close();




    //std::cout << imgName << std::endl;
    //std::cout << txtName << std::endl;

    return false;
}


