#pragma once
#include <stdint.h>
#include <string>
#include "qualifiers.h"

namespace ragii { namespace mp4 {

	struct BaseDescriptor;
	struct DecoderConfigDescriptor;
	struct DecoderSpecificInfo;
	struct ProfileLevelIndicationIndexDescriptor;
	struct SLConfigDescriptor;
	struct IPI_DescrPointer;
	struct IP_IdentificationDataSet;
	struct IPMP_DescriptorPointer;
	struct OCI_Descriptor;
	struct QoS_Descriptor;
	struct LanguageDescriptor;
	struct RegistrationDescriptor;
	struct ExtensionDescriptor;

	//----------------------------------------------------------------------------
	// descriptors
	//----------------------------------------------------------------------------

	struct BaseDescriptor
	{
		DescriptorTag m_Tag;
		virtual ~BaseDescriptor() {}
	};

	struct DecoderSpecificInfo : public BaseDescriptor
	{
		DecoderSpecificInfo() {
			m_Tag = DescriptorTag::DecSpecificInfoTag;
		}
	};

	struct ProfileLevelIndicationIndexDescriptor : public BaseDescriptor
	{
		uint8_t m_ProfileLevelIndicationIndex;

		ProfileLevelIndicationIndexDescriptor() :
			m_ProfileLevelIndicationIndex(0) {
			m_Tag = DescriptorTag::ProfileLevelIndicationIndexDescrTag;
		}
	};

	struct DecoderConfigDescriptor : public BaseDescriptor
	{
		ObjectType m_ObjectTypeIndication;
		uint8_t m_StreamType; // 6 bits
		uint8_t m_UpStream; // 1 bit
		uint8_t m_Reserved; // 1 bit
		uint32_t m_BufferSizeDB; // 24 bits
		uint32_t m_MaxBitrate;
		uint32_t m_AvgBitrate;
		DecoderSpecificInfo m_DecoderSpecificInfos[2];
		ProfileLevelIndicationIndexDescriptor m_ProfileLevelIndicationIndexDescriptors[256];

		DecoderConfigDescriptor() :
			m_ObjectTypeIndication(ObjectType::Unknown),
			m_StreamType(0),
			m_UpStream(0),
			m_Reserved(1),
			m_BufferSizeDB(0),
			m_MaxBitrate(0),
			m_AvgBitrate(0) {
			m_Tag = DescriptorTag::DecoderConfigDescrTag;
		}
	};

	struct SLConfigDescriptor : public BaseDescriptor
	{
		// TODO: members... めんどくさい

		SLConfigDescriptor() {
			m_Tag = DescriptorTag::SLConfigDescrTag;
		}
	};

	struct IPI_DescrPointer : public BaseDescriptor
	{
		uint16_t m_IPI_ES_Id;

		IPI_DescrPointer() : m_IPI_ES_Id(0) {
			m_Tag = DescriptorTag::IPI_DescrPointerTag;
		}
	};

	struct IP_IdentificationDataSet : public BaseDescriptor
	{
	};

	struct IPMP_DescriptorPointer : public BaseDescriptor
	{
		uint8_t m_IPMP_DescriptorID;
		uint16_t m_IPMP_DescriptorIDEx;// IPMP_DescriptorID == 0xff の場合のみ存在する
		uint16_t m_IPMP_ES_ID;// IPMP_DescriptorID == 0xff の場合のみ存在する

		IPMP_DescriptorPointer() :
			m_IPMP_DescriptorID(0),
			m_IPMP_DescriptorIDEx(0),
			m_IPMP_ES_ID(0) {
			m_Tag = DescriptorTag::IPMP_DescrTag;
		}
	};

	struct OCI_Descriptor : public BaseDescriptor
	{
		virtual ~OCI_Descriptor() {}
	};

	struct QoS_Descriptor : public BaseDescriptor
	{
		uint8_t m_PreDefined;
		QoS_Qualifier m_qualifiers[8];

		QoS_Descriptor() : m_PreDefined(0) {
			m_Tag = DescriptorTag::QoS_DescrTag;
		}
	};

	struct LanguageDescriptor : public OCI_Descriptor
	{
		uint32_t m_LanguageCode; // 24 bits

		LanguageDescriptor() : m_LanguageCode(0) {
			m_Tag = DescriptorTag::LanguageDescrTag;
		}
	};

	struct RegistrationDescriptor : public BaseDescriptor
	{
		uint32_t m_FormatIdentifier;
		uint8_t m_AdditionalIdentificationInfo[256] = { 0 }; // TODO: 幾つ確保すればいいのか分からない。 [sizeOfInstance-4]

		RegistrationDescriptor() :
			m_FormatIdentifier(0) {
			m_Tag = DescriptorTag::RegistrationDescrTag;
		}
	};

	struct ExtensionDescriptor : BaseDescriptor
	{
	};

	struct ESDescriptor : public BaseDescriptor
	{
		uint16_t m_ESID;
		uint8_t m_StreamDependenceFlag; // 1 bit
		uint8_t m_UrlFlag; // 1 bit
		uint8_t m_OcrStreamFlag; // 1 bit
		uint8_t m_StreamPriority; // 5 bits
		uint16_t m_DependsOnESID; // StreamDependenceFlag が 0以外 の場合のみ存在する
		uint8_t m_UrlLength; // URL_Flag が 0以外 の場合のみ存在する
		std::string m_UrlString; // URL_Flag が 0以外 の場合のみ存在する
		uint16_t m_OcrESID; // OCRstreamFlag  が 0以外 の場合のみ存在する
		DecoderConfigDescriptor m_DecConfigDescr;
		SLConfigDescriptor m_SlConfigDescr;
		IPI_DescrPointer m_IpiPtr[2];
		IP_IdentificationDataSet m_IpIDS[256];
		IPMP_DescriptorPointer m_IpmpDescrPtr[256];
		LanguageDescriptor m_LangDescr[256];
		QoS_Descriptor m_QosDescr[2];
		RegistrationDescriptor m_RegDescr[2];
		ExtensionDescriptor m_ExtDescr[256];

		ESDescriptor() {
			m_Tag = DescriptorTag::ES_DescrTag;
		}
	};

} }
