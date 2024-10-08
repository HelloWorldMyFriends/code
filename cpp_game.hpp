#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

class Game{
private:
    int number;
    int random_number;
    int pid;
public:
    Game() : number(0), random_number(0){
        cout << "Game created!" << endl;
    }

    void init(){
        srand(time(0));
        random_number = rand() % 10 + 1;
        cout << "Game initialized!" << endl;
    }

    void run(){
        while(true){
            cout << "Game running!" << endl;
            while(guess() == false){
                cout << "its wrong, try again!" << endl;
            }
        }
        
    }

    bool guess(){
        cout << "Please guess a number between 1 and 10: (-1 is quit)" << endl;
        cin >> number;
        if(number == -1){
            cout << "You quit the game!" << endl;
            pthread_exit(0);
        }
        if(number < 1 || number > 10){
            cout << "The number must be between 1 and 10!" << endl;
            return false;

        }
        cout << "You guessed " << number << endl;
        if(number == random_number){
            cout << "That's right, you win!" << endl;
            sleep(1);
            cout << "There is a train coming to celebrate you!" << endl;
            sleep(1);
            ending_theme();
            return true;
        } else {
            return false;
        }   
    }
    void ending_theme() {
    pid_t pid = fork(); // 创建子进程

    if (pid < 0) {
        // 处理 fork 失败的情况
        std::cerr << "Fork failed" << std::endl;
        exit(1);
    } else if (pid == 0) {
        // 子进程
        // 注意：system 函数的路径应以 / 开头
        system("/usr/bin/sl"); // 执行 sl 命令
        exit(0); // 子进程结束
    } else {
        // 父进程
        wait(NULL); // 等待子进程结束
    }
}

    ~Game(){
        cout << "Game destroyed!" << endl;
        pthread_exit(0);
    }
};