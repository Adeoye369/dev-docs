
# Working with Basic Inheritance

Structure
   ` |_ Account.h , Account.cpp`
   `     |_Savings.h , Savings.cpp`
   `Source.cpp - main()`

```cpp title="Account.h"
#pragma once
#include <iostream>
#include <string>

class Account
{
private:
    std::string m_Name{};
    uint32_t m_AccNo{0};
protected:
    float m_AccBal{};
public:
    static uint32_t s_genAccNum;

    Account(const std::string& name, float balance);

    void Deposit(float amount);
    void Withdrawal(float amount);
    void AccumulateInterest();
    float GetInterestRate();

    const std::string& GetName() const;
    uint32_t GetAccountNo() const;
    float GetAccountBal() const;

    ~Account();
};


```

```cpp title="Account.cpp"
#include "Account.h"

uint32_t Account::s_genAccNum = 1000000;

Account::Account(const std::string& name, float balance): m_Name(name),m_AccBal(balance){
    if (m_AccNo == 0) m_AccNo = ++s_genAccNum;
  
}


void Account::Deposit(float amount){
    if (amount > 0.0) m_AccBal += amount;
    else std::cout << "Invalid Deposit amount\n";
}


void Account::Withdrawal(float amount){
    if (m_AccBal >= amount) m_AccBal -= amount;
    else std::cout << "Withdraw limit Exceeded\n";
}

void Account::AccumulateInterest(){}

float Account::GetInterestRate(){
    return 0.0f;
    }

const std::string& Account::GetName() const{
    return m_Name;
    }

uint32_t Account::GetAccountNo() const{
    return m_AccNo;
    }

float Account::GetAccountBal() const{
    return m_AccBal;
    }

Account::~Account(){}

```

```cpp title="Savings.h"
#pragma once
#include "Account.h"

class Savings : public Account
{
    float m_Rate;
public:
    Savings(const std::string& name, float bal, float rate);

    void AccumulateInterest();
    float GetInterestRate();

    ~Savings();
};


```

```cpp title="Savings.cpp"
#include "Savings.h"


Savings::Savings(const std::string& name, float bal, float rate)
    :Account(name, bal), m_Rate(rate)
{}

void Savings::AccumulateInterest(){
    m_AccBal += (m_AccBal * m_Rate);
}

float Savings::GetInterestRate(){
    return m_Rate;
}

Savings::~Savings(){}

```

```cpp title="Source.cpp"

#include <iostream>
//<ctime> and <cstdio> are already implemented in `iostream`
//#include <ctime> 
//#include <cstdio>
#include "Savings.h"


int main() {
	
    Savings sadeAcc("Sade Adu", 3200, 0.1);

    std::cout << "Account Number is : " << sadeAcc.GetAccountNo() << "\n";
    sadeAcc.Deposit(1200);
    sadeAcc.Withdrawal(3450);
    std::cout << "Sade's Account Balance (Before Interest) is : " << sadeAcc.GetAccountBal() << "\n";
    sadeAcc.AccumulateInterest();
    sadeAcc.AccumulateInterest();
    std::cout << "Sade's Account Balance (After Interest) is : " << sadeAcc.GetAccountBal() << "\n";

return 0;

}
```
<figure markdown='span'>
    ![Output for savings inheritance](img/image-13.png)
</figure>

## Inheritance with Withdrawal

```cpp title="Checkings.h"
#pragma once
#include "Account.h"

class Checkings :public Account
{
public:
    Account::Account;
    //Checkings(const std::string name, float balance);

    void Withdrawal(float amount);

    ~Checkings();
};

```

```cpp title="Checkings.cpp"

#include "Checkings.h"

//Checkings::Checkings(const std::string name, float balance)
//	: Account(name, balance)
//{}

void Checkings::Withdrawal(float amount)
{
    float temp_bal = m_AccBal - amount;
    if (temp_bal > 50)
        Account::Withdrawal(amount);
    else
        std::cout << "The minimum Bal. in Checking should be $50\n";
    }

Checkings::~Checkings(){}

```
