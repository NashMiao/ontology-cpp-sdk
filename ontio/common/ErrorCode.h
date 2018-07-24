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
    //account error
    static nlohmann::json InvalidParams;
    static nlohmann::json UnsupportedKeyType;
    static nlohmann::json InvalidMessage;
    static nlohmann::json WithoutPrivate;
    static nlohmann::json InvalidSM2Signature;
    static nlohmann::json AccountInvalidInput;
    static nlohmann::json AccountWithoutPublicKey;
    static nlohmann::json UnknownKeyType;
    static nlohmann::json NullInput;
    static nlohmann::json InvalidData;
    static nlohmann::json Decoded3bytesError;
    static nlohmann::json DecodePrikeyPassphraseError;
    static nlohmann::json PrikeyLengthError;
    static nlohmann::json EncryptedPriKeyError;
    static nlohmann::json encryptedPriKeyAddressPasswordErr;
    static nlohmann::json EncriptPrivateKeyError;

    //
    static nlohmann::json ParamLengthErr;
    static nlohmann::json ChecksumNotValidate;
    static nlohmann::json InputTooShort;
    static nlohmann::json UnknownCurve;
    static nlohmann::json UnknownCurveLabel;
    static nlohmann::json UnknownAsymmetricKeyType;
    static nlohmann::json InvalidSignatureData;
    static nlohmann::json InvalidSignatureDataLen;
    static nlohmann::json MalformedSignature;
    static nlohmann::json UnsupportedSignatureScheme;
    static nlohmann::json DataSignatureErr;
    static nlohmann::json UnSupportOperation;

    //Core Error
    static nlohmann::json TxDeserializeError;
    static nlohmann::json BlockDeserializeError;

    //merkle error
    static nlohmann::json MerkleVerifierErr;
    static nlohmann::json TargetHashesErr;

    static nlohmann::json ConstructedRootHashErr(std::string msg)
    {
        return getError(54003, "Other Error," + msg);
    }

    static nlohmann::json AsserFailedHashFullTree;
    static nlohmann::json LeftTreeFull;

    //SmartCodeTx Error
    static nlohmann::json SendRawTxError;
    static nlohmann::json TypeError;

    //OntIdTx Error
    static nlohmann::json NullCodeHash;
    static nlohmann::json ParamError;

    static nlohmann::json ParamErr(std::string msg)
    {
        return getError(58005, msg);
    }

    static nlohmann::json DidNull;
    static nlohmann::json NotExistCliamIssuer;
    static nlohmann::json NotFoundPublicKeyId;
    static nlohmann::json PublicKeyIdErr;
    static nlohmann::json BlockHeightNotMatch;
    static nlohmann::json NodesNotMatch;
    static nlohmann::json ResultIsNull;
    static nlohmann::json CreateOntIdClaimErr;
    static nlohmann::json VerifyOntIdClaimErr;
    static nlohmann::json WriteVarBytesError;
    static nlohmann::json SendRawTransactionPreExec;
    static nlohmann::json SenderAmtNotEqPasswordAmt;
    static nlohmann::json ExpireErr;
    static nlohmann::json GetStatusErr(std::string msg) { return getError(58017, "GetStatus Error," + msg); };

    //OntAsset Error
    static nlohmann::json AssetNameError;
    static nlohmann::json DidError;
    static nlohmann::json NullPkId;
    static nlohmann::json NullClaimId;
    static nlohmann::json AmountError;
    static nlohmann::json ParamLengthNotSame;

    //RecordTx Error
    static nlohmann::json NullKeyOrValue;
    static nlohmann::json NullKey;

    //OntSdk Error
    static nlohmann::json WebsocketNotInit;
    static nlohmann::json ConnRestfulNotInit;

    //abi error
    static nlohmann::json SetParamsValueValueNumError;
    static nlohmann::json ConnectUrlErr;

    static nlohmann::json GenConnectUrlErr(std::string msg)
    {
        return getError(58403, "connect error:" + msg);
    }

    //WalletManager Error
    static nlohmann::json GetAccountByAddressErr;

    static nlohmann::json OtherError(std::string msg)
    {
        return getError(59000, "Other Error," + msg);
    }

  public:
    //account error
    static std::string StrInvalidParams;
    static std::string StrUnsupportedKeyType;
    static std::string StrInvalidMessage;
    static std::string StrWithoutPrivate;
    static std::string StrInvalidSM2Signature;
    static std::string StrAccountInvalidInput;
    static std::string StrAccountWithoutPublicKey;
    static std::string StrUnknownKeyType;
    static std::string StrNullInput;
    static std::string StrInvalidData;
    static std::string StrDecoded3bytesError;
    static std::string StrDecodePrikeyPassphraseError;
    static std::string StrPrikeyLengthError;
    static std::string StrEncryptedPriKeyError;
    static std::string StrencryptedPriKeyAddressPasswordErr;
    static std::string StrEncriptPrivateKeyError;

    //
    static std::string StrParamLengthErr;
    static std::string StrChecksumNotValidate;
    static std::string StrInputTooShort;
    static std::string StrUnknownCurve;
    static std::string StrUnknownCurveLabel;
    static std::string StrUnknownAsymmetricKeyType;
    static std::string StrInvalidSignatureData;
    static std::string StrInvalidSignatureDataLen;
    static std::string StrMalformedSignature;
    static std::string StrUnsupportedSignatureScheme;
    static std::string StrDataSignatureErr;
    static std::string StrUnSupportOperation;

    //Core Error
    static std::string StrTxDeserializeError;
    static std::string StrBlockDeserializeError;

    //merkle error
    static std::string StrMerkleVerifierErr;
    static std::string StrTargetHashesErr;

    static std::string StrConstructedRootHashErr(std::string msg)
    {
        return getStrError(54003, "Other Error," + msg);
    }

    static std::string StrAsserFailedHashFullTree;
    static std::string StrLeftTreeFull;

    //SmartCodeTx Error
    static std::string StrSendRawTxError;
    static std::string StrTypeError;

    //OntIdTx Error
    static std::string StrNullCodeHash;
    static std::string StrParamError;

    static std::string StrParamErr(std::string msg)
    {
        return getStrError(58005, msg);
    }

    static std::string StrDidNull;
    static std::string StrNotExistCliamIssuer;
    static std::string StrNotFoundPublicKeyId;
    static std::string StrPublicKeyIdErr;
    static std::string StrBlockHeightNotMatch;
    static std::string StrNodesNotMatch;
    static std::string StrResultIsNull;
    static std::string StrCreateOntIdClaimErr;
    static std::string StrVerifyOntIdClaimErr;
    static std::string StrWriteVarBytesError;
    static std::string StrSendRawTransactionPreExec;
    static std::string StrSenderAmtNotEqPasswordAmt;
    static std::string StrExpireErr;
    static std::string StrGetStatusErr(std::string msg) { return getStrError(58017, "GetStatus Error," + msg); };

    //OntAsset Error
    static std::string StrAssetNameError;
    static std::string StrDidError;
    static std::string StrNullPkId;
    static std::string StrNullClaimId;
    static std::string StrAmountError;
    static std::string StrParamLengthNotSame;

    //RecordTx Error
    static std::string StrNullKeyOrValue;
    static std::string StrNullKey;

    //OntSdk Error
    static std::string StrWebsocketNotInit;
    static std::string StrConnRestfulNotInit;

    //abi error
    static std::string StrSetParamsValueValueNumError;
    static std::string StrConnectUrlErr;
    static std::string GenStrConnectUrlErr(std::string msg)
    {
        return getStrError(58403, "connect error:" + msg);
    }

    //WalletManager Error
    static std::string StrGetAccountByAddressErr;
    static std::string StrOtherError(std::string msg)
    {
        return getStrError(59000, "Other Error," + msg);
    }
};

