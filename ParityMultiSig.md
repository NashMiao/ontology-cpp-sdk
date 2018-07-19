# 以太坊Parity多重签名设计

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

- `function daylimit(uint _limit)`：
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

### 多签钱包的使用

