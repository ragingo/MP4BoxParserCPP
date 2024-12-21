#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <format>
#include <ranges>
#include <optional>
#include "ragii/mp4/BoxParser.h"

using namespace ragii;
using namespace ragii::mp4;

std::optional<std::uintmax_t> getFileSize(const std::filesystem::path& path) {
    auto status = std::filesystem::status(path);
    if (std::filesystem::is_regular_file(status)) {
        return std::filesystem::file_size(path);
    } else {
        std::cerr << "Error: file does not exist or is not a regular file." << std::endl;
        return std::nullopt;
    }
}

int main()
{
    const std::filesystem::path filename = "D:\\temp\\videos\\mp4_h264_aac.mp4";
    std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);

    if (!ifs.is_open()) {
        std::cerr << "open failed." << std::endl;
        return EXIT_FAILURE;
    }

    auto filesize = getFileSize(filename);
    if (!filesize) {
        return EXIT_FAILURE;
    }

    std::cout << std::format("file size: {:L} bytes", *filesize) << std::endl;

    BoxParser parser(&ifs);
    parser.parse();

    auto sortedBoxes = parser.getBoxes()
        | std::views::values
        | std::ranges::to<std::vector>();

    std::ranges::sort(sortedBoxes, {}, &Box::m_Offset);

    for (const auto& box : sortedBoxes) {
        std::cout << std::format("[box info] pos: {:L},\t\tname: {},\t\tsize: {:L} bytes", box->m_Offset, box->m_TypeName, box->m_Size) << std::endl;
    }

    return EXIT_SUCCESS;
}