//account error
nlohmann::json ErrorCode::InvalidParams = getError(51001, "Account Error,invalid params");
nlohmann::json ErrorCode::UnsupportedKeyType = getError(51002, "Account Error,unsupported key type");
nlohmann::json ErrorCode::InvalidMessage = getError(51003, "Account Error,invalid message");
nlohmann::json ErrorCode::WithoutPrivate = getError(51004, "Account Error,account without private key cannot generate signature");
nlohmann::json ErrorCode::InvalidSM2Signature = getError(51005, "Account Error,invalid SM2 signature parameter, ID (String) excepted");
nlohmann::json ErrorCode::AccountInvalidInput = getError(51006, "Account Error,account invalid input");
nlohmann::json ErrorCode::AccountWithoutPublicKey = getError(51007, "Account Error,account without public key cannot verify signature");
nlohmann::json ErrorCode::UnknownKeyType = getError(51008, "Account Error,unknown key type");
nlohmann::json ErrorCode::NullInput = getError(51009, "Account Error,null input");
nlohmann::json ErrorCode::InvalidData = getError(51010, "Account Error,invalid data");
nlohmann::json ErrorCode::Decoded3bytesError = getError(51011, "Account Error,decoded 3 bytes error");
nlohmann::json ErrorCode::DecodePrikeyPassphraseError = getError(51012, "Account Error,decode prikey passphrase error.");
nlohmann::json ErrorCode::PrikeyLengthError = getError(51013, "Account Error,Prikey length error");
nlohmann::json ErrorCode::EncryptedPriKeyError = getError(51014, "Account Error,Prikey length error");
nlohmann::json ErrorCode::encryptedPriKeyAddressPasswordErr = getError(51015, "Account Error,encryptedPriKey address password not match.");
nlohmann::json ErrorCode::EncriptPrivateKeyError = getError(51016, "Account Error, encript privatekey error,");

