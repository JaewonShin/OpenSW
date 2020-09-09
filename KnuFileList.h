#pragma once

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>

struct TrainFileName {
	std::string fileName;
	int		classIdx;
};

class KnuFileList {
private:
	std::list<std::string> originFiles; //원본 train.txt에 있는 파일 이름 리스트
	std::vector<TrainFileName> MdfdFiles; //수정된 파일 이름, 카운트 벡터
	std::vector<TrainFileName> originFilesInfo;//원본 train.txt에 있는 파일에서 확장자 제거한 이름과 카운트 벡터
	int save_cnt = 0;
	int count = 1;
protected:
public:
	KnuFileList();
	virtual ~KnuFileList();
	bool open(const char *dtFile);
	bool saveNewFileName(const std::string MdfdFileName);
	bool SaveFile(const char *dtFile);
	std::size_t getFileCnt();
	std::string getFileName(int);
	TrainFileName getFileInfo(int);
	TrainFileName getMdfdFileInfo(int);
	int getMdfdFileCnt();


};

