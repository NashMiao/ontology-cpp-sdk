#ifndef ERRORCODE_H
#define ERRORCODE_H

#include <nlohmann/json.hpp>
#include <string>

class ErrorCode
{
  private:
    static nlohmann::json getError(int code, std::string msg)
    {
        nlohmann::json json_map = {{"Error", code}, {"Desc", msg}};
        return json_map;
    }

    static std::string getStrError(int code, std::string msg)
    {
        nlohmann::json json_map = {{"Error", code}, {"Desc", msg}};
        return json_map.dump();
    }

    // nlohmann::json
  public:
    // account error
    static nlohmann::json InvalidParams =
        getError(51001, "Account Error,invalid params");
    static nlohmann::json UnsupportedKeyType =
        getError(51002, "Account Error,unsupported key type");
    static nlohmann::json InvalidMessage =
        getError(51003, "Account Error,invalid message");
    static nlohmann::json WithoutPrivate = getError(
        51004,
        "Account Error,account without private key cannot generate signature");
    static nlohmann::json InvalidSM2Signature =
        getError(51005, "Account Error,invalid SM2 signature parameter, ID "
                        "(std::string) excepted");
    static nlohmann::json AccountInvalidInput =
        getError(51006, "Account Error,account invalid input");
    static nlohmann::json AccountWithoutPublicKey = getError(
        51007,
        "Account Error,account without public key cannot verify signature");
    static nlohmann::json UnknownKeyType =
        getError(51008, "Account Error,unknown key type");
    static nlohmann::json NullInput = getError(51009, "Account Error,null input");
    static nlohmann::json InvalidData =
        getError(51010, "Account Error,invalid data");
    static nlohmann::json Decoded3bytesError =
        getError(51011, "Account Error,decoded 3 bytes error");
    static nlohmann::json DecodePrikeyPassphraseError =
        getError(51012, "Account Error,decode prikey passphrase error.");
    static nlohmann::json PrikeyLengthError =
        getError(51013, "Account Error,Prikey length error");
    static nlohmann::json EncryptedPriKeyError =
        getError(51014, "Account Error,Prikey length error");
    static nlohmann::json encryptedPriKeyAddressPasswordErr = getError(
        51015, "Account Error,encryptedPriKey address password not match.");
    static nlohmann::json EncriptPrivateKeyError =
        getError(51016, "Account Error, encript privatekey error,");

    //
    static nlohmann::json ParamLengthErr =
        getError(52001, "Uint256 Error,param length error");
    static nlohmann::json ChecksumNotValidate =
        getError(52002, "Base58 Error,Checksum does not validate");
    static nlohmann::json InputTooShort =
        getError(52003, "Base58 Error,Input too short");
    static nlohmann::json UnknownCurve =
        getError(52004, "Curve Error,unknown curve");
    static nlohmann::json UnknownCurveLabel =
        getError(52005, "Curve Error,unknown curve label");
    static nlohmann::json UnknownAsymmetricKeyType =
        getError(52006, "keyType Error,unknown asymmetric key type");
    static nlohmann::json InvalidSignatureData =
        getError(52007, "Signature Error,invalid signature data: missing the ID "
                        "parameter for SM3withSM2");
    static nlohmann::json InvalidSignatureDataLen =
        getError(52008, "Signature Error,invalid signature data length");
    static nlohmann::json MalformedSignature =
        getError(52009, "Signature Error,malformed signature");
    static nlohmann::json UnsupportedSignatureScheme =
        getError(52010, "Signature Error,unsupported signature scheme:");
    static nlohmann::json DataSignatureErr =
        getError(52011, "Signature Error,Data signature error.");
    static nlohmann::json UnSupportOperation =
        getError(52012, "Address Error, UnsupportedOperationException");

    // Core Error
    static nlohmann::json TxDeserializeError =
        getError(53001, "Core Error,Transaction deserialize failed");
    static nlohmann::json BlockDeserializeError =
        getError(53002, "Core Error,Block deserialize failed");