//
nlohmann::json ErrorCode::ParamLengthErr = getError(52001, "Uint256 Error,param length error");
nlohmann::json ErrorCode::ChecksumNotValidate = getError(52002, "Base58 Error,Checksum does not validate");
nlohmann::json ErrorCode::InputTooShort = getError(52003, "Base58 Error,Input too short");
nlohmann::json ErrorCode::UnknownCurve = getError(52004, "Curve Error,unknown curve");
nlohmann::json ErrorCode::UnknownCurveLabel = getError(52005, "Curve Error,unknown curve label");
nlohmann::json ErrorCode::UnknownAsymmetricKeyType = getError(52006, "keyType Error,unknown asymmetric key type");
nlohmann::json ErrorCode::InvalidSignatureData = getError(52007, "Signature Error,invalid signature data: missing the ID parameter for SM3withSM2");
nlohmann::json ErrorCode::InvalidSignatureDataLen = getError(52008, "Signature Error,invalid signature data length");
nlohmann::json ErrorCode::MalformedSignature = getError(52009, "Signature Error,malformed signature");
nlohmann::json ErrorCode::UnsupportedSignatureScheme = getError(52010, "Signature Error,unsupported signature scheme:");
nlohmann::json ErrorCode::DataSignatureErr = getError(52011, "Signature Error,Data signature error.");
nlohmann::json ErrorCode::UnSupportOperation = getError(52012, "Address Error, UnsupportedOperationException");

//Core Error
nlohmann::json ErrorCode::TxDeserializeError = getError(53001, "Core Error,Transaction deserialize failed");
nlohmann::json ErrorCode::BlockDeserializeError = getError(53002, "Core Error,Block deserialize failed");

//merkle error
nlohmann::json ErrorCode::MerkleVerifierErr = getError(54001, "Wrong params: the tree size is smaller than the leaf index");
nlohmann::json ErrorCode::TargetHashesErr = getError(54002, "targetHashes error");

