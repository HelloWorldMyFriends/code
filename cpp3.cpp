// #include <fstream>

// int main() {
//     // 打开文件（默认为输出模式）
//     std::fstream file("laojia.txt", std::ios::out);

//     // 进行文件操作...
//     file << "Hello, World!" << std::endl;

//     // 关闭文件
//     file.close();

//     return 0;
// }
// #include <iostream>
// #include <fstream>
// #include <string>
// using namespace std;

// int main() {
//     ifstream inputFile("laojia.txt");
//     string line;

//     while (getline(inputFile, line)) {
//         cout << line << endl;
//     }

//     inputFile.close();
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // 打开文件
    fstream inputFile("laojia.txt", ios::in | ios::binary);

    // 检查文件是否成功打开
    if (!inputFile.is_open()) {
        cerr << "无法打开文件。" << endl;
        return 1;
    }

    // 获取文件大小
    inputFile.seekg(0, ios::end);
    streampos fileSize = inputFile.tellg();

    // 检查文件大小是否有效
    if (fileSize < 0) {
        cerr << "获取文件大小时发生错误。" << endl;
        inputFile.close();
        return 1;
    }

    // 将文件指针重置到文件开头
    inputFile.seekg(0, ios::beg);

    // 输出文件大小
    cout << "文件大小: " << fileSize << " 字节" << endl;

    // 定义缓冲区大小
    const int bufferSize = 100;
    char buffer[bufferSize];

    // 逐块读取文件
    while (!inputFile.eof()) {
        // 读取缓冲区大小的数据块
        inputFile.read(buffer, sizeof(buffer));

        // 处理二进制数据，以十六进制格式输出每个字节
        for (int i = 0; i < inputFile.gcount(); ++i) {
            cout << hex << static_cast<int>(buffer[i]) << " ";
        }
    }

    // 关闭文件
    inputFile.close();
    return 0;
}
