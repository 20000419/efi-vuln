function PageInit()
{
    ...
    index_var = GetVars("index");
    ...
    ruleno_obj = document.getElementById("ruleno");
    ...
    ruleno_obj.innerHTML = index_var;
    ...
}

function GetVars (str)
{
    url = location.search;
    var parameterList = url.split ("&");
    for (var i = 0; i < parameterList.length; i++) {
        parameter = parameterList[i].split ("=");
        if (parameter[0] == str) {
            return (decodeURIComponent (parameter[1]));
        }
    }
}
