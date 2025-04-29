...
var sel = WebUtil.readSetting("lang", "en"
);
...
change_ui_lang(sel);
...

WebUtil.readSetting = function (name, defaultValue) 
{
    "use strict"
;
    var
 value;
    if (window.chrome && window
.chrome.storage) {
        value = WebUtil.settings[name];
    } else
 {
        value = localStorage
.getItem(name);
    }
    if (typeof value === "undefined"
) {
        value = null
;
    }
    if (value === null && typeof defaultValue !== undefined
) {
        return
 defaultValue;
    } else
 {
        return
 value;
    }
};

function change_ui_lang(v) 
{
    ...
    var lang = eval(v + "_lang"
);
    ...
