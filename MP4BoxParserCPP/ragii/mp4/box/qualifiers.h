#pragma once
#include <stdint.h>
#include "../types.h"

namespace ragii { namespace mp4 {

	struct QoS_Qualifier
	{
		uint8_t m_Tag = 0x0;
		virtual ~QoS_Qualifier() {}
	};

	struct QoS_Qualifier_MAX_DELAY : public QoS_Qualifier
	{
		uint32_t m_MAX_DELAY = 0;
		QoS_Qualifier_MAX_DELAY() {
			m_Tag = 0x01;
		}
	};

	struct QoS_Qualifier_PREF_MAX_DELAY : public QoS_Qualifier
	{
		uint32_t m_PREF_MAX_DELAY = 0;
		QoS_Qualifier_PREF_MAX_DELAY() {
			m_Tag = 0x02;
		}
	};

	struct QoS_Qualifier_LOSS_PROB : public QoS_Qualifier
	{
		uint32_t m_LOSS_PROB = 0;
		QoS_Qualifier_LOSS_PROB() {
			m_Tag = 0x03;
		}
	};

	struct QoS_Qualifier_MAX_GAP_LOSS : public QoS_Qualifier
	{
		uint32_t m_MAX_GAP_LOSS = 0;
		QoS_Qualifier_MAX_GAP_LOSS() {
			m_Tag = 0x04;
		}
	};

	struct QoS_Qualifier_MAX_AU_SIZE : public QoS_Qualifier
	{
		uint32_t m_MAX_AU_SIZE = 0;
		QoS_Qualifier_MAX_AU_SIZE() {
			m_Tag = 0x41;
		}
	};

	struct QoS_Qualifier_AVG_AU_SIZE : public QoS_Qualifier
	{
		uint32_t m_AVG_AU_SIZE = 0;
		QoS_Qualifier_AVG_AU_SIZE() {
			m_Tag = 0x42;
		}
	};

	struct QoS_Qualifier_MAX_AU_RATE : public QoS_Qualifier
	{
		uint32_t m_MAX_AU_RATE = 0;
		QoS_Qualifier_MAX_AU_RATE() {
			m_Tag = 0x43;
		}
	};

	struct QoS_Qualifier_REBUFFERING_RATIO : public QoS_Qualifier
	{
		uint32_t m_REBUFFERING_RATIO = 0;
		QoS_Qualifier_REBUFFERING_RATIO() {
			m_Tag = 0x44;
		}
	};

} }