nlohmann::json ErrorCode::AsserFailedHashFullTree = getError(54004, "assert failed in hash full tree");
nlohmann::json ErrorCode::LeftTreeFull = getError(54005, "left tree always full");

//SmartCodeTx Error
nlohmann::json ErrorCode::SendRawTxError = getError(58001, "SmartCodeTx Error,sendRawTransaction error");
nlohmann::json ErrorCode::TypeError = getError(58002, "SmartCodeTx Error,type error");

//OntIdTx Error
nlohmann::json ErrorCode::NullCodeHash = getError(58003, "OntIdTx Error,null codeHash");
nlohmann::json ErrorCode::ParamError = getError(58004, "param error,");

nlohmann::json ErrorCode::DidNull = getError(58006, "OntIdTx Error,SendDid or receiverDid is null in metaData");
nlohmann::json ErrorCode::NotExistCliamIssuer = getError(58007, "OntIdTx Error,Not exist cliam issuer");
nlohmann::json ErrorCode::NotFoundPublicKeyId = getError(58008, "OntIdTx Error,not found PublicKeyId");
nlohmann::json ErrorCode::PublicKeyIdErr = getError(58009, "OntIdTx Error,PublicKeyId err");
nlohmann::json ErrorCode::BlockHeightNotMatch = getError(58010, "OntIdTx Error,BlockHeight not match");
nlohmann::json ErrorCode::NodesNotMatch = getError(58011, "OntIdTx Error,nodes not match");
nlohmann::json ErrorCode::ResultIsNull = getError(58012, "OntIdTx Error,result is null");
nlohmann::json ErrorCode::CreateOntIdClaimErr = getError(58013, "OntIdTx Error, createOntIdClaim error");
nlohmann::json ErrorCode::VerifyOntIdClaimErr = getError(58014, "OntIdTx Error, verifyOntIdClaim error");
nlohmann::json ErrorCode::WriteVarBytesError = getError(58015, "OntIdTx Error, writeVarBytes error");
nlohmann::json ErrorCode::SendRawTransactionPreExec = getError(58016, "OntIdTx Error, sendRawTransaction PreExec error");
nlohmann::json ErrorCode::SenderAmtNotEqPasswordAmt = getError(58017, "OntIdTx Error, senders amount is not equal password amount");
nlohmann::json ErrorCode::ExpireErr = getError(58017, "OntIdTx Error, expire is wrong");

//OntAsset Error
nlohmann::json ErrorCode::AssetNameError = getError(58101, "OntAsset Error,asset name error");
nlohmann::json ErrorCode::DidError = getError(58102, "OntAsset Error,Did error");
nlohmann::json ErrorCode::NullPkId = getError(58103, "OntAsset Error,null pkId");
nlohmann::json ErrorCode::NullClaimId = getError(58104, "OntAsset Error,null claimId");
nlohmann::json ErrorCode::AmountError = getError(58105, "OntAsset Error,amount or gas is less than or equal to zero");
nlohmann::json ErrorCode::ParamLengthNotSame = getError(58105, "OntAsset Error,param length is not the same");

//RecordTx Error
nlohmann::json ErrorCode::NullKeyOrValue = getError(58201, "RecordTx Error,null key or value");
nlohmann::json ErrorCode::NullKey = getError(58202, "RecordTx Error,null  key");

//OntSdk Error
nlohmann::json ErrorCode::WebsocketNotInit = getError(58301, "OntSdk Error,websocket not init");
nlohmann::json ErrorCode::ConnRestfulNotInit = getError(58302, "OntSdk Error,connRestful not init");

//abi error
nlohmann::json ErrorCode::SetParamsValueValueNumError = getError(58401, "AbiFunction Error,setParamsValue value num error");
nlohmann::json ErrorCode::ConnectUrlErr = getError(58402, "Interfaces Error,connect error:");

//WalletManager Error
nlohmann::json ErrorCode::GetAccountByAddressErr = getError(58501, "WalletManager Error,getAccountByAddress err");

