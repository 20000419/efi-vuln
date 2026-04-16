} else if (cmp > 0 && 0 == (cmp = buffer_caseless_compare(CONST_BUF_LEN(ds->key), CONST_STR_LEN("If-Modified-Since")))) {
    /* Proxies sometimes send dup headers
     * if they are the same we ignore the second
     * if not, we raise an error */
    if (!con->request.http_if_modified_since) {
        // Store a copy of the header value instead of the pointer
        con->request.http_if_modified_since = buffer_append_string(NULL, ds->value->ptr);
    } else {
        // Compare the stored value with the current header value
        if (buffer_caseless_compare(con->request.http_if_modified_since, ds->value->ptr) == 0) {
            // Free the duplicate header data
            ds->free((data_unset *)ds);
            ds = NULL;
        } else {
            con->http_status = 400;
            con->keep_alive = 0;
...
