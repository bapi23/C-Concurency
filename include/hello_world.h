#pragma once

class Callable
{
  public:
    void operator()()
    {
        std::cout << "Hello World! from callable object" << std::endl;
    }

};

void hello()
{
    std::cout << "Hello World!" << std::endl;
}

void hello_world()
{
    std::thread t(hello);

    t.join();

    std::thread t2([](){ std::cout << "Hello World! from labdaexpr" << std::endl; });
    t2.join();

    std::thread t3((Callable())); //most vexing parse;
    t3.join();

    {
        int a = 4;
        std::thread bad([&a](){
            std::cout << "garbage: " << a << std::endl;}
        );
        bad.detach();
    }
}
