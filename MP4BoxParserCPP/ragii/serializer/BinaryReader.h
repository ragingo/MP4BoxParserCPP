#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <sstream>
#include "../util.h"

namespace ragii { namespace serializer {

	enum class SeekOrigin {
		Head,
		Current,
		Tail,
	};

	class BinaryReader
	{
	public:
		BinaryReader(std::ifstream*& stream) :
			m_IsInitialized(false),
			m_IsLittleEndian(true),
			m_Length(0),
			m_Stream(stream) {
			assert(stream);
		}

		void initialize() {
			if (m_IsInitialized) {
				return;
			}
			m_IsInitialized = true;
			seek(0, SeekOrigin::Tail);
			m_Length = position();
			seek(0, SeekOrigin::Head);
		}

		template<typename T>
		T read() {
			T value = T();
			m_Stream->read(reinterpret_cast<char*>(&value), sizeof(T));
			if (m_IsLittleEndian) {
				value = ragii::byte_swap(value);
			}
			return value;
		}

		uint8_t readUInt8() {
			return read<uint8_t>();
		}

		uint16_t readUInt16() {
			return read<uint16_t>();
		}

		uint32_t readUInt32() {
			return read<uint32_t>();
		}

		uint64_t readUInt64() {
			return read<uint64_t>();
		}

		std::vector<uint8_t> readBytes(size_t count) {
			std::vector<uint8_t> bytes(count);
			m_Stream->read(reinterpret_cast<char*>(bytes.data()), count);
			if (m_IsLittleEndian) {
				std::reverse(bytes.begin(), bytes.end());
			}
			return bytes;
		}

		std::string readString() {
			std::stringstream ss;
			char buf = 0;
			while (true) {
				m_Stream->read(&buf, 1);
				ss << buf;
				if (buf == '\0') {
					break;
				}
			}
			return ss.str();
		}

		void setEndian(bool isLittle) {
			m_IsLittleEndian = isLittle;
		}

		bool isEof() const {
			return position() >= length();
		}

		void seek(uint64_t pos, SeekOrigin origin = SeekOrigin::Head) {
			switch (origin)
			{
			case SeekOrigin::Head:
				m_Stream->seekg(pos, std::ios_base::beg);
				break;
			case SeekOrigin::Current:
				m_Stream->seekg(pos, std::ios_base::cur);
				break;
			case SeekOrigin::Tail:
				m_Stream->seekg(pos, std::ios_base::end);
				break;
			}
		}

		uint64_t position() const {
			return m_Stream->tellg();
		}

		uint64_t length() const {
			return m_Length;
		}

	private:
		bool m_IsInitialized;
		bool m_IsLittleEndian;
		uint64_t m_Length;
		std::ifstream* m_Stream;
	};

} }