//account error
std::string ErrorCode::StrInvalidParams = getStrError(51001, "Account Error,invalid params");
std::string ErrorCode::StrUnsupportedKeyType = getStrError(51002, "Account Error,unsupported key type");
std::string ErrorCode::StrInvalidMessage = getStrError(51003, "Account Error,invalid message");
std::string ErrorCode::StrWithoutPrivate = getStrError(51004, "Account Error,account without private key cannot generate signature");
std::string ErrorCode::StrInvalidSM2Signature = getStrError(51005, "Account Error,invalid SM2 signature parameter, ID (String) excepted");
std::string ErrorCode::StrAccountInvalidInput = getStrError(51006, "Account Error,account invalid input");
std::string ErrorCode::StrAccountWithoutPublicKey = getStrError(51007, "Account Error,account without public key cannot verify signature");
std::string ErrorCode::StrUnknownKeyType = getStrError(51008, "Account Error,unknown key type");
std::string ErrorCode::StrNullInput = getStrError(51009, "Account Error,null input");
std::string ErrorCode::StrInvalidData = getStrError(51010, "Account Error,invalid data");
std::string ErrorCode::StrDecoded3bytesError = getStrError(51011, "Account Error,decoded 3 bytes error");
std::string ErrorCode::StrDecodePrikeyPassphraseError = getStrError(51012, "Account Error,decode prikey passphrase error.");
std::string ErrorCode::StrPrikeyLengthError = getStrError(51013, "Account Error,Prikey length error");
std::string ErrorCode::StrEncryptedPriKeyError = getStrError(51014, "Account Error,Prikey length error");
std::string ErrorCode::StrencryptedPriKeyAddressPasswordErr = getStrError(51015, "Account Error,encryptedPriKey address password not match.");
std::string ErrorCode::StrEncriptPrivateKeyError = getStrError(51016, "Account Error, encript privatekey error,");

//
std::string ErrorCode::StrParamLengthErr = getStrError(52001, "Uint256 Error,param length error");
std::string ErrorCode::StrChecksumNotValidate = getStrError(52002, "Base58 Error,Checksum does not validate");
std::string ErrorCode::StrInputTooShort = getStrError(52003, "Base58 Error,Input too short");
std::string ErrorCode::StrUnknownCurve = getStrError(52004, "Curve Error,unknown curve");
std::string ErrorCode::StrUnknownCurveLabel = getStrError(52005, "Curve Error,unknown curve label");
std::string ErrorCode::StrUnknownAsymmetricKeyType = getStrError(52006, "keyType Error,unknown asymmetric key type");
std::string ErrorCode::StrInvalidSignatureData = getStrError(52007, "Signature Error,invalid signature data: missing the ID parameter for SM3withSM2");
std::string ErrorCode::StrInvalidSignatureDataLen = getStrError(52008, "Signature Error,invalid signature data length");
std::string ErrorCode::StrMalformedSignature = getStrError(52009, "Signature Error,malformed signature");
std::string ErrorCode::StrUnsupportedSignatureScheme = getStrError(52010, "Signature Error,unsupported signature scheme:");
std::string ErrorCode::StrDataSignatureErr = getStrError(52011, "Signature Error,Data signature error.");
std::string ErrorCode::StrUnSupportOperation = getStrError(52012, "Address Error, UnsupportedOperationException");

//Core Error
std::string ErrorCode::StrTxDeserializeError = getStrError(53001, "Core Error,Transaction deserialize failed");
std::string ErrorCode::StrBlockDeserializeError = getStrError(53002, "Core Error,Block deserialize failed");

//merkle error
std::string ErrorCode::StrMerkleVerifierErr = getStrError(54001, "Wrong params: the tree size is smaller than the leaf index");
std::string ErrorCode::StrTargetHashesErr = getStrError(54002, "targetHashes error");

