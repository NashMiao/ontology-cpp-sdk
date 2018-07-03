#ifndef ERRORCODE_H
#define ERRORCODE_H

#include <nlohmann/json.hpp>
#include <string>

class ErrorCode
{
  public:
    static std::string getError(int code, std::string msg)
    {
        nlohmann::json json_map = {{"Error", code}, {"Desc", msg}};
        return json_map.dump();
    }

    // account error
    static std::string InvalidParams =
        getError(51001, "Account Error,invalid params");
    static std::string UnsupportedKeyType =
        getError(51002, "Account Error,unsupported key type");
    static std::string InvalidMessage =
        getError(51003, "Account Error,invalid message");
    static std::string WithoutPrivate = getError(
        51004,
        "Account Error,account without private key cannot generate signature");
    static std::string InvalidSM2Signature = getError(
        51005,
        "Account Error,invalid SM2 signature parameter, ID (String) excepted");
    static std::string AccountInvalidInput =
        getError(51006, "Account Error,account invalid input");
    static std::string AccountWithoutPublicKey = getError(
        51007,
        "Account Error,account without public key cannot verify signature");
    static std::string UnknownKeyType =
        getError(51008, "Account Error,unknown key type");
    static std::string NullInput = getError(51009, "Account Error,null input");
    static std::string InvalidData =
        getError(51010, "Account Error,invalid data");
    static std::string Decoded3bytesError =
        getError(51011, "Account Error,decoded 3 bytes error");
    static std::string DecodePrikeyPassphraseError =
        getError(51012, "Account Error,decode prikey passphrase error.");
    static std::string PrikeyLengthError =
        getError(51013, "Account Error,Prikey length error");
    static std::string EncryptedPriKeyError =
        getError(51014, "Account Error,Prikey length error");
    static std::string encryptedPriKeyAddressPasswordErr = getError(
        51015, "Account Error,encryptedPriKey address password not match.");
    static std::string EncriptPrivateKeyError =
        getError(51016, "Account Error, encript privatekey error,");

    //
    static std::string ParamLengthErr =
        getError(52001, "Uint256 Error,param length error");
    static std::string ChecksumNotValidate =
        getError(52002, "Base58 Error,Checksum does not validate");
    static std::string InputTooShort =
        getError(52003, "Base58 Error,Input too short");
    static std::string UnknownCurve =
        getError(52004, "Curve Error,unknown curve");
    static std::string UnknownCurveLabel =
        getError(52005, "Curve Error,unknown curve label");
    static std::string UnknownAsymmetricKeyType =
        getError(52006, "keyType Error,unknown asymmetric key type");
    static std::string InvalidSignatureData =
        getError(52007, "Signature Error,invalid signature data: missing the ID "
                        "parameter for SM3withSM2");
    static std::string InvalidSignatureDataLen =
        getError(52008, "Signature Error,invalid signature data length");
    static std::string MalformedSignature =
        getError(52009, "Signature Error,malformed signature");
    static std::string UnsupportedSignatureScheme =
        getError(52010, "Signature Error,unsupported signature scheme:");
    static std::string DataSignatureErr =
        getError(52011, "Signature Error,Data signature error.");
    static std::string UnSupportOperation =
        getError(52012, "Address Error, UnsupportedOperationException");

    // Core Error
    static std::string TxDeserializeError =
        getError(53001, "Core Error,Transaction deserialize failed");
    static std::string BlockDeserializeError =
        getError(53002, "Core Error,Block deserialize failed");

    // merkle error
    static std::string MerkleVerifierErr = getError(
        54001, "Wrong params: the tree size is smaller than the leaf index");
    static std::string TargetHashesErr = getError(54002, "targetHashes error");

    static std::string ConstructedRootHashErr(String msg)
    {
        return getError(54003, "Other Error," + msg);
    }

    static std::string AsserFailedHashFullTree =
        getError(54004, "assert failed in hash full tree");
    static std::string LeftTreeFull = getError(54005, "left tree always full");

    // SmartCodeTx Error
    static std::string SendRawTxError =
        getError(58001, "SmartCodeTx Error,sendRawTransaction error");
    static std::string TypeError =
        getError(58002, "SmartCodeTx Error,type error");

    // OntIdTx Error
    static std::string NullCodeHash =
        getError(58003, "OntIdTx Error,null codeHash");
    static std::string ParamError = getError(58004, "param error,");

    static std::string ParamErr(String msg) { return getError(58005, msg); }

    static std::string DidNull = getError(
        58006, "OntIdTx Error,SendDid or receiverDid is null in metaData");
    static std::string NotExistCliamIssuer =
        getError(58007, "OntIdTx Error,Not exist cliam issuer");
    static std::string NotFoundPublicKeyId =
        getError(58008, "OntIdTx Error,not found PublicKeyId");
    static std::string PublicKeyIdErr =
        getError(58009, "OntIdTx Error,PublicKeyId err");
    static std::string BlockHeightNotMatch =
        getError(58010, "OntIdTx Error,BlockHeight not match");
    static std::string NodesNotMatch =
        getError(58011, "OntIdTx Error,nodes not match");
    static std::string ResultIsNull =
        getError(58012, "OntIdTx Error,result is null");
    static std::string CreateOntIdClaimErr =
        getError(58013, "OntIdTx Error, createOntIdClaim error");
    static std::string VerifyOntIdClaimErr =
        getError(58014, "OntIdTx Error, verifyOntIdClaim error");
    static std::string WriteVarBytesError =
        getError(58015, "OntIdTx Error, writeVarBytes error");
    static std::string SendRawTransactionPreExec =
        getError(58016, "OntIdTx Error, sendRawTransaction PreExec error");
    static std::string SenderAmtNotEqPasswordAmt = getError(
        58017, "OntIdTx Error, senders amount is not equal password amount");
    static std::string ExpireErr =
        getError(58017, "OntIdTx Error, expire is wrong");
    static std::string GetStatusErr(String msg)
    {
        return getError(58017, "GetStatus Error," + msg);
    };

    // OntAsset Error
    static std::string AssetNameError =
        getError(58101, "OntAsset Error,asset name error");
    static std::string DidError = getError(58102, "OntAsset Error,Did error");
    static std::string NullPkId = getError(58103, "OntAsset Error,null pkId");
    static std::string NullClaimId =
        getError(58104, "OntAsset Error,null claimId");
    static std::string AmountError = getError(
        58105, "OntAsset Error,amount or gas is less than or equal to zero");
    static std::string ParamLengthNotSame =
        getError(58105, "OntAsset Error,param length is not the same");

    // RecordTx Error
    static std::string NullKeyOrValue =
        getError(58201, "RecordTx Error,null key or value");
    static std::string NullKey = getError(58202, "RecordTx Error,null  key");

    // OntSdk Error
    static std::string WebsocketNotInit =
        getError(58301, "OntSdk Error,websocket not init");
    static std::string ConnRestfulNotInit =
        getError(58302, "OntSdk Error,connRestful not init");

    // abi error
    static std::string SetParamsValueValueNumError =
        getError(58401, "AbiFunction Error,setParamsValue value num error");
    static std::string ConnectUrlErr =
        getError(58402, "Interfaces Error,connect error:");

    static std::string ConnectUrlErr(std::string msg)
    {
        return getError(58403, "connect error:" + msg);
    }

    // WalletManager Error
    static std::string GetAccountByAddressErr =
        getError(58501, "WalletManager Error,getAccountByAddress err");

    static std::string OtherError(std::string msg)
    {
        return getError(59000, "Other Error," + msg);
    }
};

#endif