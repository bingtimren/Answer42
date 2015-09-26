Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
  }
);

Pebble.addEventListener('appmessage', 
  function(e) {
    console.log('Phone: received message: ' + JSON.stringify(e.payload));
    console.log('prepare to call submitForm');
    submitForm(e.payload["1"]);
  }
);

function submitForm(value) {
  console.log('Prepare to submit: ' + value);
  var req = new XMLHttpRequest();
  req.open('GET', 'https://docs.google.com/forms/d/1-MmR1ptkFDktlZ936rJxYi3hsW9CIjLVIDaepOCIc2c/formResponse?ifq&entry.1880139073='+encodeURIComponent(value)+'&submit=Submit', true);
  req.onload = function(e) {
    console.log('response received, readyState:'+req.readyState+' status:' + req.status);
  };
  req.send(null);
console.log('Request sent');
}