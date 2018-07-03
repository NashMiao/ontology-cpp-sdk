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
    static nlohmann::json InvalidSM2Signature = getError(
        51005,
        "Account Error,invalid SM2 signature parameter, ID (String) excepted");
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

    static nlohmann::json ConstructedRootHashErr(String msg)
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

    static nlohmann::json ParamErr(String msg) { return getError(58005, msg); }

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
    static nlohmann::json GetStatusErr(String msg)
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
};

#endif