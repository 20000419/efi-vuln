if ( UtilGetSMTPAuthEn(hostname) )    // if SMTP credentials were configured
    {
      UtilGetSMTPUserName(smtp_username, 65);
      UtilGetSMTPPassword(smtp_password, 65);
      if ( add_escape(smtp_username, smtp_username_esc) || add_escape(smtp_password, smtp_password_esc) )
      {
        j_console_log("[%s:%d]Fail to add escape for username or password\n", "SMTPClientSendMail", 3831);
        free(command);
        free(ptr);
        return 0;
      }
      res = _snprintf_chk(
            command,
            4096,
            1,
            4096,
            "%s --host=%s --port=%d --domain=%s --timeout=1 --auth=login --user=%s --passwordeval='echo %s' --from=%s %s > %s 2>&1",
            "/bin/msmtp",
            host,
            port,
            domain,
            smtp_username,
            smtp_password,
            sender,
            recipient,
            filename);
    }
    ...
    run_shellcmd(command);