std::string ErrorCode::StrAsserFailedHashFullTree = getStrError(54004, "assert failed in hash full tree");
std::string ErrorCode::StrLeftTreeFull = getStrError(54005, "left tree always full");

//SmartCodeTx Error
std::string ErrorCode::StrSendRawTxError = getStrError(58001, "SmartCodeTx Error,sendRawTransaction error");
std::string ErrorCode::StrTypeError = getStrError(58002, "SmartCodeTx Error,type error");

//OntIdTx Error
std::string ErrorCode::StrNullCodeHash = getStrError(58003, "OntIdTx Error,null codeHash");
std::string ErrorCode::StrParamError = getStrError(58004, "param error,");

std::string ErrorCode::StrDidNull = getStrError(58006, "OntIdTx Error,SendDid or receiverDid is null in metaData");
std::string ErrorCode::StrNotExistCliamIssuer = getStrError(58007, "OntIdTx Error,Not exist cliam issuer");
std::string ErrorCode::StrNotFoundPublicKeyId = getStrError(58008, "OntIdTx Error,not found PublicKeyId");
std::string ErrorCode::StrPublicKeyIdErr = getStrError(58009, "OntIdTx Error,PublicKeyId err");
std::string ErrorCode::StrBlockHeightNotMatch = getStrError(58010, "OntIdTx Error,BlockHeight not match");
std::string ErrorCode::StrNodesNotMatch = getStrError(58011, "OntIdTx Error,nodes not match");
std::string ErrorCode::StrResultIsNull = getStrError(58012, "OntIdTx Error,result is null");
std::string ErrorCode::StrCreateOntIdClaimErr = getStrError(58013, "OntIdTx Error, createOntIdClaim error");
std::string ErrorCode::StrVerifyOntIdClaimErr = getStrError(58014, "OntIdTx Error, verifyOntIdClaim error");
std::string ErrorCode::StrWriteVarBytesError = getStrError(58015, "OntIdTx Error, writeVarBytes error");
std::string ErrorCode::StrSendRawTransactionPreExec = getStrError(58016, "OntIdTx Error, sendRawTransaction PreExec error");
std::string ErrorCode::StrSenderAmtNotEqPasswordAmt = getStrError(58017, "OntIdTx Error, senders amount is not equal password amount");
std::string ErrorCode::StrExpireErr = getStrError(58017, "OntIdTx Error, expire is wrong");

//OntAsset Error
std::string ErrorCode::StrAssetNameError = getStrError(58101, "OntAsset Error,asset name error");
std::string ErrorCode::StrDidError = getStrError(58102, "OntAsset Error,Did error");
std::string ErrorCode::StrNullPkId = getStrError(58103, "OntAsset Error,null pkId");
std::string ErrorCode::StrNullClaimId = getStrError(58104, "OntAsset Error,null claimId");
std::string ErrorCode::StrAmountError = getStrError(58105, "OntAsset Error,amount or gas is less than or equal to zero");
std::string ErrorCode::StrParamLengthNotSame = getStrError(58105, "OntAsset Error,param length is not the same");

//RecordTx Error
std::string ErrorCode::StrNullKeyOrValue = getStrError(58201, "RecordTx Error,null key or value");
std::string ErrorCode::StrNullKey = getStrError(58202, "RecordTx Error,null  key");

//OntSdk Error
std::string ErrorCode::StrWebsocketNotInit = getStrError(58301, "OntSdk Error,websocket not init");
std::string ErrorCode::StrConnRestfulNotInit = getStrError(58302, "OntSdk Error,connRestful not init");

//abi error
std::string ErrorCode::StrSetParamsValueValueNumError = getStrError(58401, "AbiFunction Error,setParamsValue value num error");
std::string ErrorCode::StrConnectUrlErr = getStrError(58402, "Interfaces Error,connect error:");

//WalletManager Error
std::string ErrorCode::StrGetAccountByAddressErr = getStrError(58501, "WalletManager Error,getAccountByAddress err");
#endif