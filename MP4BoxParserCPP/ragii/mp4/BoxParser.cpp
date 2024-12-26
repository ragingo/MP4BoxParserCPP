#include <cassert>
#include <fstream>
#include <string>
#include "types.h"
#include "BoxParser.h"

namespace ragii { namespace mp4 {

	BoxParser::BoxParser(std::ifstream* stream) : m_Reader(stream)
	{
		assert(stream);
	}

	BoxParser::~BoxParser()
	{
	}

	void BoxParser::parse()
	{
		m_Reader.initialize();

		while (!m_Reader.isEof()) {

			auto box = parseBox();

			switch (box->m_Type)
			{
			case box_types::ftyp:
				m_Boxes.push_back(box);
				m_Reader.seek(box->m_NextPos);
				break;

			case box_types::moov:
				m_Boxes.emplace_back(parseMoov(*box));
				break;

			case box_types::mdat:
			case box_types::free:
				m_Boxes.push_back(box);
				m_Reader.seek(box->m_NextPos);
				break;

			default:
				m_Boxes.push_back(box);
				m_Reader.seek(box->m_NextPos);
				break;
			}

		}
	}

	std::shared_ptr<Box> BoxParser::parseBox()
	{
		Box box;
		box.m_Size = m_Reader.readUInt32();
		box.m_Type = m_Reader.readUInt32();

		if (box.m_Size == 1) {
			box.m_LargeSize = m_Reader.readUInt64();
			box.m_Offset = m_Reader.position() - std::streampos(4 + 4 + 8);
			box.m_NextPos = box.m_Offset + box.m_LargeSize;
		}
		else {
			box.m_Offset = m_Reader.position() - std::streampos(4 + 4);
			box.m_NextPos = box.m_Offset + box.m_Size;
		}

		return std::make_shared<Box>(box);
	}

	std::shared_ptr<MovieBox> BoxParser::parseMoov(const Box& box)
	{
		auto moov_box = std::make_shared<MovieBox>();
		copy_box(moov_box.get(), &box);

		while (!m_Reader.isEof()) {

			auto child_box = parseBox();

			if (!is_child(moov_box.get(), child_box.get())) {
				m_Reader.seek(m_Reader.position() - (4 + 4));
				break;
			}

			child_box->m_Parent = moov_box.get();

			switch (child_box->m_Type)
			{
			case box_types::mvhd:
			case box_types::iods:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::trak:
				moov_box->trak = parseTrak(*child_box);
				moov_box->m_Children.push_back(moov_box->trak);
				break;

			case box_types::udta:
				m_Reader.seek(child_box->m_NextPos);
				break;

			default:
				m_Reader.seek(child_box->m_NextPos);
				break;
			}

		}

		return moov_box;
	}

	std::shared_ptr<TrackBox> BoxParser::parseTrak(const Box& box)
	{
		auto trak_box = std::make_shared<TrackBox>();
		copy_box(trak_box.get(), &box);

		while (!m_Reader.isEof()) {

			auto child_box = parseBox();

			if (!is_child(trak_box.get(), child_box.get())) {
				m_Reader.seek(m_Reader.position() - (4 + 4));
				break;
			}

			child_box->m_Parent = trak_box.get();

			switch (child_box->m_Type)
			{
			case box_types::tkhd:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::mdia:
				trak_box->mdia = parseMdia(*child_box);
				trak_box->m_Children.push_back(trak_box->mdia);
				break;

			default:
				m_Reader.seek(child_box->m_NextPos);
				break;
			}
		}

		return trak_box;
	}

	std::shared_ptr<MediaBox> BoxParser::parseMdia(const Box& box)
	{
		auto mdia_box = std::make_shared<MediaBox>();
		copy_box(mdia_box.get(), &box);

		while (!m_Reader.isEof()) {

			auto child_box = parseBox();

			if (!is_child(mdia_box.get(), child_box.get())) {
				m_Reader.seek(m_Reader.position() - (4 + 4));
				break;
			}

			child_box->m_Parent = mdia_box.get();

			switch (child_box->m_Type)
			{
			case box_types::mdhd:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::hdlr:
				mdia_box->hdlr = parseHdlr(*child_box);
				mdia_box->m_Children.push_back(mdia_box->hdlr);
				break;

			case box_types::minf:
				mdia_box->minf = parseMinf(*child_box);
				mdia_box->m_Children.push_back(mdia_box->minf);
				break;

			default:
				m_Reader.seek(child_box->m_NextPos);
				break;
			}
		}

		return mdia_box;
	}

