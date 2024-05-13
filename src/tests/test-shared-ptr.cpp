#include <iostream>
#include <memory>
#include <vector>

using namespace std;
int main()
{
    
    vector<shared_ptr<int>> T;
    
    cout <<"Allo ! "<<endl;
    for(int i=0;i<10;i++){
        T.emplace_back(new int(i));
    }
    cout <<"Allo ! "<<endl;
    
    cout<<"T : ";
    for(int i=0;i<10;i++){
        cout << *T[i] << " ";
    }
    cout<<endl;
    cout <<"Allo ! "<<endl;
    
	cout<<"T.size() : "<<T.size()<<endl;
    T.erase(T.begin()+2);
	cout<<"T.size() : "<<T.size()<<endl;
    
    cout<<"T : ";
    for(int i=0;i<9;i++){
        cout << *T[i]<< " ";
    }
    cout<<endl;


    return 0;
}