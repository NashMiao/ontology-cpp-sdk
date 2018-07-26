#include "OntSdk.h"
#include "smartcontract/Vm.h"

Vm *OntSdk::getVm()
{
    if (vm == NULL)
    {
        vm = new Vm();
    }
    return vm;
}

void OntSdk::setDefaultConnect(ConnectMgr connect) { connectDefault = connect; }

void OntSdk::setConnectTestNet()
{
    try
    {
        std::string rpcUrl = "http://polaris1.ont.io";
        setRpc(rpcUrl);
        connDefault = getRpc();
    }
    catch (SDKException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void OntSdk::setConnectMainNet()
{
    try
    {
        std::string rpcUrl = "http://dappnode1.ont.io";
        setRpc(rpcUrl);
        connDefault = getRpc();
    }
    catch (SDKException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

ConnectMgr OntSdk::getWebSocket()
{
    if (&connectWebSocket == NULL)
    {
        throw new SDKException(ErrorCode::WebsocketNotInit);
    }
    return connectWebSocket;
}
ConnectMgr OntSdk::getRpc() throw SDKException
{
    if (&connectRpc == NULL)
    {
        throw new SDKException(ErrorCode::ConnRestfulNotInit);
    }
    return connRpc;
}
ConnectMgr OntSdk::getRestful() throw SDKException
{
    if (&connectRestful == NULL)
    {
        throw new SDKException(ErrorCode::ConnRestfulNotInit);
    }
    return connRestful;
}

ConnectMgr OntSdk::getConnect()
{
    if (&connectDefault != NULL)
    {
        return connectDefault;
    }
    else if (&connectRpc != NULL)
    {
        return connectRpc;
    }
    else if (&connectRestful != NULL)
    {
        return connectRestful;
    }
    else if (&connectWebSocket != NULL)
    {
        return connectWebSocket;
    }
    else
    {
        throw new SDKException(ErrorCode::OtherError("signServer null"));
    }
}

void OntSdk::signTx(InvokeCodeTransaction &tx,
                    const std::vector<Account> &accounts)
{
    if (accounts.size() > Common::TX_MAX_SIG_SIZE)
    {
        throw SDKException(ErrorCode::StrParamErr(
            "the number of transaction signatures should not be over 16"));
    }
    std::vector<Sig> sigs;
    sigs.reserve(accounts.size());
    for (size_t i = 0; i < accounts.size(); i++)
    {
        Sig sig_item;
        for (size_t j = 0; j < accounts.size(); j++)
        {
            std::vector<unsigned char> pub_key;
            std::vector<unsigned char> signature;
            pub_key = accounts[j].serializePublicKey();
            signature = tx.sign(accounts[j], defaultSignScheme, defaultCurveName);
            sig_item.add_M();
            sig_item.add_pubKeys(pub_key);
            sig_item.add_sigData(signature);
        }
        sigs.push_back(sig_item);
    }
    tx.add_sigs(sigs);
}
void OntSdk::addSign(InvokeCodeTransaction &tx, const Account &acct)
{
    if (tx.sigs_length() > Common::TX_MAX_SIG_SIZE)
    {
        throw new SDKException(ErrorCode::ParamErr(
            "the number of transaction signatures should not be over 16"));
    }
    int m = 1;
    std::string pub_key = acct.serializePublicKey_str();
    std::string sig_data = tx.sign_str(acct, defaultSignScheme, defaultCurveName);
    Sig sig_item(pub_key, m, sig_data);
    tx.add_sig(sig_item);
}
void OntSdk::addMultiSign(InvokeCodeTransaction &tx, int M,
                          const std::vector<Account> &acct)
{
    if (tx.sigs_length() >= MULTI_SIG_MAX_PUBKEY_SIZE ||
        tx.sigs_length() + acct.size() > MULTI_SIG_MAX_PUBKEY_SIZE)
    {
        throw "the number of transaction signatures should not be over 16";
    }

    std::vector<Sig> _sigs;
    for (int i = 0; i < tx.sigs_length(); i++)
    {
        _sigs.push_back(tx.get_sig(i));
    }
    std::vector<std::string> _pubKeys;
    std::vector<std::string> _sigData;
    for (size_t i = 0; i < acct.size(); i++)
    {
        _pubKeys.push_back((acct[i].serializePublicKey_str()));
        _sigData.push_back(
            (tx.sign_str(acct[i], defaultSignScheme, defaultCurveName)));
        Sig sig_item(_pubKeys, M, _sigData);
        _sigs.push_back(sig_item);
    }
    tx.add_sigs(_sigs);
}