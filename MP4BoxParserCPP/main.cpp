#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>
#include "ragii/mp4/BoxParser.h"

using namespace ragii;
using namespace ragii::mp4;

template<typename... T>
std::string format(std::format_string<T...> fmt, T&&... args)
{
	return std::format(std::locale(""), fmt, args...);
}

int main()
{
	const auto filename = "D:\\temp\\videos\\mp4_h264_aac.mp4";
	std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);

	if (!ifs.is_open()) {
		std::cout << "open failed." << std::endl;
		return EXIT_FAILURE;
	}

	const auto filesize = std::filesystem::file_size(filename);
	std::cout << ::format("file size: {:L} bytes", filesize) << std::endl;

	BoxParser parser(&ifs);
	parser.parse();

	auto& boxes = parser.getBoxes();
	std::vector<std::shared_ptr<Box>> sortedBoxes(boxes.size());
	std::transform(boxes.begin(), boxes.end(), sortedBoxes.begin(), [](const auto& v) -> auto { return v.second; });

	std::sort(
		sortedBoxes.begin(),
		sortedBoxes.end(),
		[](const auto& lhs, const auto& rhs) -> bool { return lhs->m_Offset < rhs->m_Offset; }
	);

	for (auto& box : sortedBoxes) {
		std::cout << ::format("[box info] pos: {:L},\t\tname: {},\t\tsize: {:L} bytes", box->m_Offset, box->m_TypeName, box->m_Size) << std::endl;
	}

	ifs.close();

	return EXIT_SUCCESS;
}
