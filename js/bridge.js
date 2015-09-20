
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

    window.notificationService.notificationReplied.connect(function(title, options, reply) {
        console.log("Notification replied: " + title + " " + JSON.stringify(options) + " " + reply)
        $("span[title='" + title + "'][dir='auto']").click()

        // TODO: maybe listen for html change event instead of waiting 250ms
        setTimeout(function() {
            var input = $("div.input[dir='auto'][contenteditable='true']")
            input.text(reply)

            // trigger input event to force onChange method of react.js to be called
            var event = new Event('input', { bubbles: true });
            input[0].dispatchEvent(event);

            $("button.icon.btn-icon.icon-send.send-container").click()
        }, 250)
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

    setInterval(function(){ this.Notification("abend", {"tag": "tag", "bodoy": "body"}) }, 3000);

})
