/* This software is released under the MIT License, see LICENSE */

module.exports = function () {

	var clayConfig = this;
	
	function setupToggle(switchName, switchTarget) {
		var toggle = clayConfig.getItemByAppKey(switchName);
		var handler = function () {
			clayConfig.getItemByAppKey(switchTarget)[this.get() ? 'show' : 'hide']();
		};		
		toggle.on('change', handler);
		handler.call(toggle);		
	}

	clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
		setupToggle('ShowStatusPanel', 'PowerReserveColor');
	});

};
