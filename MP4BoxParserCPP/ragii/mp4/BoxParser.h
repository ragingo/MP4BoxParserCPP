#pragma once
#include <unordered_map>
#include "box/boxes.h"
#include "../serializer/BinaryReader.h"


namespace ragii { namespace mp4 {

	class BoxParser
	{
	public:
		BoxParser(std::ifstream* stream);
		~BoxParser();

		void parse();

		decltype(auto) getBoxes() const {
			return m_Boxes;
		}

	private:
		BoxParser();

		std::shared_ptr<Box> parseBox();
		std::shared_ptr<MovieBox> parseMoov(const Box& box);
		std::shared_ptr<TrackBox> parseTrak(const Box& box);
		std::shared_ptr<MediaBox> parseMdia(const Box& box);
		std::shared_ptr<HandlerBox> parseHdlr(const Box& box);
		std::shared_ptr<MediaInformationBox> parseMinf(const Box& box);
		std::shared_ptr<SampleTableBox> parseStbl(const Box& box);
		std::shared_ptr<SampleDescriptionBox> parseStsd(const Box& box);
		std::shared_ptr<TimeToSampleBox> parseStts(const Box& box);
		std::shared_ptr<SampleToChunkBox> parseStsc(const Box& box);
		std::shared_ptr<SampleSizeBox> parseStsz(const Box& box);
		std::shared_ptr<ChunkOffsetBox> parseStco(const Box& box);

		std::shared_ptr<Mp4AudioSampleEntry> parseMp4a();
		std::shared_ptr<EsdBox> parseEsds(const Box& box);

		serializer::BinaryReader m_Reader;
		std::vector<std::shared_ptr<Box>> m_Boxes;
	};

} }
