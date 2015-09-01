
console.log("JavaScript successfully injected")

new QWebChannel(qt.webChannelTransport, function(channel) {
    window.alert("QWebChannel successfully established")
})
