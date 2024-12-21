#pragma once
#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include "../types.h"
#include "qualifiers.h"
#include "descriptors.h"

namespace ragii { namespace mp4 {


	struct SampleEntry;
	struct AudioSampleEntry;
	struct Mp4AudioSampleEntry;
	struct MpegSampleEntry;

	struct Box;
	struct FullBox;
	struct MovieBox;
	struct TrackBox;
	struct MediaBox;
	struct HandlerBox;
	struct MediaInformationBox;
	struct SampleTableBox;
	struct SampleDescriptionBox;
	struct EsdBox;
	struct TimeToSampleBox;
	struct SampleToChunkBox;
	struct SampleSizeBox;
	struct ChunkOffsetBox;

	typedef uint32_t BoxType;
	typedef uint32_t HandlerType;
	typedef uint32_t SampleEntryCode;


	//----------------------------------------------------------------------------
	// funtions
	//----------------------------------------------------------------------------

	void copy_box(Box* dest, const Box* src);

	bool is_child(const Box* parent, const Box* target);


	//----------------------------------------------------------------------------
	// base boxes
	//----------------------------------------------------------------------------

	struct Box
	{
		std::string m_TypeName;
		uint32_t m_Size = 0;
		uint64_t m_LargeSize = 0;
		BoxType m_Type;
		uint64_t m_Offset = 0;
		uint64_t m_NextPos = 0;
		Box* m_Parent = nullptr;
		std::vector<std::shared_ptr<Box>> m_Children;

		Box(): m_Type(0) {}

		Box(BoxType type) :
			m_Type(type) {
		}

		Box& operator=(const Box& rhs) {
			copy_box(this, &rhs);
			return *this;
		}

		virtual ~Box() {}
	};

	struct FullBox : public Box
	{
		uint8_t m_Version = 0;
		uint32_t m_Flags = 0; // 24 bits

		FullBox(BoxType type) :
			Box(type) {
		}

		virtual ~FullBox() {}
	};


	//----------------------------------------------------------------------------
	// entries
	//----------------------------------------------------------------------------

	struct SampleEntry : public Box
	{
		uint8_t m_Reserved[6] = { 0 };
		uint16_t m_DataReferenceIndex = 0;

		SampleEntry(BoxType type) :
			Box(type) {
		}

		virtual ~SampleEntry() {}
	};

	struct AudioSampleEntry : public SampleEntry
	{
		static const int kDefaultChannellCount = 2;
		static const int kDefaultSampleSize = 16;

		uint32_t m_Reserved2[2] = { 0 };
		uint16_t m_ChannelCount = kDefaultChannellCount;
		uint16_t m_SampleSize = kDefaultSampleSize;
		uint16_t m_PreDefined = 0;
		uint16_t m_Reserved3 = 0;
		uint32_t m_SampleRate = 0;

		AudioSampleEntry(SampleEntryCode code) :
			SampleEntry(code) {
		}

		virtual ~AudioSampleEntry() {}
	};

	struct Mp4AudioSampleEntry : public AudioSampleEntry
	{
		Mp4AudioSampleEntry() : AudioSampleEntry(sample_entry_codes::mp4a) {
		}

		std::shared_ptr<EsdBox> esds; // TODO: ãKäiìIÇ…ïKÇ∏ä‹ÇÒÇ≈Ç¢ÇÈÇÃÇ©ÅH
	};

	struct MpegSampleEntry : public SampleEntry
	{
		MpegSampleEntry(SampleEntryCode code) : SampleEntry(code) {
		}
	};


	//----------------------------------------------------------------------------
	// boxes
	//----------------------------------------------------------------------------

	struct MovieBox : public Box
	{
		MovieBox() : Box(box_types::moov) {
		}

		std::shared_ptr<TrackBox> trak;
	};

	struct TrackBox : public Box
	{
		TrackBox() : Box(box_types::trak) {
		}

		std::shared_ptr<MediaBox> mdia;
	};

	struct MediaBox : public Box
	{
		MediaBox() : Box(box_types::mdia) {
		}

		std::shared_ptr<HandlerBox> hdlr;
		std::shared_ptr<MediaInformationBox> minf;
	};

	struct HandlerBox : public FullBox
	{
		uint32_t m_PreDefined = 0;
		HandlerType m_HandlerType = 0;
		uint32_t m_Reserved[3] = {0};
		std::string m_Name;

		std::string getHandlerName() const {
			return fourcc_to_string(m_HandlerType);
		}

		HandlerBox() :
			FullBox(box_types::hdlr) {
		}
	};

	struct MediaInformationBox : public Box
	{
		MediaInformationBox() : Box(box_types::minf) {
		}

		std::shared_ptr<SampleTableBox> stbl;
	};

	struct SampleTableBox : public Box
	{
		SampleTableBox() : Box(box_types::stbl) {
		}

		std::shared_ptr<SampleDescriptionBox> stsd;
		std::shared_ptr<TimeToSampleBox> stts;
		std::shared_ptr<SampleToChunkBox> stsc;
		std::shared_ptr<SampleSizeBox> stsz;
		std::shared_ptr<ChunkOffsetBox> stco;
	};

	struct SampleDescriptionBox : public FullBox
	{
		uint32_t m_EntryCount = 0;

		struct Entry {
			std::shared_ptr<SampleEntry> m_SampleEntry;
			Entry() {
			}
		};
		std::vector<Entry> m_Entries;

		SampleDescriptionBox() :
			FullBox(box_types::stsd) {
		}
	};

	struct EsdBox : public FullBox
	{
		ESDescriptor m_ES;

		EsdBox() : FullBox(box_types::esds) {
		}
	};

	struct TimeToSampleBox : public FullBox
	{
		uint32_t m_EntryCount = 0;

		struct Entry {
			uint32_t m_SampleCount = 0;
			uint32_t m_SampleDelta = 0;
			Entry() {}
		};

		std::vector<Entry> m_Entries;

		TimeToSampleBox() :
			FullBox(box_types::stts) {
		}
	};

	struct SampleToChunkBox : public FullBox
	{
		uint32_t m_EntryCount = 0;

		struct Entry
		{
			uint32_t m_FirstChunk = 0;
			uint32_t m_SamplePerChunk = 0;
			uint32_t m_SampleDescriptionIndex = 0;
			Entry() {}
		};

		std::vector<Entry> m_Entries;

		SampleToChunkBox() : FullBox(box_types::stsc) {
		}
	};

	struct SampleSizeBox : public FullBox
	{
		uint32_t m_SampleSize = 0;
		uint32_t m_SampleCount = 0;

		struct Entry
		{
			uint32_t m_Size = 0;
			Entry() {}
		};

		std::vector<Entry> m_Entries;

		SampleSizeBox() :
			FullBox(box_types::stsz) {
		}
	};

	struct ChunkOffsetBox : FullBox
	{
		uint32_t m_EntryCount = 0;

		struct Entry {
			uint32_t m_ChunkOffset = 0;
			Entry() {}
		};

		std::vector<Entry> m_Entries;

		ChunkOffsetBox() :
			FullBox(box_types::stco) {
		}
	};


} }
