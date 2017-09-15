/**@file rpc_msg.x
*  @brief message handler RPC
*  @note
*    comment json/xml string argument
*/
program MSG_PROG{
  version MSG_VER{
    string MSG_REQ(string) = 1;
  }
} = 0x20000001;