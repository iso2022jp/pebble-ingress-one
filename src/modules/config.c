/* This software is released under the MIT License, see LICENSE */

#include <pebble.h>
#include "modules/config.h"

#define PERSIST_SETTINGS_KEY	0

static Config m_config = {
	
	// 	.backgroundColor = GColorBlack,
	// 	.foregroundColor = GColorWhite,
	.showSecondHand = 1,
	// .secondHandColor = GColorRed,
	.detectedTimeZoneOffset = -9 * 60 * 60, // JST
	
	.showCyclePanel = 1,
	// .checkpointColor = GColorTiffanyBlue,
	._reserved1 = 1,
	._reserved2 = 1,
	
	.showStatusPanel = 1,
	// .powerReserveColor = GColorLimerick,
	._reserved4 = 1,
	._reserved5 = 1,
	
	.showSubclock = 1,
	._reserved6 = 1,
	._reserved7 = 1,
	._reserved8 = 1,
	.subclockTimeZoneOffset = 0, // UTC
	
	//.showSecondOnTap = 1,
	
	// 	.vibeOnCheckpoint = "",
	// 	.vibeOnCycle = "",
};

static ConfigChangedHandler m_handler = NULL;


static uint32_t compute_max_size() {
	return dict_calc_buffer_size(
		19,
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t),
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), 
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), 
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t),
		sizeof (int32_t)
	);	
}

static void on_received(DictionaryIterator *iterator, void *context) {

	bool anyChanged = false;

	for (Tuple *t = dict_read_first(iterator); t; t = dict_read_next(iterator)) {

		// General
		if (t->key == MESSAGE_KEY_BackgroundColor) {
			m_config.backgroundColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_ForegroundColor) {
			m_config.foregroundColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_SecondHandColor) {
			m_config.secondHandColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		}

		// Cycle panel
		else if (t->key == MESSAGE_KEY_ShowCyclePanel) {
			m_config.showCyclePanel = t->value->int32;
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_CheckpointColor) {
			m_config.checkpointColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		}

		// Status panel
		else if (t->key == MESSAGE_KEY_ShowStatusPanel) {
			m_config.showStatusPanel = t->value->int32;
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_PowerReserveColor) {
			m_config.powerReserveColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		}

		// Sub clock
		else if (t->key == MESSAGE_KEY_ShowSubclock) {
			m_config.showSubclock = t->value->int32;
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_SubclockTimeZoneOffset) {
			m_config.subclockTimeZoneOffset = t->value->int32;
			anyChanged = true;
		}

		// Special treatment
		else if (t->key == MESSAGE_KEY_DetectedTimeZoneOffset) {
			m_config.detectedTimeZoneOffset = t->value->int32;
			anyChanged = true;
		}

		// Power Saving
		else if (t->key == MESSAGE_KEY_ShowSecondHand) {
			m_config.showSecondHand = t->value->int32;
			anyChanged = true;
// 		} else if (t->key == MESSAGE_KEY_ShowSecondOnTap) {
// 			m_config.showSecondOnTap = t->value->int32;
// 			anyChanged = true;
		}


	}

	if (anyChanged) {
		m_handler(&m_config);
	}

}

//
// Module
//

void config_init(ConfigChangedHandler handler) {

	// set defaults
	m_config.backgroundColor = GColorBlack;
	m_config.foregroundColor = GColorWhite;
	m_config.secondHandColor = GColorRed;
	m_config.checkpointColor = GColorTiffanyBlue;
	m_config.powerReserveColor = GColorLimerick;

	// load
	persist_read_data(PERSIST_SETTINGS_KEY, &m_config, sizeof m_config);
	
	// backward compatibility
	if (!(m_config.secondHandColor.argb & 0x7f)) {
		m_config.secondHandColor = GColorRed;
	}
	
	m_handler = handler;

	// start message
	{
		app_message_register_inbox_received(on_received);
		app_message_open(compute_max_size(), dict_calc_buffer_size(0));
	}

}

void config_deinit(void) {

	// stop messages
	app_message_deregister_callbacks();

	// backward compatibility
	persist_delete(MESSAGE_KEY_BackgroundColor);
	persist_delete(MESSAGE_KEY_ForegroundColor);
	persist_delete(MESSAGE_KEY_ShowSecondHand);
	persist_delete(MESSAGE_KEY_SecondHandColor);
	persist_delete(MESSAGE_KEY_DetectedTimeZoneOffset);

	// save
	persist_write_data(PERSIST_SETTINGS_KEY, &m_config, sizeof m_config);

}	


const Config *config_get(void) {
	return &m_config;
}
