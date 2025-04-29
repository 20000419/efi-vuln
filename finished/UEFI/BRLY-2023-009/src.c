function PageInit()
{
    ...
    var PortNum = getParameter("port");
    ...
    if ( PortNum != "null")
        NewURL = window.location.protocol+"//" + aHostName + ":" + PortNum + "/";
    else
        NewURL = window.location.protocol+"//" + aHostName+ ":" + window.location.port + "/";

    NewString = lang.LANG_FW_RESET_DESC3.replace("NEWURL_PATTERN",NewURL);
    $('reset_string').innerHTML = NewString;
    ...

function getParameter(parameterName) {
    var strQuery = location.search.substring(1);
    var paramName = parameterName + "=";

    if (strQuery.length > 0)
    {
        begin = strQuery.indexOf(paramName);

        if (begin != -1)
        {
            begin += paramName.length;
            end = strQuery.indexOf("&" , begin);
            if ( end == -1 ) end = strQuery.length

            return unescape(strQuery.substring(begin, end));
        }
        return "null";
    }
}
