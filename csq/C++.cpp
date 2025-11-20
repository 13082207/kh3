#include <iostream>
#include <string>
using namespace std;

// 动物基类 - 体现：类的继承
class Animal {
protected:
    string name;
    int age;
    
public:
    // 构造函数 - 体现：对象初始化
    Animal(string n, int a) : name(n), age(a) {}
    
    // 虚函数 - 体现：多态，子类可以重写
    virtual void makeSound() {
        cout << name << " 发出声音" << endl;
    }
    
    // 普通方法
    void eat() {
        cout << name << " 在吃东西" << endl;
    }
    
    void display() {
        cout << "名字: " << name << ", 年龄: " << age << "岁" << endl;
    }
};

// 狗类 - 继承自动物
class Dog : public Animal {
public:
    Dog(string n, int a) : Animal(n, a) {}
    
    // 重写方法 - 体现：多态
    void makeSound() override {
        cout << name << " 汪汪叫!" << endl;
    }
    
    // 特有方法
    void fetch() {
        cout << name << " 在接飞盘" << endl;
    }
};

// 猫类 - 继承自动物
class Cat : public Animal {
public:
    Cat(string n, int a) : Animal(n, a) {}
    
    // 重写方法 - 体现：多态
    void makeSound() override {
        cout << name << " 喵喵叫!" << endl;
    }
    
    // 特有方法
    void climb() {
        cout << name << " 在爬树" << endl;
    }
};

int main() {
    cout << "=== 简单动物类演示 ===" << endl;
    
    // 创建对象 - 体现：实例化
    Dog dog("小白", 2);
    Cat cat("小花", 1);
    
    // 使用对象方法
    dog.display();
    dog.makeSound();
    dog.eat();
    dog.fetch();
    
    cout << endl;
    
    cat.display();
    cat.makeSound();
    cat.eat();
    cat.climb();
    
    cout << "\n=== 多态演示 ===" << endl;
    
    // 多态演示 - 体现：父类指针指向子类对象
    Animal* animal1 = &dog;
    Animal* animal2 = &cat;
    
    animal1->makeSound();  // 调用狗的makeSound
    animal2->makeSound();  // 调用猫的makeSound
    
    return 0;
}
