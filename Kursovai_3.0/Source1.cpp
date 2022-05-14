#include"Header.h"
#include<iostream>
#include<list> 
#include <Windows.h>

using namespace std;

void Cash::pay(int& sum_items)
{
	cout << "   Paid - " << sum_items << " Thank you for purchase." << endl;
}

const char* Cash::get_text_payment() { return "cash"; }

void Credit_card::discount(int& sum_items)
{
	cout << "   Paid by credit card with discount 5% - " << sum_items << endl;
	sum_items *= 0.95;
}

void Credit_card::pay(int& sum_items)
{
	this->discount(sum_items);
	cash->pay(sum_items);
}

const char* Credit_card::get_text_payment() { return "card"; }

Publisher::Publisher()
{
	for (int i = 0; i < 50; i++)
	{
		subscribers[i] = nullptr;
	}
	action_state = "non active";
}

void Publisher::add_subscribers(Subscriber* sub)
{
	for (int i = 0; i < 50; i++)
	{
		if (subscribers[i] == nullptr)
		{
			subscribers[i] = sub;
			break;
		}
	}
}

void Publisher::delete_subscriber(Subscriber* sub)
{
	for (int i = 0; subscribers[i]; i++)
	{
		if (subscribers[i] == sub)
		{
			subscribers[i]->unsubscribtion();
			subscribers[i] = subscribers[i + 1];
			if (subscribers[i + 1] != nullptr)
			{
				while (subscribers[i + 1] != nullptr)
				{
					subscribers[i + 1] = subscribers[i + 2];
					i++;
				}
			}
		}
	}
}

void Publisher::notify_all()
{
	for (int i = 0; subscribers[i]; i++)
	{
		subscribers[i]->notify();
	}
}

void Publisher::set_state(string s)
{
	action_state = s;
	this->notify_all();
}

void Publisher::get_status()
{
	int counting = 0;
	for (int i = 0; subscribers[i]; i++)
	{
		counting = i;
	}
	cout << "Kolicestvo podpischikov " << counting + 1 << endl;
}

Client::Client(int sum_items, Payment* payment_method) : bonus_card(0)
{
	this->sum_items = sum_items;
	this->payment_method = payment_method;
}

void Client::add(Client** array)
{
	int n = 10;
	for (int i = 0; i < n; i++)
	{
		if (array[i] == nullptr)
		{
			array[i] = this;
			break;
		}
	}
}

int Client::get_sum_items() { return this->sum_items; }

void Client::set_sum_items(int sum_items) { this->sum_items = sum_items; }

int Client::get_bonus_card() { return this->bonus_card; }

void Client::pay_client() { payment_method->pay(sum_items); };

void Client::notify() { bonus_card = 1; }

void Client::unsubscribtion() { bonus_card = 0; }

const char* Client::get_payment_method() { return payment_method->get_text_payment(); };

—ash_register::—ash_register(ObjectPool* pool) :pool(pool)
{
	state = new Handle_clients(this);
}
void —ash_register::change_state(State* state)
{
	if (this->state)
		delete this->state;
	this->state = state;
}

void —ash_register::Do_handle(Client** mas, int length, int flagg[], float rate)
{
	state->do_Business(mas, length, flagg, rate);
}

—ash_register_Simple::—ash_register_Simple(ObjectPool* pool) : —ash_register(pool), name("name"), max_people(1), available(1), served(0), card(0), cash(0), profit(0) {}

—ash_register_Simple::—ash_register_Simple(string name, int max_people, ObjectPool* pool) : —ash_register(pool), available(1), served(0), card(0), cash(0), profit(0) { this->name = name; this->max_people = max_people; }

void —ash_register_Simple::reset() { available = 1; }

int —ash_register_Simple::getflag() { return available; }

void —ash_register_Simple::setflag(int available) { this->available = available; }

int —ash_register_Simple::getmax_people() { return max_people; }

void —ash_register_Simple::setmax_people(int max_people) { this->max_people = max_people; }

string —ash_register_Simple::getname() { return name; }

void —ash_register_Simple::setname(string name) { this->name = name; }

void —ash_register_Simple::Get_stats()
{
	cout << "Stasts of cash register - " << this->getname() << "\nServed: " << this->served;
	cout << " number of people\nWith card served: " << this->card << " people\n";
	cout << "With cash served: " << this->cash << " people\n";
	cout << "Profit - " << this->profit << " lei" << endl;
}

int —ash_register_Simple::get_served() { return this->served; }

void —ash_register_Simple::set_served(int served) { this->served = served; }

