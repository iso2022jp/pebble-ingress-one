/* This software is released under the MIT License, see LICENSE */

module.exports = [

	{
		type: 'heading',
		defaultValue: 'Configuration',
	},

	// Appearance
	{
		type: 'section',
		capabilities: ['COLOR'],
		items: [
			{
				type: 'heading',
				defaultValue: 'Appearance',
				capabilities: ['COLOR'],
			},
			/*
			{
				type: 'toggle',
				messageKey: 'AutoTimezone',
				label: 'Auto Timezone',
				defaultValue: true
			},
			{
				type: 'color',
				messageKey: 'Timezone',
				label: 'Timezone',
				defaultValue: '000000'
			},
*/
// 			{
// 				type: 'color',
// 				messageKey: 'BackgroundColor',
// 				label: 'Background Color',
// 				defaultValue: '000000', // Black
// 				capabilities: ['COLOR'],
// 			},
			{
				type: 'color',
				messageKey: 'ForegroundColor',
				label: 'Foreground Color',
				defaultValue: 'FFFFFF', // White
				capabilities: ['COLOR'],
			},
			{
				type: 'color',
				messageKey: 'SecondHandColor',
				label: 'Second Hand Color',
				defaultValue: 'FF0000', // Red
				capabilities: ['COLOR'],
			},
			{
				type: 'color',
				messageKey: 'LocationMarkerColor',
				label: 'Location Marker Color',
				defaultValue: 'FFFF00', // Yellow
				capabilities: ['COLOR'],
			},
			{
				type: 'color',
				messageKey: 'LocationMarkerBorderColor',
				label: 'Location Marker Color (Border)',
				defaultValue: 'FFAA00', // ChromeYellow
				capabilities: ['COLOR'],
			}
		]
	},

	// Checkpoint / Cycle
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Checkpoint/Cycle',
			},
			{
				type: 'toggle',
				messageKey: 'ShowCyclePanel',
				label: 'Show Cycle Panel',
				defaultValue: true,
			},
			{
				type: 'color',
				messageKey: 'CheckpointColor',
				label: 'Checkpoint/Cycle Color',
				defaultValue: '00AAAA', // Tiffany Blue
				capabilities: ['COLOR'],
			}
		]
	},

	// Status panel
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Status',
			},
			{
				type: 'toggle',
				messageKey: 'ShowStatusPanel',
				label: 'Show Status Panel',
				defaultValue: true,
			},
			{
				type: 'color',
				messageKey: 'PowerReserveColor',
				label: 'Power Reserve Color',
				defaultValue: 'AAAA00', // Limerick
				capabilities: ['COLOR'],
			}
		]
	},

	// Subclock
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Subclock',
			},
			{
				type: 'toggle',
				messageKey: 'ShowSubclock',
				label: 'Show Subclock',
				defaultValue: true,
			},
// 			{
// 				type: 'slider',
// 				messageKey: 'SubTimeZoneOffset',
// 				label: 'Subclock Time Zone',
// 				defaultValue: 0, // UTC
// 				min: -12 * 60 * 60,
// 				max:  12 * 60 * 60,
// 				step: 30 * 60,
// 			}
		]
	},

// 	// Notification
// 	{
// 		type: 'section',
// 		items: [
// 			{
// 				type: 'heading',
// 				defaultValue: 'Notification'
// 			},
// 			{
// 				type: 'select',
// 				messageKey: 'VibeOnCheckpoint',
// 				label: 'Two brief vibes on Cycle ends',
// 				defaultValue: '',
// 				options: [
// 					{  label: 'None',  value: '' },
// 					{  label: 'Single',  value: 'single' },
// 					{  label: 'Double',  value: 'double' },
// 					{  label: 'Long',  value: 'long' }
// 				]
// 			},
// 			{
// 				type: 'select',
// 				messageKey: 'VibeOnCycle',
// 				label: 'Two brief vibes on Cycle ends',
// 				defaultValue: '',
// 				options: [
// 					{  label: 'None',  value: '' },
// 					{  label: 'Single',  value: 'single' },
// 					{  label: 'Double',  value: 'double' },
// 					{  label: 'Long',  value: 'long' }
// 				]
// 			}
// 		]
// 	},

	// Power Saving
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Power Saving',
			},
			{
				type: 'toggle',
				messageKey: 'ShowSecondHand',
				label: 'Show Second Hand',
				defaultValue: true,
			}
// 			{
// 				type: 'toggle',
// 				messageKey: 'ShowSecondOnTap',
// 				label: 'Show Second Hand On Tap',
// 				defaultValue: true
// 			}
		]
	},

	{
		type: 'submit',
		defaultValue: 'Save',
	}

];
