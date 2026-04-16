} else if (cmp > 0 && 0 == (cmp = buffer_caseless_compare(CONST_BUF_LEN(ds->key), CONST_STR_LEN("If-Modified-Since")))) {
    /* Proxies sometimes send dup headers
     * if they are the same we ignore the second
     * if not, we raise an error */
    if (!con->request.http_if_modified_since) {
        // Store a copy of the header value to avoid dependency on potentially reallocated/freed buffers
        con->request.http_if_modified_since = buffer_append_string(NULL, ds->value->ptr);
    } else {
        // Compare the stored copied value with the current header value (handles folded headers safely)
        if (0 == strcasecmp(con->request.http_if_modified_since, ds->value->ptr)) {
            /* ignore it if they are the same */
            ds->free((data_unset *)ds);
            ds = NULL;
        } else {
            con->http_status = 400;
            con->keep_alive = 0;
...
