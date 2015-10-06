Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
  }
);

function pad(number) {
	if (number < 10) { number = "0" + number};
	return number;
};

Pebble.addEventListener('appmessage', 
  function(e) {
    console.log('Phone: received message: ' + JSON.stringify(e.payload));
	// submit google form
	var req = new XMLHttpRequest();
	var tzAdjust = (new Date()).getTimezoneOffset()*60;
	var tStamp = new Date(e.payload["1"]*1000 + tzAdjust*1000);
	var days = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"]
	var tStampStr = tStamp.getFullYear() + "-" + pad(tStamp.getMonth()) + "-" + pad(tStamp.getDay()) + " " + pad(tStamp.getHours()) + ":"+ pad(tStamp.getMinutes())+" "+days[tStamp.getDay()];
	req.open('GET', 'https://docs.google.com/forms/d/1-MmR1ptkFDktlZ936rJxYi3hsW9CIjLVIDaepOCIc2c/formResponse?ifq&entry.1880139073='+encodeURIComponent(tStampStr)+'&submit=Submit', true);
	req.onload = function(x) {
		console.log('response received, readyState:'+req.readyState+' status:' + req.status);
		if (req.status == "200") {
			status = "S";
		} else {
			status = "F";
		};
		payload = {
				0:e.payload["0"],
				4:status
			};
		Pebble.sendAppMessage(payload, null, null);
		console.log('ack to watch sent, payload '+JSON.stringify(payload));
	};
	req.send(null);
	console.log('Request sent');
  }
);

