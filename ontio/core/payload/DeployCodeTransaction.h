#ifndef DEPLOYCODETRANSACTION_H
#define DEPLOYCODETRANSACTION_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <vector>

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "../transaction/Transaction.h"
#include "../transaction/TransactionType.h"

class DeployCodeTransaction : public Transaction
{
  public:
    std::vector<unsigned char> code;
    bool needStorage;
    std::string name;
    std::string version;
    std::string author;
    std::string email;
    std::string description;

  public:
    DeployCodeTransaction() : Transaction(TransactionType::DeployCode) {}

  protected:
    void deserializeExclusiveData(BinaryReader *reader) override
    {
        try
        {
            code = reader->readVarBytes();
            needStorage = reader->readBool();
            name = reader->readVarString();
            version = reader->readVarString();
            author = reader->readVarString();
            email = reader->readVarString();
            description = reader->readVarString();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void serializeExclusiveData(BinaryWriter* writer) override
    {
        try
        {
            writer->writeVarBytes(code);
            writer->writeBoolean(needStorage);
            writer->writeVarString(name);
            writer->writeVarString(version);
            writer->writeVarString(author);
            writer->writeVarString(email);
            writer->writeVarString(description);
        }
        catch (const std::exception &e){
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif