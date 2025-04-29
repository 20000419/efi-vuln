if ( smtpport )                             // if custom SMTP port was specified
    port = smtpport;
else
    port = 25;
if ( user || pwd )                          // if SMTP user or password was specified
    _snprintf_chk(
        command,
        256,
        1,
        256,
        "%s --host=%s --port=%d --timeout=10 --auth=login --user=%s --passwordeval='echo %s' --from=%s %s < %s 2>&1",
        msmtp_path,                         // /bin/msmtp
        smtpaddr,                           // SMTP server host
        port,                               // SMTP server port
        user,                               // SMTP server user
        pwd,                                // SMTP server password
        sender,                             // from email address
        mail,                               // to email address
        msg_path);                          // /tmp/pef.txt
else
    _snprintf_chk(
        command,
        256,
        1,
        256,
        "%s --host=%s --port=%d --timeout=10 --auth=off --from=%s %s < %s 2>&1",
        msmtp_path,                         // /bin/msmtp
        smtpaddr,                           // SMTP server host
        port,                               // SMTP server port
        sender,                             // from email address
        mail,                               // to email address
        msg_path);                          // /tmp/pef.txt

...

j_ipmi_log("email cmd=%s\n", command);      // print command to console
v15 = 0;
...

while ( do_popen(command, v24) < 0 )        // execute command
{
    v16 = v15++;
    j_console_log("msmtp: cannot send email! retry %d\n", v16);
    if ( v15 == 3 )
        return 0;
}
