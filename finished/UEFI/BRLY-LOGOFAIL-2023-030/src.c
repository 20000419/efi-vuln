jpeg_error_mgr *__fastcall jpeg_std_error(jpeg_error_mgr *err)
{
  jpeg_error_mgr *result; // rax

  err->last_jpeg_message = 126;
  *&err->trace_level = 0i64;
  err->error_exit = error_exit_function;
  err->emit_message = emit_message;
  err->output_message = output_message;
  err->format_message = format_message;
  err->reset_error_mgr = reset_error_mgr;
  err->jpeg_message_table = jpeg_std_message_table;
  result = err;
  err->msg_code = 0;
  err->addon_message_table = 0i64;
  *&err->first_addon_message = 0i64;
  return result;
}

unsigned __int64 __fastcall DecodeJPEG(const JOCTET *a1, unsigned int a2, __int64 a3)
{
  struct jpeg_error_mgr *err; // rax
  struct jpeg_decompress_struct cinfo; // [rsp+20h] [rbp-E0h] BYREF
  jpeg_error_mgr jerr; // [rsp+2A0h] [rbp+1A0h] BYREF

  if ( a1 && a3 )
  {
    err = jpeg_std_error(&jerr);
    Buffer = 0i64;
    cinfo.err = err;
    // BRLY-LOGOFAIL-2023-030: error_exit is overwritten with a dummy function which doesn't terminate execution when invoked.
    jerr.error_exit = null_sub;
    jerr.emit_message = null_sub;
    jerr.output_message = null_sub;
    jerr.format_message = null_sub;
    jpeg_CreateDecompress(&cinfo, 90, 0x278i64);
    jpeg_mem_src(&cinfo, a1, a2);
    if ( jpeg_read_header(&cinfo, 0) == 1 && jpeg_start_decompress(&cinfo) == 1 )
    {
      buffer = AllocateBuffer((cinfo.output_width * cinfo.output_components));
      if ( !buffer )
      {
        v7 = 0x8000000000000009ui64;
LABEL_28:
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        return v7;
      }
      decoded_image = AllocateBuffer(4i64 * cinfo.output_width * cinfo.output_height);      
...

char __fastcall get_dht(jpeg_decompress_struct *cinfo)
{
  struct jpeg_source_mgr *src; // rbx
  size_t bytes_in_buffer_2; // rsi
  const JOCTET *next_input_byte; // r14
  char result; // al
  int v6; // ebp
  const JOCTET *v7; // r14
  int v8; // ebp
  size_t v9; // rsi
  int v10; // eax
  size_t bytes_in_buffer; // rsi
  char *v12; // r14
  int length; // ebp MAPDST
  __int64 index; // r12
  int count; // r13d
  __int64 i_1; // r15
  int v17; // eax
  struct jpeg_error_mgr *err; // rdx
  __int64 j; // rcx
  struct jpeg_error_mgr *v21; // rdx
  __int64 k; // rcx
  __int64 i; // r15
  JHUFF_TBL **v24; // r15
  char v25[32]; // [rsp+20h] [rbp-148h]
  char huffval[256]; // [rsp+40h] [rbp-128h]

  src = cinfo->src;
  bytes_in_buffer_2 = src->bytes_in_buffer;
  next_input_byte = src->next_input_byte;
  if ( !bytes_in_buffer_2 )
  {
    if ( !(src->fill_input_buffer)() )
      return 0;
    next_input_byte = src->next_input_byte;
    bytes_in_buffer_2 = src->bytes_in_buffer;
  }
  v6 = *next_input_byte;
  v7 = next_input_byte + 1;
  v8 = v6 << 8;
  v9 = bytes_in_buffer_2 - 1;
  if ( !v9 )
  {
    if ( !src->fill_input_buffer(cinfo) )
      return 0;
    v7 = src->next_input_byte;
    v9 = src->bytes_in_buffer;
  }
  v10 = *v7;
  bytes_in_buffer = v9 - 1;
  v12 = (v7 + 1);
  length = v10 + v8 - 2;
  while ( length > 16 )
  {
    if ( !bytes_in_buffer )
    {
      if ( !src->fill_input_buffer(cinfo) )
        return 0;
      v12 = src->next_input_byte;
      bytes_in_buffer = src->bytes_in_buffer;
    }
    index = *v12;
    --bytes_in_buffer;
    ++v12;
    cinfo->err->msg_code = 82;
    cinfo->err->msg_parm.i[0] = index;
    cinfo->err->emit_message(cinfo, 1);
    count = 0;
    v25[0] = 0;
    for ( i_1 = 1i64; i_1 <= 16; ++i_1 )
    {
      if ( !bytes_in_buffer )
      {
        if ( !src->fill_input_buffer(cinfo) )
          return 0;
        v12 = src->next_input_byte;
        bytes_in_buffer = src->bytes_in_buffer;
      }
      v17 = *v12;
      --bytes_in_buffer;
      v25[i_1] = v17;
      ++v12;
      count += v17;
    }
    err = cinfo->err;
    length -= 17;
    for ( j = 0i64; j < 8; ++j )
      err->msg_parm.i[j] = v25[j + 1];
    cinfo->err->msg_code = 88;
    cinfo->err->emit_message(cinfo, 2);
    v21 = cinfo->err;
    for ( k = 0i64; k < 8; ++k )
      v21->msg_parm.i[k] = v25[k + 9];
    cinfo->err->msg_code = 88;
    cinfo->err->emit_message(cinfo, 2);
    if ( count > 256 || count > length )
    {
      cinfo->err->msg_code = JERR_BAD_HUFF_TABLE;
      // Problem here: error_exit normally aborts execution, but in Phoenix firmware 
      // it's a dummy function, so execution just continues.
      cinfo->err->error_exit(cinfo);
    }
    for ( i = 0i64; i < count; huffval[i++] = *v12++ )
    {
      if ( !bytes_in_buffer )
      {
        if ( !src->fill_input_buffer(cinfo) )
          return 0;
        v12 = src->next_input_byte;
        bytes_in_buffer = src->bytes_in_buffer;
      }
      --bytes_in_buffer;
    }
    length -= count;
    if ( (index & 0x10) != 0 )
    {
      LODWORD(index) = index - 16;
      v24 = &cinfo->ac_huff_tbl_ptrs[index];
    }
    else
    {
      v24 = &cinfo->dc_huff_tbl_ptrs[index];
    }
    if ( index > 3 )
    {
      cinfo->err->msg_code = 31;
      cinfo->err->msg_parm.i[0] = index;
      cinfo->err->error_exit(cinfo);
    }
    if ( !*v24 )
      *v24 = jpeg_alloc_huff_table(cinfo);
    MEMCOPY(*v24);
    if ( count > 0 )
      MEMCOPY((*v24)->huffval);
  }
  if ( length )
  {
    cinfo->err->msg_code = 12;
    cinfo->err->error_exit(cinfo);
  }
  src->next_input_byte = v12;
  result = 1;
  src->bytes_in_buffer = bytes_in_buffer;
  return result;
}


