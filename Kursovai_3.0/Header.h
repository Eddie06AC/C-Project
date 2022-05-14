#ifndef HEADER_H_
#define HEADER_H_
#include<iostream>
#include <list>
#include<ctime>

using namespace std;

class Payment
{
public:
    virtual void pay(int& sum_items) = 0;
    virtual const char* get_text_payment() = 0;
};

class Cash : public Payment
{
public:
    void pay(int& sum_items);
    const char* get_text_payment();
};

class Credit_card : public Payment
{
private:
    Cash* cash;
public:
    void discount(int& sum_items);
    void pay(int& sum_items);
    Credit_card(Cash* cash) : cash(new Cash(*cash)) {};
    ~Credit_card() { delete cash; };
    const char* get_text_payment();
};

class Subscriber
{
public:
    virtual void notify() = 0;
    virtual void unsubscribtion() = 0;
};

class Publisher
{
private:
    Subscriber* subscribers[100];
    string action_state;
public:
    Publisher();
    void add_subscribers(Subscriber* sub);
    void delete_subscriber(Subscriber* sub);
    void notify_all();
    void set_state(string s);
    void get_status();
};

class Client : public Subscriber
{
private:
    int sum_items;
    Payment* payment_method;
    int bonus_card;
public:
    Client(int sum_items, Payment* payment_method);
    void add(Client** array);
    int get_sum_items();
    void set_sum_items(int sum_items);
    void pay_client();
    const char* get_payment_method();
    int get_bonus_card();
    void notify();
    void unsubscribtion();
};

class ObjectPool;
class State;

class —ash_register
{
private:
    State* state;
    ObjectPool* pool;
public:
    —ash_register(ObjectPool* pool);
    virtual  void reset() = 0;
    virtual  int getflag() = 0;
    virtual  void setflag(int available) = 0;
    virtual  int getmax_people() = 0;
    virtual   void setmax_people(int max_people) = 0;
    virtual   string getname() = 0;
    virtual   void setname(string name) = 0;
    virtual   void Get_stats() = 0;
    virtual   int get_served() = 0;
    virtual   void set_served(int served) = 0;
    virtual   int get_card() = 0;
    virtual  void set_card(int card) = 0;
    virtual  int get_cash() = 0;
    virtual  void set_cash(int cash) = 0;
    virtual  int get_profit() = 0;
    virtual  void set_profit(int profit, Client* mas, int money, float rate) = 0;
    virtual void change_state(State* state);
    void Do_handle(Client** mas, int length, int flagg[], float rate);
    ObjectPool* get_pool() { return pool; }
};

class State
{
public:
    State(—ash_register* cash) :cash(cash) {}
    virtual void do_Business(Client** mas, int length, int flagg[], float rate) = 0;
    virtual ~State() {};
protected:
    —ash_register* cash;
    int chance = 0;
};

class Handle_clients : public State
{
public:
    Handle_clients(—ash_register* cash) : State(cash) {}
    void do_Business(Client** mas, int length, int flagg[], float rate);
};

class Recalculation : public State
{
public:
    Recalculation(—ash_register* cash) : State(cash) {}
    void do_Business(Client** mas, int length, int flagg[], float rate);
};


class —ash_register_Simple : public —ash_register
{
private:
    string name;
    int max_people;
    int available;
    int served;
    int card;
    int cash;
    int profit;

public:
    —ash_register_Simple(ObjectPool* pool);
    —ash_register_Simple(string name, int max_people, ObjectPool* pool);
    void reset();
    int getflag();
    void setflag(int available);
    int getmax_people();
    void setmax_people(int max_people);
    string getname();
    void setname(string name);
    void Get_stats();
    int get_served();
    void set_served(int served);
    int get_card();
    void set_card(int card);
    int get_cash();
    void set_cash(int cash);
    int get_profit();
    void set_profit(int profit, Client* mas, int money, float rate);
};

class —ash_register_Decorator :public —ash_register
{
public:
    —ash_register_Decorator(—ash_register* decorated_cash_register, ObjectPool* pool);

protected:
    —ash_register* decorated_cash_register;
};

class —ash_register_Bonus_card : —ash_register_Decorator
{
    // ¡ÓÌÛÒÌ‡ˇ Í‡Ú‡- ÂÒÎË ÂÒÚ¸ Û ˜ÂÎÓ‚ÂÍ‡!
    // rand( 1 or 2 ) - ÂÒÎË 1 ÚÓ Û ˜ÂÎÓ‚ÂÍ‡ ÂÒÚ¸ ·ÓÌÛÒÌ˚Â ÔÓ‰ÛÍÚ˚ 
    // ≈ÒÎË ÂÒÚ¸ ·ÓÌÛÒÌ‡ˇ Í‡Ú‡ Ë rand ‚ÂÌÛÎ 1 -> 10% ÒÍË‰Í‡...
public:
    —ash_register_Bonus_card(—ash_register* decorated_cash_register, ObjectPool* pool) : 
           —ash_register_Decorator(decorated_cash_register,pool) {};
    void reset();
    int getflag();
    void setflag(int available);
    int getmax_people();
    void setmax_people(int max_people);
    string getname();
    void setname(string name);
    void Get_stats();
    int get_served();
    void set_served(int served);
    int get_card();
    void set_card(int card);
    int get_cash();
    void set_cash(int cash);
    int get_profit();
    void set_profit(int profit, Client* mas, int money, float rate);
};



class ObjectPool
{
private:
    list<—ash_register*> created_cash_registers;
    static ObjectPool* instance;
    ObjectPool() {}
public:
    static ObjectPool* getInstance();
    —ash_register* get—ash_register(—ash_register* other);
    void return—ash_register(—ash_register* object);
    void handler(—ash_register* other, Client** mas, int length, int flagg[], float rate);
    void handle(—ash_register* other, Client** mas, int length, int flagg[], float rate);
};

class EventHandler
{
public:
    virtual float update(int rate) = 0;
};

class EventGenerator
{
private:
    EventHandler* Event;
public:
    void addEvent(EventHandler* other);
    float generate(int rate);
};

class UP_DOWN_price : public EventHandler
{
public:
    float update(int rate);
};



#endif // !HEADER_H_

