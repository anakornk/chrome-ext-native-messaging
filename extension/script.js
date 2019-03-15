var port = chrome.runtime.connectNative('com.hashpire.pingpong');
port.onMessage.addListener(function(msg) {
  console.log("Received" + JSON.stringify(msg));
  document.getElementById("display").innerHTML = msg.text;
});

port.onDisconnect.addListener(function() {
  console.log("Disconnected");
});

document.getElementById("pingpong-btn").onclick = function(ev){
  var textboxText = document.getElementById("textbox").value;
  port.postMessage({ text: textboxText });
};


