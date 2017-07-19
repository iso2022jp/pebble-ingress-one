/* This software is released under the MIT License, see LICENSE */

#include <pebble.h>
#include "./config.h"

#define PERSIST_SETTINGS_KEY	0

// Application settings with defaults
static Config m_config = {
	
	// 	.backgroundColor = GColorBlack,
	// 	.foregroundColor = GColorWhite,
	.showSecondHand = 1,
	// .secondHandColor = GColorRed,
	.detectedTimeZoneOffset = -9 * 60 * 60, // JST
	
	.showCyclePanel = 1,
	// .checkpointColor = GColorTiffanyBlue,
	// .locationMarkerColor = GColorYellow
	// .locationMarkerBorderColor = GColorChromeYellow,
	
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

// Callback
static ConfigChangedHandler m_handler = NULL;

static uint32_t compute_max_size() {
	// FIXME: ugly
	return dict_calc_buffer_size(
		19,
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t),
		sizeof (int32_t),
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), 
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), 
		sizeof (int32_t), sizeof (int32_t), sizeof (int32_t), sizeof (int32_t),
		sizeof (int32_t)
	);	
}

// Handle incomming messages
static void on_received(DictionaryIterator *iterator, void *context) {

	bool anyChanged = false;

	for (Tuple *t = dict_read_first(iterator); t; t = dict_read_next(iterator)) {

		// Appearance
		if (t->key == MESSAGE_KEY_BackgroundColor) {
			m_config.backgroundColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_ForegroundColor) {
			m_config.foregroundColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_SecondHandColor) {
			m_config.secondHandColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_LocationMarkerColor) {
			m_config.locationMarkerColor = GColorFromHEX(t->value->int32);
			anyChanged = true;
		} else if (t->key == MESSAGE_KEY_LocationMarkerBorderColor) {
			m_config.locationMarkerBorderColor = GColorFromHEX(t->value->int32);
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

		// Power Saving
		else if (t->key == MESSAGE_KEY_ShowSecondHand) {
			m_config.showSecondHand = t->value->int32;
			anyChanged = true;
// 		} else if (t->key == MESSAGE_KEY_ShowSecondOnTap) {
// 			m_config.showSecondOnTap = t->value->int32;
// 			anyChanged = true;
		}

		// Special treatment
		else if (t->key == MESSAGE_KEY_DetectedTimeZoneOffset) {
			m_config.detectedTimeZoneOffset = t->value->int32;
			anyChanged = true;
		}

	}

	if (anyChanged) {
		m_handler(&m_config);
	}

}

static void upgrade() {
		
	// bool to GColor
	if (!(m_config.locationMarkerColor.argb & 0x80)) {
		m_config.secondHandColor = GColorRed;
	}

	// reserved to GColor
	if (!(m_config.locationMarkerColor.argb & 0x80)) {
		m_config.locationMarkerColor = GColorYellow;
	}
	if (!(m_config.locationMarkerBorderColor.argb & 0x80)) {
		m_config.locationMarkerBorderColor = GColorChromeYellow;
	}

}

//
// Module
//

void config_init(ConfigChangedHandler handler) {

	// Set defaults for non constants
	m_config.backgroundColor = GColorBlack;
	m_config.foregroundColor = GColorWhite;
	m_config.secondHandColor = GColorRed;
	m_config.checkpointColor = GColorTiffanyBlue;
	m_config.powerReserveColor = GColorLimerick;
	m_config.locationMarkerColor = GColorYellow;
	m_config.locationMarkerBorderColor = GColorChromeYellow;

	// Load state
	persist_read_data(PERSIST_SETTINGS_KEY, &m_config, sizeof m_config);
	
	// Upgrade old settings
	upgrade();
	
	m_handler = handler;

	// Start message
	{
		app_message_register_inbox_received(on_received);
		app_message_open(compute_max_size(), dict_calc_buffer_size(0));
	}

}

void config_deinit(void) {

	// stop messages
	app_message_deregister_callbacks();

	// purge old settings
	{
		persist_delete(MESSAGE_KEY_BackgroundColor);
		persist_delete(MESSAGE_KEY_ForegroundColor);
		persist_delete(MESSAGE_KEY_ShowSecondHand);
		persist_delete(MESSAGE_KEY_SecondHandColor);
		persist_delete(MESSAGE_KEY_DetectedTimeZoneOffset);
	}

	// Save state
	persist_write_data(PERSIST_SETTINGS_KEY, &m_config, sizeof m_config);

}	

const Config *config_get(void) {
	return &m_config;
}
