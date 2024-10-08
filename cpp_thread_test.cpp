// #include <iostream>  
// #include <thread>  
 
// void thread1_function() {  
//     while(1){
//         std::cout << "Hello from thread1!\n";   
//     }
// }  

// void thread2_function() {  
//     while(1){
//         std::cout << "Hello from thread2!\n";  

//     }
// } 
// int main() {  
//     std::thread my_thread1(thread1_function);  
//     std::thread my_thread2(thread2_function);
//     my_thread1.join(); // 等待线程结束  
//     my_thread2.join(); // 等待线程结束
//     return 0;  
// }


// #include <iostream>  
// #include <thread>  
  
// void thread_function() {  
//     std::thread::id id = std::this_thread::get_id();  
//     std::cout << "Thread ID: " << id << std::endl;  
// }  
  
// int main() {  
//     std::thread t(thread_function);  
//     t.join();  
//     return 0;  
// }

#include <iostream>  
#include <thread>  
#include <chrono>  
  
int main() {  
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 休眠1秒  
    std::cout << "Woke up after 1 second!" << std::endl;  
  
    // 休眠到某个时间点  
    auto wakeup_time = std::chrono::system_clock::now() + std::chrono::seconds(2);  
    std::this_thread::sleep_until(wakeup_time);  
    std::cout << "Woke up at the specified time!" << std::endl;  
  
    return 0;  
}