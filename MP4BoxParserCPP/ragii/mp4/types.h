#pragma once
#include <stdint.h>
#include <string>

namespace ragii { namespace mp4 {

	constexpr uint32_t fourcc(char a, char b, char c, char d)
	{
		return (a << 24) | (b << 16) | (c << 8) | d;
	}

	template<typename T>
	std::string fourcc_to_string(T value)
	{
		const char chars[] = {
			(char)((value >> 24) & 0xff),
			(char)((value >> 16) & 0xff),
			(char)((value >>  8) & 0xff),
			(char)((value >>  0) & 0xff),
			(char)NULL
		};
		return std::string(chars);
	}

	template<typename T, typename CHAR = char>
	constexpr void fourcc_to_string2(T value, CHAR str[5])
	{
		str[0] = (value >> 24) & 0xff;
		str[1] = (value >> 16) & 0xff;
		str[2] = (value >>  8) & 0xff;
		str[3] = (value >>  0) & 0xff;
		str[4] = NULL;
	}

	namespace box_types {

		constexpr uint32_t ainf = fourcc('a', 'i', 'n', 'f');
		constexpr uint32_t avcn = fourcc('a', 'v', 'c', 'n');
		constexpr uint32_t bloc = fourcc('b', 'l', 'o', 'c');
		constexpr uint32_t bpcc = fourcc('b', 'p', 'c', 'c');
		constexpr uint32_t buff = fourcc('b', 'u', 'f', 'f');
		constexpr uint32_t bxml = fourcc('b', 'x', 'm', 'l');
		constexpr uint32_t ccid = fourcc('c', 'c', 'i', 'd');
		constexpr uint32_t cdef = fourcc('c', 'd', 'e', 'f');
		constexpr uint32_t clip = fourcc('c', 'l', 'i', 'p');
		constexpr uint32_t cmap = fourcc('c', 'm', 'a', 'p');
		constexpr uint32_t co64 = fourcc('c', 'o', '6', '4');
		constexpr uint32_t coin = fourcc('c', 'o', 'i', 'n');
		constexpr uint32_t colr = fourcc('c', 'o', 'l', 'r');
		constexpr uint32_t crgn = fourcc('c', 'r', 'g', 'n');
		constexpr uint32_t crhd = fourcc('c', 'r', 'h', 'd');
		constexpr uint32_t cslg = fourcc('c', 's', 'l', 'g');
		constexpr uint32_t ctab = fourcc('c', 't', 'a', 'b');
		constexpr uint32_t ctts = fourcc('c', 't', 't', 's');
		constexpr uint32_t cvru = fourcc('c', 'v', 'r', 'u');
		constexpr uint32_t dinf = fourcc('d', 'i', 'n', 'f');
		constexpr uint32_t dref = fourcc('d', 'r', 'e', 'f');
		constexpr uint32_t dsgd = fourcc('d', 's', 'g', 'd');
		constexpr uint32_t dstg = fourcc('d', 's', 't', 'g');
		constexpr uint32_t edts = fourcc('e', 'd', 't', 's');
		constexpr uint32_t elst = fourcc('e', 'l', 's', 't');
		constexpr uint32_t emsg = fourcc('e', 'm', 's', 'g');
		constexpr uint32_t fdel = fourcc('f', 'd', 'e', 'l');
		constexpr uint32_t feci = fourcc('f', 'e', 'c', 'i');
		constexpr uint32_t fecr = fourcc('f', 'e', 'c', 'r');
		constexpr uint32_t fiin = fourcc('f', 'i', 'i', 'n');
		constexpr uint32_t fire = fourcc('f', 'i', 'r', 'e');
		constexpr uint32_t fpar = fourcc('f', 'p', 'a', 'r');
		constexpr uint32_t free = fourcc('f', 'r', 'e', 'e');
		constexpr uint32_t frma = fourcc('f', 'r', 'm', 'a');
		constexpr uint32_t ftyp = fourcc('f', 't', 'y', 'p');
		constexpr uint32_t gitn = fourcc('g', 'i', 't', 'n');
		constexpr uint32_t grpi = fourcc('g', 'r', 'p', 'i');
		constexpr uint32_t hdlr = fourcc('h', 'd', 'l', 'r');
		constexpr uint32_t hmhd = fourcc('h', 'm', 'h', 'd');
		constexpr uint32_t hpix = fourcc('h', 'p', 'i', 'x');
		constexpr uint32_t icnu = fourcc('i', 'c', 'n', 'u');
		constexpr uint32_t ID32 = fourcc('I', 'D', '3', '2');
		constexpr uint32_t idat = fourcc('i', 'd', 'a', 't');
		constexpr uint32_t ihdr = fourcc('i', 'h', 'd', 'r');
		constexpr uint32_t iinf = fourcc('i', 'i', 'n', 'f');
		constexpr uint32_t iloc = fourcc('i', 'l', 'o', 'c');
		constexpr uint32_t imap = fourcc('i', 'm', 'a', 'p');
		constexpr uint32_t imif = fourcc('i', 'm', 'i', 'f');
		constexpr uint32_t infe = fourcc('i', 'n', 'f', 'e');
		constexpr uint32_t infu = fourcc('i', 'n', 'f', 'u');
		constexpr uint32_t iods = fourcc('i', 'o', 'd', 's');
		constexpr uint32_t iphd = fourcc('i', 'p', 'h', 'd');
		constexpr uint32_t ipmc = fourcc('i', 'p', 'm', 'c');
		constexpr uint32_t ipro = fourcc('i', 'p', 'r', 'o');
		constexpr uint32_t iref = fourcc('i', 'r', 'e', 'f');
		constexpr uint32_t jP = fourcc('j', 'P', ' ', ' ');
		constexpr uint32_t jp2c = fourcc('j', 'p', '2', 'c');
		constexpr uint32_t jp2h = fourcc('j', 'p', '2', 'h');
		constexpr uint32_t jp2i = fourcc('j', 'p', '2', 'i');
		constexpr uint32_t kmat = fourcc('k', 'm', 'a', 't');
		constexpr uint32_t leva = fourcc('l', 'e', 'v', 'a');
		constexpr uint32_t load = fourcc('l', 'o', 'a', 'd');
		constexpr uint32_t lrcu = fourcc('l', 'r', 'c', 'u');
		constexpr uint32_t m7hd = fourcc('m', '7', 'h', 'd');
		constexpr uint32_t matt = fourcc('m', 'a', 't', 't');
		constexpr uint32_t mdat = fourcc('m', 'd', 'a', 't');
		constexpr uint32_t mdhd = fourcc('m', 'd', 'h', 'd');
		constexpr uint32_t mdia = fourcc('m', 'd', 'i', 'a');
		constexpr uint32_t mdri = fourcc('m', 'd', 'r', 'i');
		constexpr uint32_t meco = fourcc('m', 'e', 'c', 'o');
		constexpr uint32_t mehd = fourcc('m', 'e', 'h', 'd');
		constexpr uint32_t mere = fourcc('m', 'e', 'r', 'e');
		constexpr uint32_t meta = fourcc('m', 'e', 't', 'a');
		constexpr uint32_t mfhd = fourcc('m', 'f', 'h', 'd');
		constexpr uint32_t mfra = fourcc('m', 'f', 'r', 'a');
		constexpr uint32_t mfro = fourcc('m', 'f', 'r', 'o');
		constexpr uint32_t minf = fourcc('m', 'i', 'n', 'f');
		constexpr uint32_t mjhd = fourcc('m', 'j', 'h', 'd');
		constexpr uint32_t moof = fourcc('m', 'o', 'o', 'f');
		constexpr uint32_t moov = fourcc('m', 'o', 'o', 'v');
		constexpr uint32_t mvcg = fourcc('m', 'v', 'c', 'g');
		constexpr uint32_t mvci = fourcc('m', 'v', 'c', 'i');
		constexpr uint32_t mvex = fourcc('m', 'v', 'e', 'x');
		constexpr uint32_t mvhd = fourcc('m', 'v', 'h', 'd');
		constexpr uint32_t mvra = fourcc('m', 'v', 'r', 'a');
		constexpr uint32_t nmhd = fourcc('n', 'm', 'h', 'd');
		constexpr uint32_t ochd = fourcc('o', 'c', 'h', 'd');
		constexpr uint32_t odaf = fourcc('o', 'd', 'a', 'f');
		constexpr uint32_t odda = fourcc('o', 'd', 'd', 'a');
		constexpr uint32_t odhd = fourcc('o', 'd', 'h', 'd');
		constexpr uint32_t odhe = fourcc('o', 'd', 'h', 'e');
		constexpr uint32_t odrb = fourcc('o', 'd', 'r', 'b');
		constexpr uint32_t odrm = fourcc('o', 'd', 'r', 'm');
		constexpr uint32_t odtt = fourcc('o', 'd', 't', 't');
		constexpr uint32_t ohdr = fourcc('o', 'h', 'd', 'r');
		constexpr uint32_t padb = fourcc('p', 'a', 'd', 'b');
		constexpr uint32_t paen = fourcc('p', 'a', 'e', 'n');
		constexpr uint32_t pclr = fourcc('p', 'c', 'l', 'r');
		constexpr uint32_t pdin = fourcc('p', 'd', 'i', 'n');
		constexpr uint32_t pitm = fourcc('p', 'i', 't', 'm');
		constexpr uint32_t pnot = fourcc('p', 'n', 'o', 't');
		constexpr uint32_t prft = fourcc('p', 'r', 'f', 't');
		constexpr uint32_t pssh = fourcc('p', 's', 's', 'h');
		constexpr uint32_t res = fourcc('r', 'e', 's', ' ');
		constexpr uint32_t resc = fourcc('r', 'e', 's', 'c');
		constexpr uint32_t resd = fourcc('r', 'e', 's', 'd');
		constexpr uint32_t rinf = fourcc('r', 'i', 'n', 'f');
		constexpr uint32_t saio = fourcc('s', 'a', 'i', 'o');
		constexpr uint32_t saiz = fourcc('s', 'a', 'i', 'z');
		constexpr uint32_t sbgp = fourcc('s', 'b', 'g', 'p');
		constexpr uint32_t schi = fourcc('s', 'c', 'h', 'i');
		constexpr uint32_t schm = fourcc('s', 'c', 'h', 'm');
		constexpr uint32_t sdep = fourcc('s', 'd', 'e', 'p');
		constexpr uint32_t sdhd = fourcc('s', 'd', 'h', 'd');
		constexpr uint32_t sdtp = fourcc('s', 'd', 't', 'p');
		constexpr uint32_t sdvp = fourcc('s', 'd', 'v', 'p');
		constexpr uint32_t segr = fourcc('s', 'e', 'g', 'r');
		constexpr uint32_t senc = fourcc('s', 'e', 'n', 'c');
		constexpr uint32_t sgpd = fourcc('s', 'g', 'p', 'd');
		constexpr uint32_t sidx = fourcc('s', 'i', 'd', 'x');
		constexpr uint32_t sinf = fourcc('s', 'i', 'n', 'f');
		constexpr uint32_t skip = fourcc('s', 'k', 'i', 'p');
		constexpr uint32_t smhd = fourcc('s', 'm', 'h', 'd');
		constexpr uint32_t srmb = fourcc('s', 'r', 'm', 'b');
		constexpr uint32_t srmc = fourcc('s', 'r', 'm', 'c');
		constexpr uint32_t srpp = fourcc('s', 'r', 'p', 'p');
		constexpr uint32_t ssix = fourcc('s', 's', 'i', 'x');
		constexpr uint32_t stbl = fourcc('s', 't', 'b', 'l');
		constexpr uint32_t stco = fourcc('s', 't', 'c', 'o');
		constexpr uint32_t stdp = fourcc('s', 't', 'd', 'p');
		constexpr uint32_t sthd = fourcc('s', 't', 'h', 'd');
		constexpr uint32_t strd = fourcc('s', 't', 'r', 'd');
		constexpr uint32_t stri = fourcc('s', 't', 'r', 'i');
		constexpr uint32_t stsc = fourcc('s', 't', 's', 'c');
		constexpr uint32_t stsd = fourcc('s', 't', 's', 'd');
		constexpr uint32_t stsg = fourcc('s', 't', 's', 'g');
		constexpr uint32_t stsh = fourcc('s', 't', 's', 'h');
		constexpr uint32_t stss = fourcc('s', 't', 's', 's');
		constexpr uint32_t stsz = fourcc('s', 't', 's', 'z');
		constexpr uint32_t stts = fourcc('s', 't', 't', 's');
		constexpr uint32_t styp = fourcc('s', 't', 'y', 'p');
		constexpr uint32_t stz2 = fourcc('s', 't', 'z', '2');
		constexpr uint32_t subs = fourcc('s', 'u', 'b', 's');
		constexpr uint32_t swtc = fourcc('s', 'w', 't', 'c');
		constexpr uint32_t tfad = fourcc('t', 'f', 'a', 'd');
		constexpr uint32_t tfdt = fourcc('t', 'f', 'd', 't');
		constexpr uint32_t tfhd = fourcc('t', 'f', 'h', 'd');
		constexpr uint32_t tfma = fourcc('t', 'f', 'm', 'a');
		constexpr uint32_t tfra = fourcc('t', 'f', 'r', 'a');
		constexpr uint32_t tibr = fourcc('t', 'i', 'b', 'r');
		constexpr uint32_t tiri = fourcc('t', 'i', 'r', 'i');
		constexpr uint32_t tkhd = fourcc('t', 'k', 'h', 'd');
		constexpr uint32_t traf = fourcc('t', 'r', 'a', 'f');
		constexpr uint32_t trak = fourcc('t', 'r', 'a', 'k');
		constexpr uint32_t tref = fourcc('t', 'r', 'e', 'f');
		constexpr uint32_t trex = fourcc('t', 'r', 'e', 'x');
		constexpr uint32_t trgr = fourcc('t', 'r', 'g', 'r');
		constexpr uint32_t trik = fourcc('t', 'r', 'i', 'k');
		constexpr uint32_t trun = fourcc('t', 'r', 'u', 'n');
		constexpr uint32_t udta = fourcc('u', 'd', 't', 'a');
		constexpr uint32_t uinf = fourcc('u', 'i', 'n', 'f');
		constexpr uint32_t UITS = fourcc('U', 'I', 'T', 'S');
		constexpr uint32_t ulst = fourcc('u', 'l', 's', 't');
		constexpr uint32_t url = fourcc('u', 'r', 'l', ' ');
		constexpr uint32_t uuid = fourcc('u', 'u', 'i', 'd');
		constexpr uint32_t vmhd = fourcc('v', 'm', 'h', 'd');
		constexpr uint32_t vwdi = fourcc('v', 'w', 'd', 'i');
		constexpr uint32_t xml = fourcc('x', 'm', 'l', ' ');