int —ash_register_Simple::get_card() { return this->card; }

void —ash_register_Simple::set_card(int card) { this->card = card; }

int —ash_register_Simple::get_cash() { return this->cash; }

void —ash_register_Simple::set_cash(int cash) { this->cash = cash; }

int —ash_register_Simple::get_profit() { return this->profit; }

void —ash_register_Simple::set_profit(int profit, Client* mas, int money, float rate) { this->profit = profit; }

//////////////////////////////////////////////////////////////////////////////////////////////////

—ash_register_Decorator::—ash_register_Decorator(—ash_register* decorated_cash_register, ObjectPool* pool) :—ash_register(pool)
{
	this->decorated_cash_register = decorated_cash_register;
}

void —ash_register_Bonus_card::reset() { decorated_cash_register->reset(); }

int —ash_register_Bonus_card::getflag() { return decorated_cash_register->getflag(); }

void —ash_register_Bonus_card::setflag(int available) { decorated_cash_register->setflag(available); }

int —ash_register_Bonus_card::getmax_people() { return decorated_cash_register->getmax_people(); }

void —ash_register_Bonus_card::setmax_people(int max_people) { decorated_cash_register->setmax_people(max_people); }

string —ash_register_Bonus_card::getname() { return decorated_cash_register->getname(); }

void —ash_register_Bonus_card::setname(string name) { decorated_cash_register->setname(name); }

void —ash_register_Bonus_card::Get_stats()
{
	cout << "DECORATOR" << endl;
	cout << "Stasts of cash register - " << this->getname() << "\nServed: " << decorated_cash_register->get_served();
	cout << " number of people\nWith card served: " << decorated_cash_register->get_card() << " people\n";
	cout << "With cash served: " << decorated_cash_register->get_cash() << " people\n";
	cout << "Profit - " << decorated_cash_register->get_profit() << " lei" << endl;
}

int —ash_register_Bonus_card::get_served() { return decorated_cash_register->get_served(); }

void —ash_register_Bonus_card::set_served(int served) { decorated_cash_register->set_served(served); }

int —ash_register_Bonus_card::get_card() { return decorated_cash_register->get_card(); }

void —ash_register_Bonus_card::set_card(int card) { decorated_cash_register->set_card(card); }

int —ash_register_Bonus_card::get_cash() { return  decorated_cash_register->get_cash(); }

void —ash_register_Bonus_card::set_cash(int cash) { decorated_cash_register->set_cash(cash); }

int —ash_register_Bonus_card::get_profit() { return decorated_cash_register->get_profit(); }

void —ash_register_Bonus_card::set_profit(int profit, Client* mas, int money, float rate)
{
	int p = mas->get_bonus_card();
	if (p == 1)
	{
		int lol = rand() % 2;
		if (lol == 1)
		{
			cout << "   Bonus card! Discount Bonus + 10%." << endl;
			money *= 0.9;

		}
	}
	if (rate != 0)
	{
		int static counter = 0;
		int static counter1 = 0;
		int static counter2 = 0;
		float static rate_tmp = 0.f;
		float static rate_older = 0.f;


		if (rate_older != rate)
			counter = 0;

		if (rate_older != rate && counter == 0 && rate > 0)
		{
			if (counter1 == 0)
			{
				cout << "PRICE UP! coefficient is " << rate * 100 << "%" << endl;
				counter1++;
			}
			else
				cout << "PRICE UP! coefficient is " << rate * 100 - rate_older * 100 << "%" << ", the current coefficient " << rate * 100 << endl;
		}
		else if (rate_older != rate && counter == 0)
		{
			if (counter1 == 0)
			{
				cout << "PRICE DOWN! coefficient is " << rate * 100 << "%" << endl;
				counter1++;
			}
			else
				cout << "PRICE DOWN! coefficient is " << rate * 100 - rate_older * 100 << "%" << ", the current coefficient " << rate * 100 << endl;
		}

		rate_older = rate;

		int money2 = money;
		money = money + (money * rate_older);
		cout << "   Price before downed - " << money2 << endl;
		counter++;
	}
	profit += money;
	cout << "Last Price - " << money << endl;
	decorated_cash_register->set_profit(profit, mas, money, rate);
}

//////////////////////////////////////////////////////////////////////////////////////////////////


