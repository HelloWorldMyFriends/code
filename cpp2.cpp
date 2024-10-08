#include"iostream"
#include<vector>
#include<algorithm>
using namespace std;


void printIntVector(const vector<int> & mybox)
{
	for (auto x : mybox) {
	
		cout << x << " ";
	
	}
	cout << endl;

}

int main() {
	vector<int> mybox = {12,2,3,3,3,3,4,45,3,34,2,5,6,7,8};
	vector<int> mybox1 = {1,2,3,4,56};
	mybox1.resize(mybox.size());

	//1.翻转元素
	//reverse(mybox.begin(), mybox.end());
	
	//2.旋转 将左边的一半移动到右边
	rotate(mybox.begin(), mybox.begin() + mybox.size() / 2, mybox.end());
    for(auto &i:mybox){
        cout << i << " ";
    }

	//3.删除某个指定的元素
	//remove(mybox.begin(), mybox.end(), 45);
	
	//4.删除某一类元素,注意remove 并不是真的删除元素  而是从头部开始覆盖 然后返回一个迭代器首位置
	/*auto it = std::remove_if(mybox.begin(), mybox.end(), [](const int& a) {return a % 2 == 0; });
	mybox.erase(it, mybox.end());*/

	//5.unique 移除重复的元素
	/*auto it = unique(mybox.begin(), mybox.end());
	mybox.erase(it, mybox.end());*/

	//6.unique_copy 将序列中的元素复制到另一个序列，并移除连续重复的元素。
	/*printIntVector(mybox1);
	auto it=unique_copy(mybox.begin(), mybox.end(),mybox1.begin());
	mybox1.erase(it, mybox1.end());
	printIntVector(mybox1);*/


	cout << endl;
	return 0;
}