    // merkle error
    static nlohmann::json MerkleVerifierErr = getError(
        54001, "Wrong params: the tree size is smaller than the leaf index");
    static nlohmann::json TargetHashesErr = getError(54002, "targetHashes error");

    static nlohmann::json ConstructedRootHashErr(std::string msg)
    {
        return getError(54003, "Other Error," + msg);
    }

    static nlohmann::json AsserFailedHashFullTree =
        getError(54004, "assert failed in hash full tree");
    static nlohmann::json LeftTreeFull = getError(54005, "left tree always full");

    // SmartCodeTx Error
    static nlohmann::json SendRawTxError =
        getError(58001, "SmartCodeTx Error,sendRawTransaction error");
    static nlohmann::json TypeError =
        getError(58002, "SmartCodeTx Error,type error");

    // OntIdTx Error
    static nlohmann::json NullCodeHash =
        getError(58003, "OntIdTx Error,null codeHash");
    static nlohmann::json ParamError = getError(58004, "param error,");

    static nlohmann::json ParamErr(std::string msg)
    {
        return getError(58005, msg);
    }

    static nlohmann::json DidNull = getError(
        58006, "OntIdTx Error,SendDid or receiverDid is null in metaData");
    static nlohmann::json NotExistCliamIssuer =
        getError(58007, "OntIdTx Error,Not exist cliam issuer");
    static nlohmann::json NotFoundPublicKeyId =
        getError(58008, "OntIdTx Error,not found PublicKeyId");
    static nlohmann::json PublicKeyIdErr =
        getError(58009, "OntIdTx Error,PublicKeyId err");
    static nlohmann::json BlockHeightNotMatch =
        getError(58010, "OntIdTx Error,BlockHeight not match");
    static nlohmann::json NodesNotMatch =
        getError(58011, "OntIdTx Error,nodes not match");
    static nlohmann::json ResultIsNull =
        getError(58012, "OntIdTx Error,result is null");
    static nlohmann::json CreateOntIdClaimErr =
        getError(58013, "OntIdTx Error, createOntIdClaim error");
    static nlohmann::json VerifyOntIdClaimErr =
        getError(58014, "OntIdTx Error, verifyOntIdClaim error");
    static nlohmann::json WriteVarBytesError =
        getError(58015, "OntIdTx Error, writeVarBytes error");
    static nlohmann::json SendRawTransactionPreExec =
        getError(58016, "OntIdTx Error, sendRawTransaction PreExec error");
    static nlohmann::json SenderAmtNotEqPasswordAmt = getError(
        58017, "OntIdTx Error, senders amount is not equal password amount");
    static nlohmann::json ExpireErr =
        getError(58017, "OntIdTx Error, expire is wrong");
    static nlohmann::json GetStatusErr(std::string msg)
    {
        return getError(58017, "GetStatus Error," + msg);
    };

    // OntAsset Error
    static nlohmann::json AssetNameError =
        getError(58101, "OntAsset Error,asset name error");
    static nlohmann::json DidError = getError(58102, "OntAsset Error,Did error");
    static nlohmann::json NullPkId = getError(58103, "OntAsset Error,null pkId");
    static nlohmann::json NullClaimId =
        getError(58104, "OntAsset Error,null claimId");
    static nlohmann::json AmountError = getError(
        58105, "OntAsset Error,amount or gas is less than or equal to zero");
    static nlohmann::json ParamLengthNotSame =
        getError(58105, "OntAsset Error,param length is not the same");

    // RecordTx Error
    static nlohmann::json NullKeyOrValue =
        getError(58201, "RecordTx Error,null key or value");
    static nlohmann::json NullKey = getError(58202, "RecordTx Error,null  key");

    // OntSdk Error
    static nlohmann::json WebsocketNotInit =
        getError(58301, "OntSdk Error,websocket not init");
    static nlohmann::json ConnRestfulNotInit =
        getError(58302, "OntSdk Error,connRestful not init");

    // abi error
    static nlohmann::json SetParamsValueValueNumError =
        getError(58401, "AbiFunction Error,setParamsValue value num error");
    static nlohmann::json ConnectUrlErr =
        getError(58402, "Interfaces Error,connect error:");

