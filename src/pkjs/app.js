/* This software is released under the MIT License, see LICENSE */

var Clay = require('pebble-clay');

var config = require('./clay-config');
var handler = require('./clay-handler');

var clay = new Clay(config, handler);

// Aplite ではタイムゾーンを拾えないので JavaScript で送り込む
Pebble.addEventListener('ready', function () {

	var data = {
		DetectedTimeZoneOffset: new Date().getTimezoneOffset() * 60
	};

	Pebble.sendAppMessage(data, function () {
		console.log('Message sent successfully: ' + JSON.stringify(data));
	}, function (e) {
		console.log('Message failed: ' + JSON.stringify (e));
	});

});
