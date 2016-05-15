var days = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];

DEBUG = false;

Pebble.addEventListener('ready',
  function(e) {
    debug_log('JavaScript app ready and running!');
  }
);

function debug_log(message) {
	if (DEBUG) console.log(message);
};

debug_log("DEBUGGING MODE");

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
			debug_log('Acknowledgement sent, acknowledgement length:' + acknowledgement.length);
		},
		function(e) {
			debug_log('Error sending acknowledgement info to Pebble!');
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
  //*********************************************************************//	
	// when response is loaded
	function onload_handler(i, index, localReq) {
		return function() {
			ack_count += 1; // one more result known
			if (localReq.status == "200") {
				if (localReq.responseText.indexOf("Your response has been recorded.")>=0) {
					// register success index to acknowledgement array
					acknowledgement = acknowledgement + String.fromCharCode(index+1); 
					debug_log("[i="+i+"] "+'Response received, submission recorded, readyState:'+localReq.readyState+' status:' + localReq.status+" success, index="+index+" total_success="+ack_count);
				} else {
					// this is where interesting thing happened, status 200 but response not recorded?
					debug_log("Status 200 but response not recorded, what??!!");
					debug_log(localReq.responseText);
				};
			} else
				debug_log("[i="+i+"] "+'Response received, readyState:'+localReq.readyState+' status:' + localReq.status+" FAILED!, index="+index+" total_success="+ack_count);
			// if this is the last, send acknowledgement
			if (ack_count == numberOfRecords) {
				debug_log("Last result received, prepare to acknowledge to pebble.");
				send_ack(acknowledgement);
			};
		}; // end of function
	}; // Immediately Invoked Function Expression	

  //*********************************************************************//
	// when response has error  
	function onerror_handler(i, index, localReq) {
		return function() {
			ack_count += 1; // one more result known
			debug_log("[i="+i+"] "+'ERROR, readyState:'+localReq.readyState+' status:' + localReq.status+" FAILED!, index="+index+" total_success="+ack_count);
			// if this is the last, send acknowledgement
			if (ack_count == numberOfRecords) {
				debug_log("Last result received (on error), prepare to acknowledge to pebble.");
				send_ack(acknowledgement);
			};
		}; // end of function
	}; // Immediately Invoked Function Expression		  
	
	// actually start
    debug_log('Phone: received message: ' + JSON.stringify(e.payload));
    debug_log('Number of records received: ' + numberOfRecords);
	
    for (var i=0; i<numberOfRecords; i++) {
		// submit google form
		var req = new XMLHttpRequest();
		var index = e.payload[i*4+1];
		var tStamp = new Date(e.payload[i*4+2]*1000);
		var tDateStr = tStamp.getFullYear() + "." + pad(tStamp.getMonth()+1) + "." + pad(tStamp.getDate()) + " " +days[tStamp.getDay()];
		var tTimeStr = pad(tStamp.getHours()) + ":"+ pad(tStamp.getMinutes());
		var durition = e.payload[i*4+3]/100;
		var what = e.payload[i*4+4];
		var summary = "index="+index+" time stamp={"+tDateStr+" / "+tTimeStr+"} durition="+durition+" what:"+what;
		debug_log("Before sending, Summary: "+summary);
		
		var URL = 'https://docs.google.com/forms/d/1gOp9TOxxIoQRsY0rD7eGmJApORie8W-RQGeg2EZQz14/formResponse?ifq'+
			'&entry.1602682480='+encodeURIComponent(tDateStr)+
			'&entry.1527113700='+encodeURIComponent(tTimeStr)+
			'&entry.1936279194='+encodeURIComponent(durition)+
			'&entry.55169166='+encodeURIComponent(what)+
			'&entry.440204214=Y&submit=Submit';
		// prepare to submit
		debug_log("URL: "+URL);
		req.open('GET', URL, true);
		req.onload = onload_handler(i, index, req);
		req.onabort = onerror_handler(i, index, req);
		req.onerror = onerror_handler(i, index, req);	
		req.ontimeout = onerror_handler(i, index, req);
		req.send();
		debug_log('Request sent');
	}; // end for
	debug_log("ALL SENT");
  }
);
