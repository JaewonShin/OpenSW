#include "KnuFileList.h"

KnuFileList::KnuFileList() {
}

KnuFileList::~KnuFileList() {
	if (!originFiles.empty()) originFiles.clear();
}

std::size_t KnuFileList::getFileCnt() {
	return originFiles.size();
}

std::string KnuFileList::getFileName(int idx) {
	std::list<std::string>::iterator iter = originFiles.begin();
	std::advance(iter, idx);
	return  *iter;
}

TrainFileName KnuFileList::getFileInfo(int idx) {
	std::vector<TrainFileName>::iterator info = originFilesInfo.begin();
	std::advance(info, idx);
	return *info;
}
TrainFileName KnuFileList::getMdfdFileInfo(int idx) {
	std::vector<TrainFileName>::iterator info = MdfdFiles.begin();
	std::advance(info, idx);
	return *info;
}
int KnuFileList::getMdfdFileCnt() {
	return MdfdFiles.size();
}

bool KnuFileList::open(const char *dtFile) {
	originFiles.clear();

	std::ifstream openFile(dtFile);

	if (!openFile.is_open())
		return false;
	else
		std::cout << "File opened." << std::endl;

	std::string trainFileName;


	while (std::getline(openFile, trainFileName)) {
		TrainFileName FileNameList;

		originFiles.push_back(trainFileName);
		FileNameList.fileName = trainFileName;
		/*add filename with extension to originFilesInfo vector*/
		trainFileName.erase(trainFileName.end() - 4, trainFileName.end());
		move(trainFileName);

		/*add filename without extension to list*/
		originFiles.push_back(trainFileName);
		FileNameList.classIdx = original_count;
		/*add filecnt to vector*/
		originFilesInfo.push_back(FileNameList);

		original_count++;
	}

	openFile.close();

	return true;
}

bool KnuFileList::saveNewFileName(const std::string MdfdFileName) {
	TrainFileName SaveFileNames;
	SaveFileNames.fileName = MdfdFileName;
	SaveFileNames.classIdx = save_cnt;
	MdfdFiles.push_back(SaveFileNames);
	/*save new filename to MdfdFiles vector*/
	save_cnt++;
	return true;
}
bool KnuFileList::SaveFile(const char *dtFile)
{
	std::ofstream saveFile;

	saveFile.open(dtFile, std::ios::app);
	/*save information of MdfdFiles vector to train.txt*/
	if (!saveFile.is_open())
		return false;
	else
		std::cout << "Save File opened." << std::endl;
	saveFile << '\n';/

	for (int i = 0; i < getMdfdFileCnt(); i++)
		saveFile << MdfdFiles[i].fileName << '\n';

	saveFile.close();

	return true;
}