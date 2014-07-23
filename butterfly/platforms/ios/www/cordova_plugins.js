cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/org.apache.cordova.console/www/console-via-logger.js",
        "id": "org.apache.cordova.console.console",
        "clobbers": [
            "console"
        ]
    },
    {
        "file": "plugins/org.apache.cordova.console/www/logger.js",
        "id": "org.apache.cordova.console.logger",
        "clobbers": [
            "cordova.logger"
        ]
    },
    {
        "file": "plugins/org.apache.cordova.dialogs/www/notification.js",
        "id": "org.apache.cordova.dialogs.notification",
        "merges": [
            "navigator.notification"
        ]
    },{
    "file": "plugins/butterfly.navigation/www/navigation.js",
    "id": "butterfly.navigation",
    "merges": [
             "navigator.navigation"
             ]
    },
    {
    "file": "plugins/butterfly.loading/www/loading.js",
    "id": "butterfly.loading",
    "merges": [
             "navigator.loading"
             ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "org.apache.cordova.console": "0.2.8",
    "org.apache.cordova.dialogs": "0.2.7"
}
// BOTTOM OF METADATA
});