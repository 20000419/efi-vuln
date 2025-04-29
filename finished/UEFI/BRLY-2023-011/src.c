...
lang_setting = ReadCookie("language");
if (lang_setting == null) {
  CreateCookie("langSetFlag", "0");
  CreateCookie("language", "English");
  lang_setting = "English";
}
document.write(
  '<script type="text/javascript", src = "../js/lang/' +
    lang_setting +
    '/lang_str.js"></script>'
);
...

function ReadCookie(name) {
  let invalidStr = name.match(/([^A-Za-z0-9= ;])+/g);
  if (!invalidStr) {
    var arg = name + "=";
    var alen = arg.length;
    var clen = document.cookie.length;
    var i = 0;

    while (i < clen) {
      var j = i + alen;

      if (document.cookie.substring(i, j) == arg) {
        return get_cookie_val(j);
      }

      i = document.cookie.indexOf(" ", i) + 1;

      if (i == 0) {
        break;
      }
    }
  }
  return null;
}
