
console.log("JavaScript successfully injected")

new QWebChannel(qt.webChannelTransport, function(channel) {
    console.log("QWebChannel successfully established")

    // hook into the notification API, to deliver notifications native
    this.Notification = function(title, options) {
        console.log('Notification: ' + title + ' ' + JSON.stringify(options));
    };

    this.Notification.permission = 'granted';
    this.Notification.requestPermission = function(callback) {
        callback('granted');
    };

})

