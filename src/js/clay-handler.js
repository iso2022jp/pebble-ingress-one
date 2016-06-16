/* This software is released under the MIT License, see LICENSE */

module.exports = function () {

	var clayConfig = this;

	function toggleShowStatusPanel() {
		if (this.get()) {
			clayConfig.getItemByAppKey('PowerReserveColor').show();
		} else {
			clayConfig.getItemByAppKey('PowerReserveColor').hide();
		}
	}

// 	function toggleShowSecondHand() {
// 		if (this.get()) {
// 			clayConfig.getItemByAppKey('ShowSecondOnTap').hide();
// 		} else {
// 			clayConfig.getItemByAppKey('ShowSecondOnTap').show();
// 		}
// 	}

	clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {

		var toggle;

		// Show/Hide Status Panel
		toggle = clayConfig.getItemByAppKey('ShowStatusPanel');
		toggle.on('change', toggleShowStatusPanel);
		toggleShowStatusPanel.call(toggle);

// 		// Show/Hide Second Hand
// 		toggle = clayConfig.getItemByAppKey('ShowSecondHand');
// 		toggle.on('change', toggleShowSecondHand);
// 		toggleShowSecondHand.call(toggle);

	});

};
