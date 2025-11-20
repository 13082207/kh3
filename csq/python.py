# 银行账户基类
class BankAccount:
    def __init__(self, name, money=0):
        self.name = name        # 账户名
        self.money = money      # 余额
    
    def save(self, amount):     # 存款方法
        self.money += amount
        print(f"{self.name} 存了 {amount} 元")
    
    def take(self, amount):     # 取款方法 - 子类会重写
        pass
    
    def show(self):             # 显示余额
        print(f"{self.name} 有 {self.money} 元")

# 普通账户 - 不能透支
class NormalAccount(BankAccount):
    def take(self, amount):     # 重写取款方法
        if amount <= self.money:
            self.money -= amount
            print(f"{self.name} 取了 {amount} 元")
        else:
            print(f"{self.name} 余额不足")

# 信用卡账户 - 可以透支
class CreditAccount(BankAccount):
    def take(self, amount):     # 重写取款方法
        self.money -= amount
        print(f"{self.name} 取了 {amount} 元")
        if self.money < 0:
            print(f"{self.name} 已透支 {-self.money} 元")

# 使用示例
print("=== 银行账户演示 ===")

# 创建两个账户
account1 = NormalAccount("小明", 1000)
account2 = CreditAccount("小红", 1000)

# 显示初始状态
account1.show()
account2.show()

print("\n=== 存款操作 ===")
account1.save(500)
account2.save(500)

print("\n=== 取款操作 - 体现多态 ===")
# 相同的取款方法，不同结果
account1.take(2000)  # 普通账户：余额不足
account2.take(2000)  # 信用卡账户：可以透支

print("\n=== 最终状态 ===")
account1.show()
account2.show()
