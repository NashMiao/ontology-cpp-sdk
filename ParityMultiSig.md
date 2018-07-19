# 以太坊Parity多重签名设计

## 使用体验

### 界面

个人认为Parity的界面并不美观。

![Alt text](img/Parity_UI/parity_ui.png)

![Alt text](img/Parity_UI/parity_ui_accounts.png)

### 使用

Parity的助记词只能逐一输入，体验不佳。对比来看，ONTO的助记词是在所给助记词中选择顺序，用户体验比较好。

![Alt text](/img/Parity_UI/parity_owner_recovery_phrase.png)

## 多重签名

Parity的多重签名基于智能合约实现。

![Alt text](img/Parity_UI/parity_multisig_wallet.png)

### Wallet.sol文件

