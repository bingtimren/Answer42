var days = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];

Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
  }
);

function pad(number) {
	if (number < 10) { number = "0" + number};
	return number;
};

function send_ack(acknowledgement) {
	var dic = {
		42: acknowledgement
	};
	Pebble.sendAppMessage(dic,
		function(e) {
			console.log('Acknowledgement sent, acknowledgement length:' + acknowledgement.length);
		},
		function(e) {
			console.log('Error sending acknowledgement info to Pebble!');
		}
	);	
};




Pebble.addEventListener('appmessage', 
  function(e) {
	var ack_count = 0;
	var acknowledgement = "";
    // obtain number of records
    var numberOfRecords = e.payload["0"];	
	// the closures
	function onload_handler(i, index, localReq) {
		return function() {
			ack_count += 1; // one more result known
			if (localReq.status == "200") {
				// register success index to acknowledgement array
				acknowledgement = acknowledgement + String.fromCharCode(index+1); 
				console.log("[i="+i+"] "+'Response received, readyState:'+localReq.readyState+' status:' + localReq.status+" success, index="+index+" total_success="+ack_count);
			} else
				console.log("[i="+i+"] "+'Response received, readyState:'+localReq.readyState+' status:' + localReq.status+" FAILED!, index="+index+" total_success="+ack_count);
			// if this is the last, send acknowledgement
			if (ack_count == numberOfRecords) {
				console.log("Last result received, prepare to acknowledge to pebble.");
				send_ack(acknowledgement);
			};
		}; // end of function
	}; // Immediately Invoked Function Expression	
	  
	function onerror_handler(i, index, localReq) {
		return function() {
			ack_count += 1; // one more result known
			console.log("[i="+i+"] "+'ERROR, readyState:'+localReq.readyState+' status:' + localReq.status+" FAILED!, index="+index+" total_success="+ack_count);
			// if this is the last, send acknowledgement
			if (ack_count == numberOfRecords) {
				console.log("Last result received (on error), prepare to acknowledge to pebble.");
				send_ack(acknowledgement);
			};
		}; // end of function
	}; // Immediately Invoked Function Expression		  
	
	// actually start
    console.log('Phone: received message: ' + JSON.stringify(e.payload));
    console.log('Number of records received: ' + numberOfRecords);
	var tzAdjust = (new Date()).getTimezoneOffset()*60;
	console.log('Time zone adjustment is ' + tzAdjust);
	
    for (var i=0; i<numberOfRecords; i++) {
		// submit google form
		var req = new XMLHttpRequest();
		var index = e.payload[i*4+1];
		var tStamp = new Date(e.payload[i*4+2]*1000 + tzAdjust*1000);
		var tStampStr = tStamp.getFullYear() + "-" + pad(tStamp.getMonth()) + "-" + pad(tStamp.getDay()) + " " + pad(tStamp.getHours()) + ":"+ pad(tStamp.getMinutes())+" "+days[tStamp.getDay()];
		var durition = e.payload[i*4+3]
		var what = e.payload[i*4+4]
		var summary = "index="+index+" time stamp={"+tStampStr+"} durition="+durition+" what:"+what;
		console.log("Before sending, Summary: "+summary);
		
		// prepare to submit
		req.open('GET', 'https://docs.google.com/forms/d/1-MmR1ptkFDktlZ936rJxYi3hsW9CIjLVIDaepOCIc2c/formResponse?ifq&entry.1880139073='+encodeURIComponent(summary)+'&submit=Submit', true);
		req.onload = onload_handler(i, index, req);
		req.onabort = onerror_handler(i, index, req);
		req.onerror = onerror_handler(i, index, req);	
		req.ontimeout = onerror_handler(i, index, req);
		req.send();
		console.log('Request sent');
	}; // end for
	console.log("ALL SENT");
  }
);

