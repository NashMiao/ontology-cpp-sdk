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
#endif