		constexpr uint32_t avc1 = fourcc('a', 'v', 'c', '1');
		constexpr uint32_t mp4v = fourcc('m', 'p', '4', 'v');
		constexpr uint32_t mp4a = fourcc('m', 'p', '4', 'a');

		constexpr uint32_t esds = fourcc('e', 's', 'd', 's');
		constexpr uint32_t btrt = fourcc('b', 't', 'r', 't');
		constexpr uint32_t uri  = fourcc('u', 'r', 'i', ' ');
		constexpr uint32_t uriI = fourcc('u', 'r', 'i', 'I');
		constexpr uint32_t urim = fourcc('u', 'r', 'i', 'm');
		constexpr uint32_t pasp = fourcc('p', 'a', 's', 'p');
		constexpr uint32_t clap = fourcc('c', 'l', 'a', 'p');
		constexpr uint32_t urn  = fourcc('u', 'r', 'n', ' ');

	}

	namespace handler_types {

		constexpr uint32_t soun = fourcc('s', 'o', 'u', 'n');
		constexpr uint32_t vide = fourcc('v', 'i', 'd', 'e');
		constexpr uint32_t hint = fourcc('h', 'i', 'n', 't');
		constexpr uint32_t meta = fourcc('m', 'e', 't', 'a');
		constexpr uint32_t auxv = fourcc('a', 'u', 'x', 'v');

	}

