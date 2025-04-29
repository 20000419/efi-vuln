var sel = WebUtil.readSetting("lang","en");

translator = jQuery('body').translate ({
    lang: sel,
    t: eval("kvmdict_" + sel)
});
