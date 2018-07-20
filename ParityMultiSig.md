# 以太坊Parity多重签名设计

<!-- TOC -->

- [以太坊Parity多重签名设计](#%E4%BB%A5%E5%A4%AA%E5%9D%8Aparity%E5%A4%9A%E9%87%8D%E7%AD%BE%E5%90%8D%E8%AE%BE%E8%AE%A1)
    - [使用体验](#%E4%BD%BF%E7%94%A8%E4%BD%93%E9%AA%8C)
        - [界面](#%E7%95%8C%E9%9D%A2)
        - [助记词](#%E5%8A%A9%E8%AE%B0%E8%AF%8D)
    - [多重签名](#%E5%A4%9A%E9%87%8D%E7%AD%BE%E5%90%8D)
        - [Wallet.sol文件](#walletsol%E6%96%87%E4%BB%B6)
            - [文件结构](#%E6%96%87%E4%BB%B6%E7%BB%93%E6%9E%84)
            - [multiowned合约](#multiowned%E5%90%88%E7%BA%A6)
            - [multisig合约](#multisig%E5%90%88%E7%BA%A6)
            - [daylimit合约](#daylimit%E5%90%88%E7%BA%A6)
        - [多签钱包的部署](#%E5%A4%9A%E7%AD%BE%E9%92%B1%E5%8C%85%E7%9A%84%E9%83%A8%E7%BD%B2)
        - [多签钱包的使用](#%E5%A4%9A%E7%AD%BE%E9%92%B1%E5%8C%85%E7%9A%84%E4%BD%BF%E7%94%A8)
            - [getOwner与isOwner的使用](#getowner%E4%B8%8Eisowner%E7%9A%84%E4%BD%BF%E7%94%A8)
            - [setDailyLimit](#setdailylimit)
            - [向多签钱包转账](#%E5%90%91%E5%A4%9A%E7%AD%BE%E9%92%B1%E5%8C%85%E8%BD%AC%E8%B4%A6)
            - [多签示例](#%E5%A4%9A%E7%AD%BE%E7%A4%BA%E4%BE%8B)

<!-- /TOC -->

## 使用体验

### 界面

个人认为Parity的界面并不美观。

![Alt text](img/Parity_UI/parity_ui.png)

![Alt text](img/Parity_UI/parity_ui_accounts.png)

### 助记词

Parity的助记词只能逐一输入，体验不佳。对比来看，ONTO的助记词是在所给助记词中选择顺序，用户体验比较好。

![Alt text](/img/Parity_UI/parity_owner_recovery_phrase.png)

## 多重签名

Parity的多重签名基于智能合约`Wallet.sol`实现。

### Wallet.sol文件

#### 文件结构

> https://github.com/ethereum/dapp-bin/blob/master/wallet/wallet.sol

`Wallet.sol`中包含了4个合约（contract）：

- Wallet.sol
  - contract multiowned
  - contract daylimit
  - contract multisig
  - contract Wallet

![Alt text](img/Parity_UI/wallel_sol_uml.png)

#### multiowned合约

`multiowned`合约定义了6种事件（Event）：

```
event Confirmation(address owner, bytes32 operation);
event Revoke(address owner, bytes32 operation);
event OwnerChanged(address oldOwner, address newOwner);
event OwnerAdded(address newOwner);
event OwnerRemoved(address oldOwner);
event RequirementChanged(uint newRequirement);
```

- `OwnerAdded`：用于记录增加钱包所有人操作。
- `OwnerRemoved`：用于记录删除钱包所有人操作。
- `OwnerChanged`：用于记录修改钱包所有人操作。
- `RequirementChanged`：用于记录修改多重签名方案（M-N）操作。

#### multisig合约

`contract multisig`合约定义了4种事件：

```
event Deposit(address _from, uint value);
event SingleTransact(address owner, uint value, address to, bytes data);
event MultiTransact(address owner, bytes32 operation, uint value, address to, bytes data);
event ConfirmationNeeded(bytes32 operation, address initiator, uint value, address to, bytes data);
```    

- `Deposit`：用于记录多签钱包中实际存有的资金数量。
- `SingleTransact`：用于记录从多签钱包中发起的单签交易的相关信息：签名者、资金数量、资金流向、操作的哈希值。
- `MultiTransact`：用于记录从多签钱包中发起的多签交易的相关信息：最终签名者、资金数量、资金流向、操作的哈希值。
- `ConfirmationNeeded`：用于记录多签钱包中发起一笔交易还需要的签名数量。

#### daylimit合约

`daylimit`合约未定义事件，提供了5个方法：

```
function daylimit(uint _limit)
function setDailyLimit(uint _newLimit)
function resetSpentToday()
function underLimit(uint _value)
function today()
```

- `function daylimit(uint _limit)`：检查今天是否还有可用花费。
- `function setDailyLimit(uint _newLimit)`：设置每日花费限额（需要多重签名使其生效）。
- `function resetSpentToday()`：重置今天已经产生的花费（需要多重签名使其生效）。
- `function underLimit(uint _value)`：
- `function today()`：确定今天的索引。

### 多签钱包的部署

![Alt text](img/Parity_UI/parity_multisig_wallet.png)

在实际部署时，`Parity UI`中提供的智能合约编译器在`Kovan`测试网中一直无法加载出来，故最终使用了[Remix](https://remix.ethereum.org/)进行智能合约的编译。

![Alt text](img/Parity_UI/multisig_deploy_1.png)

![Alt text](img/Parity_UI/multisig_deploy_2.png)

![Alt text](img/Parity_UI/multisig_deploy_3.png)

![Alt text](img/Parity_UI/multisig_deploy_4.png)

![Alt text](img/Parity_UI/multisig_deploy_5.png)

![Alt text](img/Parity_UI/multisig_deploy_6.png)

![Alt text](img/Parity_UI/multisig_deploy_7.png)

![Alt text](img/Parity_UI/multisig_deploy_8.png)

### 多签钱包的使用

#### getOwner与isOwner的使用

![Alt text](img/Parity_UI/get_owner_and_is_owner.png)

#### setDailyLimit

![Alt text](img/Parity_UI/set_daily_limit_1.png)

![Alt text](img/Parity_UI/set_daily_limit_2.png)

![Alt text](img/Parity_UI/set_daily_limit_3.png)

![Alt text](img/Parity_UI/set_daily_limit_4.png)

![Alt text](img/Parity_UI/set_daily_limit_5.png)


#### 向多签钱包转账

![Alt text](img/Parity_UI/transfer_1.png)

![Alt text](img/Parity_UI/transfer_2.png)

![Alt text](img/Parity_UI/transfer_3.png)

![Alt text](img/Parity_UI/transfer_4.png)

![Alt text](img/Parity_UI/transfer_5.png)

![Alt text](img/Parity_UI/transfer_6.png)

![Alt text](img/Parity_UI/transfer_7.png)

![Alt text](img/Parity_UI/transfer_8.png)

![Alt text](img/Parity_UI/transfer_9.png)

#### 多签示例

将多签钱包更改为3-2多签钱包（`m_numOwners`：3，`m_required`：2）：

![Alt text](img/Parity_UI/multisig_example_1.png)

将多签钱包的每日限额从`100`降低到`50`：

![Alt text](img/Parity_UI/multisig_example_2.png)

填入参数，执行`setDailyLimit`方法：

![Alt text](img/Parity_UI/multisig_example_3.png)

确认交易：

![Alt text](img/Parity_UI/multisig_example_4.png)

将交易发送到网络：

![Alt text](img/Parity_UI/multisig_example_5.png)

等待交易被写入区块：

![Alt text](img/Parity_UI/multisig_example_6.png)

在交易发起者的账户下查询交易`0x365511f1f417c39e5ede320281f8fbb64f42bc7aeb4e9322033564d17bb9d46e`：

![Alt text](img/Parity_UI/multisig_example_7.png)

在区块链浏览器中查询交易`0x365511f1f417c39e5ede320281f8fbb64f42bc7aeb4e9322033564d17bb9d46e`：

![Alt text](img/Parity_UI/multisig_example_8.png)

交易`0x365511f1f417c39e5ede320281f8fbb64f42bc7aeb4e9322033564d17bb9d46e`还未被`ACCT`确认：

![Alt text](img/Parity_UI/multisig_example_9.png)

账户`ACCT`通过执行`confirm`方法确认交易`0x365511f1f417c39e5ede320281f8fbb64f42bc7aeb4e9322033564d17bb9d46e`：

![Alt text](img/Parity_UI/multisig_example_10.png)

![Alt text](img/Parity_UI/multisig_example_11.png)

![Alt text](img/Parity_UI/multisig_example_12.png)

`confirm`方法发起的交易被写入到区块中，调用`hasConfirmed`方法查询`ACCT`的确认状态，显示为`true`:

![Alt text](img/Parity_UI/multisig_example_13.png)

`m_dailyLimit`仍然为`100`，还需要第二位所有者确认：

![Alt text](img/Parity_UI/multisig_example_14.png)

![Alt text](img/Parity_UI/multisig_example_15.png)

![Alt text](img/Parity_UI/multisig_example_16.png)

![Alt text](img/Parity_UI/multisig_example_17.png)