	namespace sample_entry_codes {

		constexpr uint32_t tgvo = fourcc('3', 'g', 'v', 'o');
		constexpr uint32_t ac_3 = fourcc('a', 'c', '-', '3');
		constexpr uint32_t ac_4 = fourcc('a', 'c', '-', '4');
		constexpr uint32_t alac = fourcc('a', 'l', 'a', 'c');
		constexpr uint32_t alaw = fourcc('a', 'l', 'a', 'w');
		constexpr uint32_t avc1 = fourcc('a', 'v', 'c', '1');
		constexpr uint32_t avc2 = fourcc('a', 'v', 'c', '2');
		constexpr uint32_t avc3 = fourcc('a', 'v', 'c', '3');
		constexpr uint32_t avc4 = fourcc('a', 'v', 'c', '4');
		constexpr uint32_t avcp = fourcc('a', 'v', 'c', 'p');
		constexpr uint32_t dra1 = fourcc('d', 'r', 'a', '1');
		constexpr uint32_t drac = fourcc('d', 'r', 'a', 'c');
		constexpr uint32_t dtsc = fourcc('d', 't', 's', 'c');
		constexpr uint32_t dtse = fourcc('d', 't', 's', 'e');
		constexpr uint32_t dtsh = fourcc('d', 't', 's', 'h');
		constexpr uint32_t dtsl = fourcc('d', 't', 's', 'l');
		constexpr uint32_t dtsp = fourcc('d', 't', 's', '+'); // plus
		constexpr uint32_t dtsm = fourcc('d', 't', 's', '-'); // minus
		constexpr uint32_t dtsx = fourcc('d', 't', 's', 'x');
		constexpr uint32_t dvav = fourcc('d', 'v', 'a', 'v');
		constexpr uint32_t dvhe = fourcc('d', 'v', 'h', 'e');
		constexpr uint32_t ec_3 = fourcc('e', 'c', '-', '3');
		constexpr uint32_t enca = fourcc('e', 'n', 'c', 'a');
		constexpr uint32_t encs = fourcc('e', 'n', 'c', 's');
		constexpr uint32_t enct = fourcc('e', 'n', 'c', 't');
		constexpr uint32_t encv = fourcc('e', 'n', 'c', 'v');
		constexpr uint32_t fdp_ = fourcc('f', 'd', 'p', ' ');
		constexpr uint32_t g719 = fourcc('g', '7', '1', '9');
		constexpr uint32_t g726 = fourcc('g', '7', '2', '6');
		constexpr uint32_t hvc1 = fourcc('h', 'v', 'c', '1');
		constexpr uint32_t hev1 = fourcc('h', 'e', 'v', '1');
		constexpr uint32_t ixse = fourcc('i', 'x', 's', 'e');
		constexpr uint32_t m2ts = fourcc('m', '2', 't', 's');
		constexpr uint32_t m4ae = fourcc('m', '4', 'a', 'e');
		constexpr uint32_t mett = fourcc('m', 'e', 't', 't');
		constexpr uint32_t metx = fourcc('m', 'e', 't', 'x');
		constexpr uint32_t mha1 = fourcc('m', 'h', 'a', '1');
		constexpr uint32_t mha2 = fourcc('m', 'h', 'a', '2');
		constexpr uint32_t mjp2 = fourcc('m', 'j', 'p', '2');
		constexpr uint32_t mlix = fourcc('m', 'l', 'i', 'x');
		constexpr uint32_t mlpa = fourcc('m', 'l', 'p', 'a');
		constexpr uint32_t mp4a = fourcc('m', 'p', '4', 'a');
		constexpr uint32_t mp4s = fourcc('m', 'p', '4', 's');
		constexpr uint32_t mp4v = fourcc('m', 'p', '4', 'v');
		constexpr uint32_t mvc1 = fourcc('m', 'v', 'c', '1');
		constexpr uint32_t mvc2 = fourcc('m', 'v', 'c', '2');
		constexpr uint32_t mvc3 = fourcc('m', 'v', 'c', '3');
		constexpr uint32_t mvc4 = fourcc('m', 'v', 'c', '4');
		constexpr uint32_t oksd = fourcc('o', 'k', 's', 'd');
		constexpr uint32_t Opus = fourcc('O', 'p', 'u', 's');
		constexpr uint32_t pm2t = fourcc('p', 'm', '2', 't');
		constexpr uint32_t prtp = fourcc('p', 'r', 't', 'p');
		constexpr uint32_t raw_ = fourcc('r', 'a', 'w', ' ');
		constexpr uint32_t resv = fourcc('r', 'e', 's', 'v');
		constexpr uint32_t rm2t = fourcc('r', 'm', '2', 't');
		constexpr uint32_t rrtp = fourcc('r', 'r', 't', 'p');
		constexpr uint32_t rsrp = fourcc('r', 's', 'r', 'p');
		constexpr uint32_t rtp_ = fourcc('r', 't', 'p', ' ');
		constexpr uint32_t s263 = fourcc('s', '2', '6', '3');
		constexpr uint32_t samr = fourcc('s', 'a', 'm', 'r');
		constexpr uint32_t sawb = fourcc('s', 'a', 'w', 'b');
		constexpr uint32_t sawp = fourcc('s', 'a', 'w', 'p');
		constexpr uint32_t sevc = fourcc('s', 'e', 'v', 'c');
		constexpr uint32_t sm2t = fourcc('s', 'm', '2', 't');
		constexpr uint32_t sqcp = fourcc('s', 'q', 'c', 'p');
		constexpr uint32_t srtp = fourcc('s', 'r', 't', 'p');
		constexpr uint32_t ssmv = fourcc('s', 's', 'm', 'v');
		constexpr uint32_t stpp = fourcc('s', 't', 'p', 'p');
		constexpr uint32_t svc1 = fourcc('s', 'v', 'c', '1');
		constexpr uint32_t svc2 = fourcc('s', 'v', 'c', '2');
		constexpr uint32_t svcM = fourcc('s', 'v', 'c', 'M');
		constexpr uint32_t tc64 = fourcc('t', 'c', '6', '4');
		constexpr uint32_t tmcd = fourcc('t', 'm', 'c', 'd');
		constexpr uint32_t twos = fourcc('t', 'w', 'o', 's');
		constexpr uint32_t tx3g = fourcc('t', 'x', '3', 'g');
		constexpr uint32_t ulaw = fourcc('u', 'l', 'a', 'w');
		constexpr uint32_t urim = fourcc('u', 'r', 'i', 'm');
		constexpr uint32_t vc_1 = fourcc('v', 'c', '-', '1');
		constexpr uint32_t wvtt = fourcc('w', 'v', 't', 't');

	}