    static nlohmann::json ConnectUrlErr(std::string msg)
    {
        return getError(58403, "connect error:" + msg);
    }

    // WalletManager Error
    static nlohmann::json GetAccountByAddressErr =
        getError(58501, "WalletManager Error,getAccountByAddress err");

    static nlohmann::json OtherError(std::string msg)
    {
        return getError(59000, "Other Error," + msg);
    }

    // std::string
  public:
    // string account error
    static std::string InvalidParams =
        getStrError(51001, "Account Error,invalid params");
    static std::string UnsupportedKeyType =
        getStrError(51002, "Account Error,unsupported key type");
    static std::string InvalidMessage =
        getStrError(51003, "Account Error,invalid message");
    static std::string WithoutPrivate = getStrError(
        51004,
        "Account Error,account without private key cannot generate signature");
    static std::string InvalidSM2Signature =
        getStrError(51005, "Account Error,invalid SM2 signature parameter, ID "
                           "(std::string) excepted");
    static std::string AccountInvalidInput =
        getStrError(51006, "Account Error,account invalid input");
    static std::string AccountWithoutPublicKey = getStrError(
        51007,
        "Account Error,account without public key cannot verify signature");
    static std::string UnknownKeyType =
        getStrError(51008, "Account Error,unknown key type");
    static std::string NullInput = getStrError(51009, "Account Error,null input");
    static std::string InvalidData =
        getStrError(51010, "Account Error,invalid data");
    static std::string Decoded3bytesError =
        getStrError(51011, "Account Error,decoded 3 bytes error");
    static std::string DecodePrikeyPassphraseError =
        getStrError(51012, "Account Error,decode prikey passphrase error.");
    static std::string PrikeyLengthError =
        getStrError(51013, "Account Error,Prikey length error");
    static std::string EncryptedPriKeyError =
        getStrError(51014, "Account Error,Prikey length error");
    static std::string encryptedPriKeyAddressPasswordErr = getStrError(
        51015, "Account Error,encryptedPriKey address password not match.");
    static std::string EncriptPrivateKeyError =
        getStrError(51016, "Account Error, encript privatekey error,");

    //
    static std::string ParamLengthErr =
        getStrError(52001, "Uint256 Error,param length error");
    static std::string ChecksumNotValidate =
        getStrError(52002, "Base58 Error,Checksum does not validate");
    static std::string InputTooShort =
        getStrError(52003, "Base58 Error,Input too short");
    static std::string UnknownCurve =
        getStrError(52004, "Curve Error,unknown curve");
    static std::string UnknownCurveLabel =
        getStrError(52005, "Curve Error,unknown curve label");
    static std::string UnknownAsymmetricKeyType =
        getStrError(52006, "keyType Error,unknown asymmetric key type");
    static std::string InvalidSignatureData = getStrError(
        52007, "Signature Error,invalid signature data: missing the ID "
               "parameter for SM3withSM2");
    static std::string InvalidSignatureDataLen =
        getStrError(52008, "Signature Error,invalid signature data length");
    static std::string MalformedSignature =
        getStrError(52009, "Signature Error,malformed signature");
    static std::string UnsupportedSignatureScheme =
        getStrError(52010, "Signature Error,unsupported signature scheme:");
    static std::string DataSignatureErr =
        getStrError(52011, "Signature Error,Data signature error.");
    static std::string UnSupportOperation =
        getStrError(52012, "Address Error, UnsupportedOperationException");

    // string Core Error
    static std::string TxDeserializeError =
        getStrError(53001, "Core Error,Transaction deserialize failed");
    static std::string BlockDeserializeError =
        getStrError(53002, "Core Error,Block deserialize failed");

    // string merkle error
    static std::string MerkleVerifierErr = getStrError(
        54001, "Wrong params: the tree size is smaller than the leaf index");
    static std::string TargetHashesErr = getStrError(54002, "targetHashes error");

    static std::string ConstructedRootHashErr(std::string msg)
    {
        return getStrError(54003, "Other Error," + msg);
    }

