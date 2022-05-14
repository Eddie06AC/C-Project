#include"Header.h"
#include<iostream>


using namespace std;

int main()
{
    EventGenerator* gen = new EventGenerator();
    UP_DOWN_price* event_price = new UP_DOWN_price();
    gen->addEvent(event_price);
    float rate = 0.f;
    srand(time(NULL));

    Cash* cash = new Cash();
    Credit_card* card = new Credit_card(cash);

    Client* client1 = new Client(1500, cash);  //
    Client* client2 = new Client(200, card);
    Client* client3 = new Client(500, card);  //
    Client* client4 = new Client(1500, card);  //
    Client* client5 = new Client(50, cash);
    Client* client6 = new Client(200, card);  //
    Client* client7 = new Client(100, cash);
    Client* client8 = new Client(1800, cash);
    Client* client9 = new Client(300, cash);  //

    int const length = 10;
    Client* mas[length];

    for (int i = 0; i < length; i++)
    {
        mas[i] = 0;

    }
    client1->add(mas);
    client2->add(mas);
    client3->add(mas);
    client4->add(mas);
    client5->add(mas);
    client6->add(mas);
    client7->add(mas);
    client8->add(mas);
    client9->add(mas);


    Publisher* actions_store = new Publisher();

    actions_store->add_subscribers(client1);
    actions_store->add_subscribers(client3);
    actions_store->add_subscribers(client4);
    actions_store->add_subscribers(client6);
    actions_store->add_subscribers(client9);

    actions_store->set_state("Action");

    actions_store->delete_subscriber(client1);


    int flagg[3] = { 1,0,0 };
    // first: 1 - if exists queue 
    // second: number of remaining people
    // third: number of person who need to be handled
    ObjectPool* admin = ObjectPool::getInstance();

    Ñash_register* a = new Ñash_register_Simple("first", 1, admin);
    Ñash_register* b = new Ñash_register_Simple("second", 1, admin);
    Ñash_register* c = new Ñash_register_Simple("third",1, admin);

    Ñash_register* apas = (Ñash_register*) new Ñash_register_Bonus_card(a, admin);
    Ñash_register* bpas = (Ñash_register*) new Ñash_register_Bonus_card(b, admin);
    Ñash_register* cpas = (Ñash_register*) new Ñash_register_Bonus_card(c, admin);

    int event_count = 0;

    while (flagg[0] == 1)
    {
        /*if (event_count == 0)
        {
            rate += gen->generate(1);
            event_count++;
        }*/
        apas = admin->getÑash_register(apas);
        cout << apas << " - " << apas->getname() << endl;
        admin->handle(apas, mas, length, flagg, rate);
        if (flagg[0] == 1)
        {
            bpas = admin->getÑash_register(bpas);
            cout << bpas << " - " << bpas->getname() << endl;
            admin->handle(bpas, mas, length, flagg, rate);
            if (flagg[0] == 1)
            {
               /* if (event_count == 1)
                {
                    rate += gen->generate(0);
                    event_count++;
                }*/
                cpas = admin->getÑash_register(cpas);
                cout << cpas << " - " << cpas->getname() <<endl;
                admin->handle(cpas, mas, length, flagg, rate);
            }
        }
        admin->returnÑash_register(apas);
        admin->returnÑash_register(bpas);
        admin->returnÑash_register(cpas);
    }

    cout << "Queue is finished;\n" << endl;

    apas->Get_stats();
    cout << endl;
    bpas->Get_stats();
    cout << endl;
    cpas->Get_stats();
    cout << endl;

    actions_store->get_status();
    actions_store->delete_subscriber(client9);
    actions_store->get_status();

    return 0;
}