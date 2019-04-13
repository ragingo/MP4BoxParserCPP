#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>
#include "ragii/mp4/BoxParser.h"


using namespace ragii;
using namespace ragii::mp4;


template<
	typename TKey,
	typename TValue
>
static std::vector<TValue> map_to_vector(const std::unordered_multimap<TKey, TValue>& map)
{
	std::vector<TValue> ret;

	for (auto& pair : map) {
		ret.push_back(pair.second);
	}

	return ret;
}


int main()
{
	const char* filename = "D:\\temp\\videos\\mp4_h264_aac.mp4";
	std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary;
	std::ifstream ifs(filename, mode);

	if (!ifs.is_open()) {
		std::cout << "open failed." << std::endl;
		return -1;
	}

	std::cout << "opened." << std::endl;

	std::streampos end_pos = ifs.seekg(0, std::ios_base::end).tellg();
	std::cout << "file size: " << (std::streamoff)end_pos << " bytes." << std::endl;

	ifs.seekg(0, std::ios_base::beg);

	BoxParser parser(&ifs);
	parser.parse();

	auto boxes = map_to_vector<BoxType, std::shared_ptr<Box>>(parser.getBoxes());

	std::sort(boxes.begin(), boxes.end(), [](const auto& lhs, const auto& rhs)->bool { return lhs->m_Offset < rhs->m_Offset; });

	for (auto& item : boxes) {
		if (item->m_Parent) {
			//std::cout << "\t";
		}
		std::cout <<
			"[box info] pos: " << item->m_Offset <<
			",\t\tname: " << item->m_TypeName <<
			",\t\tsize: " << item->m_Size << " bytes " <<
			std::endl;
	}

	ifs.close();

	if (!ifs.is_open()) {
		std::cout << "closed." << std::endl;
	}

	return 0;
}
