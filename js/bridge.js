
console.log("JavaScript successfully injected")

new QWebChannel(qt.webChannelTransport, function(channel) {
    console.log("QWebChannel successfully established")
})

