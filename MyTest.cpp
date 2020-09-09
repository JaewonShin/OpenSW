#include <stdio.h>
#include <string.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "../YoloDataTool/KnuFileList.h"
#include "../YoloDataTool/KnuSizeRate.h"
//#include "../YoloDataTool/KnuRotateRate.h"

int main() {

	ImageScale *pImgScale = new ImageScale();
	KnuFileList *pDtEditor = new KnuFileList();



	std::cout << "hello test" << std::endl;
	std::ifstream sqr("test.txt");


	std::string fileName;
	pDtEditor->open("train.txt");

	struct EditValue* value;

	// QT제외 임시 값으로 대체하였습니다.
	value->MinScale = 0.5;
	value->MaxScale = 1;
	value->ScaleLevel = 0.1;
	value->MinAngle = -10;
	value->MaxAngle = 10;
	value->RotateLevel = 1;




	std::string testName= "test";



    for(int i = 0; i < pDtEditor->getFileCnt(); i++) {
      fileName = pDtEditor->getFileName(i);
      std::cout << "원본 파일 이름: " << fileName << std::endl;
      std::cout << "파일 이름 : " << fileName << std::endl;
      std::cout << "파일 카운트 : " << pDtEditor->getFileInfo(i).classIdx << std::endl;
	  
	  std::cout << fileName << std::endl;

      pImgScale->changeSize(fileName, pDtEditor, value);
    }	

	std::cout << "원본 파일 개수 : " << pDtEditor->getFileCnt() << std::endl;
   	std::cout << "수정 파일 개수 : " << pDtEditor->getMdfdFileCnt() << std::endl;


   	if(pDtEditor->SaveFile("train.txt"))
      std::cout << "Save Complete" << std::endl;


   	delete pDtEditor;
	delete pImgScale;


	return 0;


}
