} else if (cmp > 0 && 0 == (cmp = buffer_caseless_compare(CONST_BUF_LEN(ds->key), CONST_STR_LEN("If-Modified-Since")))) {
    /* Proxies sometimes send dup headers
     * if they are the same we ignore the second
     * if not, we raise an error */
    if (!con->request.http_if_modified_since) {
        con->request.http_if_modified_since = ds->value->ptr;
    } else {
        /* Check if the new header value is the same as the stored one */
        if (0 == strcasecmp(con->request.http_if_modified_since, ds->value->ptr)) {
            /* ignore it if they are the same */
            ds->free((data_unset *)ds);
            ds = NULL;
        } else {
            con->http_status = 400;
            con->keep_alive = 0;
...
