#include <iostream>
#include <cstring>
using namespace std;

class BigNum{
		string a;
		bool operator < (BigNum& c1);
		public:
		BigNum(string i=""):a(i){};
		BigNum operator + (const BigNum & b);
		BigNum operator - (const BigNum & b);
		BigNum operator * (const BigNum & b);
		BigNum operator / (const BigNum & b);
		friend ostream & operator <<(ostream & os, BigNum & a);
};
BigNum BigNum::operator + (const BigNum & b){
		int i(0),sum[200];
		BigNum c;
		int m(0),tmp(0);
		int alen, blen;
		alen = a.length();
		blen = b.a.length();
		while(alen>0 && blen>0){
				tmp = (a[alen-1]-'0')+(b.a[blen-1]-'0')+tmp;
				cout << tmp <<endl;
				sum[i]=tmp%10;
				tmp = tmp/10;
				++i;
				--alen;
				--blen;
		}
		while(alen==0 && blen>0){
				tmp=(b.a[blen-1]-'0')+tmp;
				sum[i] = tmp%10;
				tmp = tmp/10;
				++i;
				--blen;
		}
		while(alen>0 && blen==0){
				tmp=(a[alen-1]-'0')+tmp;
				sum[i]=tmp%10;
				tmp = tmp/10;
				++i;
				--alen;
		}		
		while(tmp!=0){
				sum[i]=tmp%10;
				tmp=tmp/10;
				++i;
		}
		for(m=i-1;m>=0;--m){
				c.a.append(1u,sum[m]+'0');
		}
		return c;
}
BigNum BigNum::operator-(const BigNum & b){
		int lena, lenb, i, m, sign(0);
		string sa,sb;
		BigNum c;
		int cal[200];
		lena = a.length();
		lenb = b.a.length();
		if(lena > lenb){sa=a; sb=b.a; sign =1;}
		else if(lena < lenb){sa = b.a; sb = a; sign=-1;}
		else{
				m=lena-1;
				while(m>=0){
						if(a[m]>b.a[m]){sa=a; sb=b.a; sign =1;break;}
						else if(a[m]<b.a[m]){sa=b.a; sb=a; sign =-1;break;}
						--m;
				}
		}	
		if(m==-1 && sign==0) {c.a="0"; return c;}
		lena = sa.length();
		lenb = sb.length();
		i=0;
		while(lena>0 && lenb>0){
				if(sa[lena-1]>=sb[lenb-1]) cal[i]=sa[lena-1]-sb[lenb-1];
				else {cal[i]=10+sa[lena-1]-sb[lenb-1]; --sa[lena-2];}
				--lena;
				--lenb;
				++i;
		}	
		while(lena>0){
				cal[i]=sa[lena-1]-'0';
				--lena;
				++i;
		}
		if(sign==-1)
				c.a = "-";
		for(m=i-1;m>=0;--m)
				c.a.append(1u,cal[m]+'0');
		i = 0;
		while(c.a.at(i)=='0') ++i;
		c.a = c.a.substr(i,c.a.length()-i+1);

		return c;
}
BigNum BigNum::operator*(const BigNum &b){
		BigNum c;
		int m(0),m_tmp(0),len,i,j,lena,lenb;
		int tmp(0);
		int cal[200]={0};
		lena=a.length();
		lenb=b.a.length();
		for(i=lena-1;i>=0;--i){
				for(j=lenb-1;j>=0;--j){
						tmp=cal[m]+tmp+(a[i]-'0')*(b.a[j]-'0');
						cal[m]=tmp%10;
						tmp=tmp/10;
						++m;
						len = m;
				}
				while(tmp%10!=0){
						tmp=cal[m]+tmp;
						cal[m]=tmp%10;
						tmp=tmp/10;
						++m;
						len = m;
				}
				++m_tmp;
				m=m_tmp;
		}
		for(i=len-1;i>=0;--i)
				c.a.append(1u,cal[i]+'0');
		return c;
}

BigNum BigNum::operator/(const BigNum & b){
		BigNum c;
		string a_tmp;
		int cal[200]={0};
		int i,m,lena,lenb,len(0);
		lena = a.length();
		lenb = b.a.length();
		if(lena<lenb) {c.a = "0"; return c;}
		else{
				BigNum ca_tmp(a.substr(0,lenb));
				m=lenb;
				BigNum b_tmp = b;
				if(ca_tmp<b_tmp){ca_tmp.a.append(1u,a[m]); ++m;}
				while(m<=lena){
						for(i=0;i<=9;++i){
								char s1=i+'0', s2=i+'1';
								string s1_tmp, s2_tmp;
								s1_tmp.append(1u,s1);
								s2_tmp.append(1u,s2);
								BigNum c1(s1_tmp),c2(s2_tmp),c1_tmp,c2_tmp;
								c1_tmp=c1*b;
								c2_tmp=c2*b;
								if (c1_tmp<ca_tmp && !(c2_tmp<ca_tmp)){
										cal[len]=i;
										++len;
										ca_tmp = ca_tmp-c1_tmp;
										break;
								}
						}
						if(ca_tmp.a=="0") ca_tmp.a="";
						if(m<lena)
								ca_tmp.a.append(1u,a[m]);
						++m;
				}
		}
		if(len == 0)
				c.a="0";	
		for(i=0;i<len;++i)
				c.a.append(1u,cal[i]+'0');
		return c;
}
ostream & operator<<(ostream & os , BigNum & b){
		os<<b.a;
		return os;
}

bool BigNum::operator < (BigNum& c){
		int i, len1, len2;
		len1 = a.length();
		len2 = c.a.length();
		if(len1<len2) return true;
		else if(len1>len2) return false;
		for(i=0;i<len1;++i){
				if(a[i]<c.a[i]) return true;
				else if(a[i]>c.a[i]) return false;
		}
		return true;
}

int main(){
		char o;
		string s1,s2;
		BigNum c;
		cin>>s1>>o>>s2;
		BigNum a(s1),b(s2);
		switch(o){
				case '+': {c=a+b;break;}
				case '-': {c=a-b;break;}
				case '*': {c=a*b;break;}
				case '/': {c=a/b;break;}
		}
		cout<<c<<endl;	
		return 0;
}

