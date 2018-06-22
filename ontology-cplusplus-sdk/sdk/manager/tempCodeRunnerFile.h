    // try
    // {
    //   RpcClient rpc;
    //   rpc = dynamic_cast<RpcClient &>(connector);
    //   any_ret = rpc.sendRawTransaction(true, "", hexData);
    //   return any_ret;
    // }
    // catch (std::bad_cast const &ex)
    // {
    //   std::cout << "[" << ex.what() << "]" << std::endl;
    //   throw "connector instanceof Unsupport type";
    // }