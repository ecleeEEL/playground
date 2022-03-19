
#include <list>
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> stop_thread = {false};

struct ProdCons {
    std::list<int> q;
    std::list<int>::iterator qRead;
    std::list<int>::iterator qWrite;
    bool consume(int* element) {
        auto currRead {qRead};
        currRead++;
        if (currRead != qWrite) {
            *element = *currRead;
            qRead = currRead;
            return true;
        } else {
            return false;
        }

    }

    void produce(int element) {
        q.push_back(element);
        qWrite = q.end();

        auto walk = q.begin();
        while (walk != qRead) {
            q.erase(walk);
            walk = q.begin();
        }

    }

    ProdCons(): q{} {
        q.push_back(-1);
        qWrite = q.end();
        qRead = q.begin();
    }
};


void runthread(ProdCons * pc) {
    struct timespec tim;
    tim.tv_sec = 1;
    while (true) {
        int val {-1};
        if (pc->consume(&val)) {
            std::cout << "*** Consumed " << val << std::endl;
        } else if (stop_thread) {
            return;
        } else {
            nanosleep(&tim, NULL);
        }

    }
}

int main() {
    ProdCons *pc = new ProdCons();
    struct timespec tim;
    tim.tv_sec = 10;
    std::thread t(runthread, pc);
    

    for (int i = 0; i < 500; i++ ) {
        pc->produce(i);
    }

    nanosleep(&tim, NULL);
    stop_thread = true;
    t.join();
    return 0;

}