
console.log("JavaScript successfully injected")

new QWebChannel(qt.webChannelTransport, function(channel) {
    console.log("QWebChannel successfully established")

    window.notificationService = channel.objects.notificationService

    // hook into the notification API, to deliver notifications native
    this.Notification = function(title, options) {
        console.log('Notification: ' + title + ' ' + JSON.stringify(options))

        window.notificationService.deliverNotification(title, options)
    };

    this.Notification.permission = 'granted';
    this.Notification.requestPermission = function(callback) {
        callback('granted');
    };

})

