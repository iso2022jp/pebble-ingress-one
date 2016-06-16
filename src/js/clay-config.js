/* This software is released under the MIT License, see LICENSE */

module.exports = [

	{
		type: 'heading',
		defaultValue: 'Configuration'
	},

	// Appearance
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Appearance'
			},
			/*
			{
				type: 'toggle',
				appKey: 'AutoTimezone',
				label: 'Auto Timezone',
				defaultValue: true
			},
			{
				type: 'color',
				appKey: 'Timezone',
				label: 'Timezone',
				defaultValue: '000000'
			},
*/
			{
				type: 'color',
				appKey: 'BackgroundColor',
				label: 'Background Color',
				defaultValue: '000000' // Black
			},
			{
				type: 'color',
				appKey: 'ForegroundColor',
				label: 'Foreground Color',
				defaultValue: 'FFFFFF' // White
			},
			{
				type: 'color',
				appKey: 'SecondHandColor',
				label: 'Second Hand Color',
				defaultValue: 'FF0000', // Red
				capabilities: ['COLOR']
			}
		]
	},

	// Checkpoint / Cycle
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Checkpoint/Cycle'
			},
			{
				type: 'toggle',
				appKey: 'ShowCyclePanel',
				label: 'Show Cycle Panel',
				defaultValue: true,
			},
			{
				type: 'color',
				appKey: 'CheckpointColor',
				label: 'Checkpoint/Cycle Color',
				defaultValue: '00AAAA', // Tiffany Blue
				capabilities: ['COLOR']
			}
		]
	},

	// Status panel
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Status'
			},
			{
				type: 'toggle',
				appKey: 'ShowStatusPanel',
				label: 'Show Status Panel',
				defaultValue: true
			},
			{
				type: 'color',
				appKey: 'PowerReserveColor',
				label: 'Power Reserve Color',
				defaultValue: 'AAAA00', // Limerick
				capabilities: ['COLOR']
			}
		]
	},

	// Subclock
	{
		type: 'section',
		items: [
			{
				type: 'heading',
				defaultValue: 'Subclock'
			},
			{
				type: 'toggle',
				appKey: 'ShowSubclock',
				label: 'Show Subclock',
				defaultValue: true
			},
// 			{
// 				type: 'slider',
// 				appKey: 'SubTimeZoneOffset',
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
// 				appKey: 'VibeOnCheckpoint',
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
// 				appKey: 'VibeOnCycle',
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
				defaultValue: 'Power Saving'
			},
			{
				type: 'toggle',
				appKey: 'ShowSecondHand',
				label: 'Show Second Hand',
				defaultValue: true
			}
// 			{
// 				type: 'toggle',
// 				appKey: 'ShowSecondOnTap',
// 				label: 'Show Second Hand On Tap',
// 				defaultValue: true
// 			}
		]
	},

	{
		type: 'submit',
		defaultValue: 'Save'
	}

];