    static std::string AsserFailedHashFullTree =
        getStrError(54004, "assert failed in hash full tree");
    static std::string LeftTreeFull = getStrError(54005, "left tree always full");

    // string SmartCodeTx Error
    static std::string SendRawTxError =
        getStrError(58001, "SmartCodeTx Error,sendRawTransaction error");
    static std::string TypeError =
        getStrError(58002, "SmartCodeTx Error,type error");

    // string OntIdTx Error
    static std::string NullCodeHash =
        getStrError(58003, "OntIdTx Error,null codeHash");
    static std::string ParamError = getStrError(58004, "param error,");

    static std::string StrParamErr(std::string msg)
    {
        return getStrError(58005, msg);
    }

    static std::string DidNull = getStrError(
        58006, "OntIdTx Error,SendDid or receiverDid is null in metaData");
    static std::string NotExistCliamIssuer =
        getStrError(58007, "OntIdTx Error,Not exist cliam issuer");
    static std::string NotFoundPublicKeyId =
        getStrError(58008, "OntIdTx Error,not found PublicKeyId");
    static std::string PublicKeyIdErr =
        getStrError(58009, "OntIdTx Error,PublicKeyId err");
    static std::string BlockHeightNotMatch =
        getStrError(58010, "OntIdTx Error,BlockHeight not match");
    static std::string NodesNotMatch =
        getStrError(58011, "OntIdTx Error,nodes not match");
    static std::string ResultIsNull =
        getStrError(58012, "OntIdTx Error,result is null");
    static std::string CreateOntIdClaimErr =
        getStrError(58013, "OntIdTx Error, createOntIdClaim error");
    static std::string VerifyOntIdClaimErr =
        getStrError(58014, "OntIdTx Error, verifyOntIdClaim error");
    static std::string WriteVarBytesError =
        getStrError(58015, "OntIdTx Error, writeVarBytes error");
    static std::string SendRawTransactionPreExec =
        getStrError(58016, "OntIdTx Error, sendRawTransaction PreExec error");
    static std::string SenderAmtNotEqPasswordAmt = getStrError(
        58017, "OntIdTx Error, senders amount is not equal password amount");
    static std::string ExpireErr =
        getStrError(58017, "OntIdTx Error, expire is wrong");
    static std::string GetStatusErr(std::string msg)
    {
        return getStrError(58017, "GetStatus Error," + msg);
    };

    // string OntAsset Error
    static std::string AssetNameError =
        getStrError(58101, "OntAsset Error,asset name error");
    static std::string DidError = getStrError(58102, "OntAsset Error,Did error");
    static std::string NullPkId = getStrError(58103, "OntAsset Error,null pkId");
    static std::string NullClaimId =
        getStrError(58104, "OntAsset Error,null claimId");
    static std::string AmountError = getStrError(
        58105, "OntAsset Error,amount or gas is less than or equal to zero");
    static std::string ParamLengthNotSame =
        getStrError(58105, "OntAsset Error,param length is not the same");

    // string RecordTx Error
    static std::string NullKeyOrValue =
        getStrError(58201, "RecordTx Error,null key or value");
    static std::string NullKey = getStrError(58202, "RecordTx Error,null  key");

    // string OntSdk Error
    static std::string WebsocketNotInit =
        getStrError(58301, "OntSdk Error,websocket not init");
    static std::string ConnRestfulNotInit =
        getStrError(58302, "OntSdk Error,connRestful not init");

    // string abi error
    static std::string SetParamsValueValueNumError =
        getStrError(58401, "AbiFunction Error,setParamsValue value num error");
    static std::string ConnectUrlErr =
        getStrError(58402, "Interfaces Error,connect error:");

    static std::string ConnectUrlErr(std::string msg)
    {
        return getStrError(58403, "connect error:" + msg);
    }

    // string WalletManager Error
    static std::string GetAccountByAddressErr =
        getStrError(58501, "WalletManager Error,getAccountByAddress err");

    static std::string OtherError(std::string msg)
    {
        return getStrError(59000, "Other Error," + msg);
    }
};

#endif