	std::shared_ptr<HandlerBox> BoxParser::parseHdlr(const Box& box)
	{
		auto hdlr_box = std::make_shared<HandlerBox>();
		copy_box(hdlr_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		hdlr_box->m_Version = ver_and_flags >> 24;
		hdlr_box->m_Flags = ver_and_flags & 0x00ffffff;
		hdlr_box->m_PreDefined = m_Reader.readUInt32();
		hdlr_box->m_HandlerType = m_Reader.readUInt32();
		hdlr_box->m_Reserved[0] = m_Reader.readUInt32();
		hdlr_box->m_Reserved[1] = m_Reader.readUInt32();
		hdlr_box->m_Reserved[2] = m_Reader.readUInt32();
		hdlr_box->m_Name = m_Reader.readString();

		return hdlr_box;
	}

	std::shared_ptr<MediaInformationBox> BoxParser::parseMinf(const Box& box)
	{
		auto minf_box = std::make_shared<MediaInformationBox>();
		copy_box(minf_box.get(), &box);

		while (!m_Reader.isEof()) {

			auto child_box = parseBox();

			if (!is_child(minf_box.get(), child_box.get())) {
				m_Reader.seek(m_Reader.position() - (4 + 4));
				break;
			}

			child_box->m_Parent = minf_box.get();

			switch (child_box->m_Type)
			{
			case box_types::vmhd:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::dinf:
				break;

			case box_types::dref:
				m_Reader.seek(child_box->m_NextPos);// TODO: fullbox だからとりあえず読み飛ばす(子の url にいかない)
				break;

			case box_types::url:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::stbl:
				minf_box->stbl = parseStbl(*child_box);
				minf_box->m_Children.push_back(minf_box->stbl);
				break;

			case box_types::smhd:
				m_Reader.seek(child_box->m_NextPos);
				break;

			default:
				m_Reader.seek(child_box->m_NextPos);
				break;
			}
		}

		return minf_box;
	}

	std::shared_ptr<SampleTableBox> BoxParser::parseStbl(const Box& box)
	{
		auto stbl_box = std::make_shared<SampleTableBox>();
		copy_box(stbl_box.get(), &box);

		while (!m_Reader.isEof()) {

			auto child_box = parseBox();

			if (!is_child(stbl_box.get(), child_box.get())) {
				m_Reader.seek(m_Reader.position() - (4 + 4));
				break;
			}

			child_box->m_Parent = stbl_box.get();

			switch (child_box->m_Type)
			{
			case box_types::stsd:
				stbl_box->stsd = parseStsd(*child_box);
				stbl_box->m_Children.push_back(stbl_box->stsd);
				break;

			//case box_types::stsd:
			//	m_Reader.seek(child_box->m_NextPos);// TODO: fullbox だからとりあえず読み飛ばす(子の mp4v,mp4a にいかない)
			//	break;

			//case box_types::mp4v:
			//	break;

				//case box_types::avcc:
				//	m_Reader.seek(child_box->m_NextPos);
				//	break;

			//case box_types::btrt:
			//	m_Reader.seek(child_box->m_NextPos);
			//	break;

				//case box_types::svcc:
				//	m_Reader.seek(child_box->m_NextPos);
				//	break;

			//case box_types::mp4a:
			//	break;

			//case box_types::esds:
			//	m_Reader.seek(child_box->m_NextPos);
			//	break;

			case box_types::ctts:
			case box_types::stss:
				m_Reader.seek(child_box->m_NextPos);
				break;

			case box_types::stts:
				stbl_box->stts = parseStts(*child_box);
				stbl_box->m_Children.push_back(stbl_box->stts);
				break;

			case box_types::stsc:
				stbl_box->stsc = parseStsc(*child_box);
				stbl_box->m_Children.push_back(stbl_box->stsc);
				break;

			case box_types::stsz:
				stbl_box->stsz = parseStsz(*child_box);
				stbl_box->m_Children.push_back(stbl_box->stsz);
				break;

			case box_types::stco:
				stbl_box->stco = parseStco(*child_box);
				stbl_box->m_Children.push_back(stbl_box->stco);
				break;

			default:
				m_Reader.seek(child_box->m_NextPos);
				break;
			}
		}

		return stbl_box;
	}

	std::shared_ptr<SampleDescriptionBox> BoxParser::parseStsd(const Box& box)
	{
		auto stsd_box = std::make_shared<SampleDescriptionBox>();
		copy_box(stsd_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		stsd_box->m_Version = ver_and_flags >> 24;
		stsd_box->m_Flags = ver_and_flags & 0x00ffffff;
		stsd_box->m_EntryCount = m_Reader.readUInt32();

		for (size_t i = 0; i < stsd_box->m_EntryCount; i++) {
			const MediaBox* mdia_box = static_cast<const MediaBox*>(stsd_box->m_Parent->m_Parent->m_Parent);
			const HandlerBox* hdlr_box = mdia_box->hdlr.get();
			switch (hdlr_box->m_HandlerType)
			{
			case handler_types::soun:
				{
					SampleDescriptionBox::Entry entry;
					entry.m_SampleEntry = parseMp4a();
					stsd_box->m_Entries.push_back(entry);
				}
				break;
			}
		}

		return stsd_box;
	}

	std::shared_ptr<TimeToSampleBox> BoxParser::parseStts(const Box& box)
	{
		auto stts_box = std::make_shared<TimeToSampleBox>();
		copy_box(stts_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		stts_box->m_Version = ver_and_flags >> 24;
		stts_box->m_Flags = ver_and_flags & 0x00ffffff;
		stts_box->m_EntryCount = m_Reader.readUInt32();

		for (size_t i = 0; i < stts_box->m_EntryCount; i++) {
			TimeToSampleBox::Entry entry;
			entry.m_SampleCount = m_Reader.readUInt32();
			entry.m_SampleDelta= m_Reader.readUInt32();
			stts_box->m_Entries.push_back(entry);
		}

		return stts_box;
	}

	std::shared_ptr<SampleToChunkBox> BoxParser::parseStsc(const Box& box)
	{
		auto stsc_box = std::make_shared<SampleToChunkBox>();
		copy_box(stsc_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		stsc_box->m_Version = ver_and_flags >> 24;
		stsc_box->m_Flags = ver_and_flags & 0x00ffffff;
		stsc_box->m_EntryCount = m_Reader.readUInt32();

		for (size_t i = 0; i < stsc_box->m_EntryCount; i++) {
			SampleToChunkBox::Entry entry;
			entry.m_FirstChunk = m_Reader.readUInt32();
			entry.m_SamplePerChunk = m_Reader.readUInt32();
			entry.m_SampleDescriptionIndex = m_Reader.readUInt32();
			stsc_box->m_Entries.push_back(entry);
		}

		return stsc_box;
	}

	std::shared_ptr<SampleSizeBox> BoxParser::parseStsz(const Box& box)
	{
		auto stsz_box = std::make_shared<SampleSizeBox>();
		copy_box(stsz_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		stsz_box->m_Version = ver_and_flags >> 24;
		stsz_box->m_Flags = ver_and_flags & 0x00ffffff;
		stsz_box->m_SampleSize = m_Reader.readUInt32();
		stsz_box->m_SampleCount = m_Reader.readUInt32();

		for (size_t i = 0; i < stsz_box->m_SampleCount; i++) {
			SampleSizeBox::Entry entry;
			entry.m_Size = m_Reader.readUInt32();
			stsz_box->m_Entries.push_back(entry);
		}

		return stsz_box;
	}

	std::shared_ptr<ChunkOffsetBox> BoxParser::parseStco(const Box& box)
	{
		auto stco_box = std::make_shared<ChunkOffsetBox>();
		copy_box(stco_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		stco_box->m_Version = ver_and_flags >> 24;
		stco_box->m_Flags = ver_and_flags & 0x00ffffff;
		stco_box->m_EntryCount = m_Reader.readUInt32();

		for (size_t i = 0; i < stco_box->m_EntryCount; i++) {
			ChunkOffsetBox::Entry entry;
			entry.m_ChunkOffset = m_Reader.readUInt32();
			stco_box->m_Entries.push_back(entry);
		}

		return stco_box;
	}

	std::shared_ptr<Mp4AudioSampleEntry> BoxParser::parseMp4a()
	{
		auto mp4a_entry = std::make_shared<Mp4AudioSampleEntry>();

		copy_box(mp4a_entry.get(), parseBox().get());

		mp4a_entry->m_Reserved[0] = m_Reader.readUInt8();
		mp4a_entry->m_Reserved[1] = m_Reader.readUInt8();
		mp4a_entry->m_Reserved[2] = m_Reader.readUInt8();
		mp4a_entry->m_Reserved[3] = m_Reader.readUInt8();
		mp4a_entry->m_Reserved[4] = m_Reader.readUInt8();
		mp4a_entry->m_Reserved[5] = m_Reader.readUInt8();
		mp4a_entry->m_DataReferenceIndex = m_Reader.readUInt16();
		mp4a_entry->m_Reserved2[0] = m_Reader.readUInt32();
		mp4a_entry->m_Reserved2[1] = m_Reader.readUInt32();
		mp4a_entry->m_ChannelCount = m_Reader.readUInt16();
		mp4a_entry->m_SampleSize = m_Reader.readUInt16();
		mp4a_entry->m_PreDefined = m_Reader.readUInt16();
		mp4a_entry->m_Reserved3 = m_Reader.readUInt16();
		mp4a_entry->m_SampleRate = m_Reader.readUInt32() >> 16;// 16.16 hi.lo

		mp4a_entry->esds = parseEsds(*parseBox());

		return mp4a_entry;
	}

	std::shared_ptr<EsdBox> BoxParser::parseEsds(const Box& box)
	{
		auto esds_box = std::make_shared<EsdBox>();
		copy_box(esds_box.get(), &box);

		uint32_t ver_and_flags = m_Reader.readUInt32();
		esds_box->m_Version = ver_and_flags >> 24;
		esds_box->m_Flags = ver_and_flags & 0x00ffffff;

		// TODO: 擬似的に読み取ったとする・・・
		m_Reader.seek(esds_box->m_NextPos);

		return esds_box;
	}

} }
