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
	std::list<std::string> originFiles; //���� train.txt�� �ִ� ���� �̸� ����Ʈ
	std::vector<TrainFileName> MdfdFiles; //������ ���� �̸�, ī��Ʈ ����
	std::vector<TrainFileName> originFilesInfo;//���� train.txt�� �ִ� ���Ͽ��� Ȯ���� ������ �̸��� ī��Ʈ ����
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

