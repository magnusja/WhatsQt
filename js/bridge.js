
console.log("JavaScript successfully injected")

var script = document.createElement('script');
script.src = 'https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js';
script.type = 'text/javascript';
document.getElementsByTagName('head')[0].appendChild(script);

new QWebChannel(qt.webChannelTransport, function(channel) {
    console.log("QWebChannel successfully established")

    window.notificationService = channel.objects.notificationService

    window.notificationService.notificationClicked.connect(function(title, options) {
        console.log("Notification clicked: " + title + " " + JSON.stringify(options))
        $("span[title='" + title + "'][dir='auto']").click()
    })
    // hook into the notification API, to deliver notifications native
    this.Notification = function(title, options) {
        console.log("Notification: " + title + " " + JSON.stringify(options))

        window.notificationService.deliverNotification(title, options)
    };

    this.Notification.permission = "granted";
    this.Notification.requestPermission = function(callback) {
        callback("granted");
    };

})