void ObjectPool::handler(—ash_register* other, Client** mas, int length, int flagg[], float rate)
{
	const char* tmp;
	int k = 0, l = 0;
	int a = other->getmax_people();
	int count = 0;
	int count_client = 0;
	for (int i = 0; i < length; i++)
	{
		if (mas[i] != nullptr)
		{
			count_client++;
		}
		else break;
	}
	while (count < a)
	{
		cout << flagg[2] << endl;
		for (flagg[2]; flagg[2] < count_client; flagg[2]++)
		{
			int served = other->get_served();
			int cash = other->get_cash();
			int card = other->get_card();
			int profit = other->get_profit();
			served += 1;
			mas[flagg[2]]->pay_client();
			tmp = mas[flagg[2]]->get_payment_method();
			if (strcmp("cash", tmp) == 0)
			{
				cash += 1;
			}
			else
				card += 1;
			//profit += mas[flagg[2]]->get_sum_items();
			int money = mas[flagg[2]]->get_sum_items();
			other->set_served(served);
			other->set_cash(cash);
			other->set_card(card);
			other->set_profit(profit, mas[flagg[2]], money, rate);
			//    »—œ–¿¬»“‹, profit = ‚ÒÂ ‰ÂÌ¸„Ë, ‡ Ì‡‰Ó ‰ÂÌ¸„Ë Ò ˜ÂÎÓ‚ÂÍ‡
			count++;
			if (count >= a)
			{
				k = 1;
				l = flagg[2] + 1;
				break;
			}

		}
		if (k == 1)
			break;
		else if (flagg[2] == count_client)
		{
			k = 1;
		}
	}
	if (a > count)
	{
		flagg[0] = 0;
		//Sleep(number * 1000);
		this->return—ash_register(other);
	}
	else if (k == 1 || a >= count)
	{
		if (l == count_client)
		{
			flagg[0] = 0;
			this->return—ash_register(other);
		}
		else
		{
			cout << "The queue of " << count << " people is processed by " << other->getname() << " cash register." << endl;
			flagg[0] = 1;
			if (flagg[1] == 0)
			{
				flagg[1] = abs(a - count_client);
			}
			else
			{
				flagg[1] = abs(a - flagg[1]);
			}
			flagg[2] = l;
			cout << "Attention!!!!!!\nThe queue is full, need to open another cash register to serve the remaining " << flagg[1] << " people" << endl;
		}
	}
}

void ObjectPool::handle(—ash_register* other, Client** mas, int length, int flagg[], float rate)
{
	other->Do_handle(mas, length, flagg, rate);
}

ObjectPool* ObjectPool::instance = 0;

ObjectPool* ObjectPool::getInstance()
{
	if (instance == 0)
	{
		instance = new ObjectPool;
	}
	return instance;
}

—ash_register* ObjectPool::get—ash_register(—ash_register* other)
{
	if (created_cash_registers.empty())
	{
		std::cout << "\n........................Creating new........................" << std::endl;
		other->setflag(0);
		// return new —ash_register;
		return other;
	}
	else
	{
		std::cout << "\n........................Reusing existing........................" << std::endl;
		—ash_register* created_cash_register = created_cash_registers.front();
		created_cash_registers.pop_front();
		other->setflag(0);
		return created_cash_register;
	}
}

void ObjectPool::return—ash_register(—ash_register* object)
{
	object->reset();
	created_cash_registers.push_back(object);
}


void EventGenerator::addEvent(EventHandler* other)
{
	Event = other;
}

float EventGenerator::generate(int rate)
{
	return Event->update(rate);
}

float  UP_DOWN_price::update(int rate)
{
	int t, t1;
	switch (rate)
	{
	case 0: t = rand() % 3;
		if (t == 0)
			return 0.075f;
		else if (t == 1)
			return 0.05f;
		else
			return 0.1f;

	case 1: t1 = rand() % 3;
		if (t1 == 0)
			return -0.05f;
		else if (t1 == 1)
			return -0.025f;
		else
			return -0.075f;
	}
}


void Handle_clients::do_Business(Client** mas, int length, int flagg[], float rate)
{
	this->cash->get_pool()->handler(cash, mas, length, flagg, rate);
	chance++;
	if (this->chance == 2)
	{
		cash->change_state(new Recalculation(cash));
	}
}


void Recalculation::do_Business(Client** mas, int length, int flagg[], float rate)
{
	
		cout << "   Preliminary results of cash register - " << cash->getname() << " requested by the server...." << endl;
		cout << "   All actions with cash register - " << cash->getname() << " are stopped!" << endl;
		cash->Get_stats();
		chance++;
	if (this->chance == 1)
	{
		cash->change_state(new Handle_clients(cash));
	}
}