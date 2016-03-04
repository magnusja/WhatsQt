/*
 * This file is part of WhatsQt.
 *
 * WhatsQt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WhatsQt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WhatsQt.  If not, see <http://www.gnu.org/licenses/>.
 */

console.log("JavaScript successfully injected")

var script = document.createElement('script');
script.src = 'https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js';
script.type = 'text/javascript';
document.documentElement.appendChild(script);

function openChat(tag) {
    tag = tag.replace('.', '=1');
    console.log("Open chat with tag: " + tag);
    var event = new MouseEvent('mousedown', { 'view': window, 'bubbles': true, 'cancelable': true });

    document.querySelector('div.chat[data-reactid*="' + tag + '"]').dispatchEvent(event);
}

new QWebChannel(qt.webChannelTransport, function(channel) {
    console.log("QWebChannel successfully established");

    window.notificationService = channel.objects.notificationService;

    window.notificationService.notificationClicked.connect(function(title, options) {
        console.log("Notification clicked: " + title + " " + JSON.stringify(options));
        openChat(options.tag);
    });

    window.notificationService.notificationReplied.connect(function(title, options, reply) {
        console.log("Notification replied: " + title + " " + JSON.stringify(options) + " " + reply);
        openChat(options.tag);

        // TODO: maybe listen for html change event instead of waiting 250ms
        setTimeout(function() {
            var input = $("div.input[dir='auto'][contenteditable='true']");
            if(input.length <= 0) {
                alert("input null");
                return;
            }

            input.text(reply);

            // trigger input event to force onChange method of react.js to be called
            var event = new Event('input', { bubbles: true });
            input[0].dispatchEvent(event);

            var button = $("button.icon.btn-icon.icon-send.send-container");

            if(button.length <= 0) {
                alert("button null");
                return;
            }

            button.click();
        }, 250)
    })


    // hook into the notification API, to deliver notifications native
    this.Notification = function(title, options) {
        console.log("Notification: " + title + " " + JSON.stringify(options));

        window.notificationService.deliverNotification(title, options);
    };

    this.Notification.permission = "granted";
    this.Notification.requestPermission = function(callback) {
        callback("granted");
    };

    //setInterval(function() {
    //    this.Notification("Title", {tag: "tag", body: "Body"})
    //}, 3000);

});
