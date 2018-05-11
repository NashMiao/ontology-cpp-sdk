/**
 * list transaction types
 */
enum TransactionType
{
    Bookkeeping = 0x00,
    Bookkeeper = 0x02,
    Claim = 0x03,
    Enrollment = 0x04,
    Vote = 0x05,
    DeployCode = 0xd0,
    InvokeCode = 0xd1,
};