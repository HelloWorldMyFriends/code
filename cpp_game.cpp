#include "cpp_game.hpp"
using namespace std;

int main(){
    Game game;
    pthread_t thread;
    try{
        game.init();

        if(pthread_create(&thread, NULL, (void*(*)(void*))&Game::run, &game)){
            throw runtime_error("pthread_create failed!");
        }

        if(pthread_join(thread, NULL) != 0){
            throw runtime_error("pthread_join failed!");
        }
        
    } catch(exception &e){
        cout << "Exception: " << e.what() << endl;
        if(pthread_cancel(thread) != 0){
            cout << "pthread_cancel failed!" << endl;
        }
    }
    return 0; 
}