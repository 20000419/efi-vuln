function PageInit() {
  ...
  var param1 = window.location.hash.split("#");
  if (param1[1].length != 0) {
    var param2 = param1[1].split(",");
    if (param2[0].length != 0 && param2[1].length != 0) {
      ctrl_idx = param2[0];
      max_api_row_size = param2[1];
      document.getElementById("devinfo").innerHTML =
        "Device" + ctrl_idx + ": Unconfigured good drive";
      GetPhysicalHDDInfo(ctrl_idx);
    }
  } else {
    location.href = "../cgi/url_redirect.cgi?url_name=servh_storage";
  }
}
