#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex{
private:
	double r,i;
public:
	void Print(){
		cout<< r << "+" << i << "i" <<endl;
	}
	void operator = (const char*s){
		int n,mark;
		r = 0;
		i = 0;
		n = 0;
		while(s[n]!='i'){
			if(s[n]=='+' || s[n]=='-'){
				int k = n-1;
				mark = n;
				while(k > 0){
					r += (n-k)*(s[k]-'0');
					--k;
				}
				if(s[k] == '-'){r = -r;}
				else {r += (n-k)*(s[k]-'0');}
			}
			if(s[n+1]=='i'){
					int k = n;
					while(k > mark){
					i += (n+1-k)*(s[k]-'0');
					--k;
				}
			}
			++n;
		}
	}
};

int main(){
	Complex a;
	a = "3+4i"; a.Print();
	a = "5+6i"; a.Print();
	return 0;
}