	enum class DescriptorTag {
		Forbidden = 0x00,
		ObjectDescrTag = 0x01,
		InitialObjectDescrTag = 0x02,
		ES_DescrTag = 0x03,
		DecoderConfigDescrTag = 0x04,
		DecSpecificInfoTag = 0x05,
		SLConfigDescrTag = 0x06,
		ContentIdentDescrTag = 0x07,
		SupplContentIdentDescrTag = 0x08,
		IPI_DescrPointerTag = 0x09,
		IPMP_DescrPointerTag = 0x0A,
		IPMP_DescrTag = 0x0B,
		QoS_DescrTag = 0x0C,
		RegistrationDescrTag = 0x0D,
		ES_ID_IncTag = 0x0E,
		ES_ID_RefTag = 0x0F,
		MP4_IOD_Tag = 0x10,
		MP4_OD_Tag = 0x11,
		IPL_DescrPointerRefTag = 0x12,
		ExtensionProfileLevelDescrTag = 0x13,
		ProfileLevelIndicationIndexDescrTag = 0x14,
		ReservedForIsoUsed_Min = 0x15,
		ReservedForIsoUsed_Max = 0x3F,
		ContentClassificationDescrTag = 0x40,
		KeyWordDescrTag = 0x41,
		RatingDescrTag = 0x42,
		LanguageDescrTag = 0x43,
		ShortTextualDescrTag = 0x44,
		ExpandedTextualDescrTag = 0x45,
		ContentCreatorNameDescrTag = 0x46,
		ContentCreationDateDescrTag = 0x47,
		OCICreatorNameDescrTag = 0x48,
		OCICreationDateDescrTag = 0x49,
		SmpteCameraPositionDescrTag = 0x4A,
		SegmentDescrTag = 0x4B,
		MediaTimeDescrTag = 0x4C,
		ReservedForIsoUsed_OciExtensions_Min = 0x4D,
		ReservedForIsoUsed_OciExtensions_Max = 0x5F,
		IPMP_ToolsListDescrTag = 0x60,
		IPMP_ToolTag = 0x61,
		M4MuxTimingDescrTag = 0x62,
		M4MuxCodeTableDescrTag = 0x63,
		ExtSLConfigDescrTag = 0x64,
		M4MuxBufferSizeDescrTag = 0x65,
		M4MuxIdentDescrTag = 0x66,
		DependencyPointerTag = 0x67,
		DependencyMarkerTag = 0x68,
		M4MuxChannelDescrTag = 0x69,
		ReservedForIsoUsed2_Min = 0x6A,
		ReservedForIsoUsed2_Max = 0xBF,
		UserPrivate_Min = 0xC0,
		UserPrivate_Max = 0xFE,
		Forbidden2 = 0xFF,
	};

	enum class ObjectType {
		Unknown = -1,
		Mpeg4Audio = 0x40,
	};

} }
