//Inverse trignometric functions are represented as arcsin,arccos,arctan,arccot,arccosec,arcsec
//Logarithm represented as ln(x)
//Give input without spaces


#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

int getcoef(string a)
{
	char sign='+';
	int i=0;
	if(a[0]=='-')
	{
		sign='-';
		i=1;
	}
	int coef=0;
	//cout<<i<<endl;
	while(a[i]<58 && a[i]>47)							//Returns coefficient of a term
	{
		int c=a[i]-'0';
		//cout<<c;
		coef=coef*10+c;
		i++;
	}
	if(coef==0)
	coef=1;
	if(sign=='-')
	coef*=-1;
	return coef;
}

string numtostr(int a)
{
	string res;
	if(a<0)
	{
		a=a*(-1);
		res="-";
	}
	int arr[10],l=0;
	while(a!=0)
	{
		int num=a%10;								//returns integer as string with sign
		arr[l]=num;
		l++;
		a/=10;
	}
	l--;
	while(l>=0)
	{
		char c=arr[l]+48;
		res.push_back(c);
		l--;
	}
	return res;
}



string diff(string a)
{
	int coef=getcoef(a);							//Function returns derivative of a term
	string inp;
	int j=0;
	for(int i=0;i<a.length();i++)
	{
		if(a[i]=='-')
		continue;
		if(a[i]<58 && a[i]>47)
		continue;
		if(a[i]=='(')
		{
			j=i;
			break;
		}
		inp.push_back(a[i]);
	}
	//cout<<a[j]<<endl;
	string inp2;
	int pow=0;
	if(j==0)
	{
		if(inp!="x")
		return "0";
		else
		return numtostr(coef);
	}
	else
	{
		if(a[j-1]=='^' && a[j-2]!='e')
		{
			j++;
			int multi=1;
			if(a[j]=='-')
			{
				multi=-1;
				j++;
			}
			while(a[j]!=')')
			{
				int digit=a[j]-'0';
				pow=pow*10+digit;
				j++;
			}
			pow*=multi;
			j++;
		}
		int brackt=1;
		j++;
		while(j<a.length())
		{
			if(a[j]=='(')
			brackt++;
			if(a[j]==')')
			brackt--;
			if(brackt==0)
			break;
			inp2.push_back(a[j]);
			j++;
		}
		//cout<<inp2<<endl;
	}
	int isx=0;
	if(inp2=="x" || inp=="x^")
	{
		isx=1;
	}
	
	//CASES FOR DERIVATIVE
	string derivative,res;
	if(inp=="sin" || inp=="sin^")
	derivative="cos";
	if(inp=="cos" || inp=="cos^")
	derivative="-sin";
	if(inp=="tan" || inp=="tan^")
	derivative="sec^(2)";
	if(inp=="cot" || inp=="cot^")
	derivative="-cosec^(2)";
	if(inp=="sinh" || inp=="sinh^")
	derivative="cosh";
	if(inp=="cosh" || inp=="cosh^")
	derivative="sinh";
	if(inp=="e^")
	derivative="e^";
	//int len=inp.length();
	//int index=0;
	if(pow)
	{
		coef*=pow;
		pow-=1;
		string power=numtostr(pow);
		//res=numtostr(coef);
		if(inp=="x^")
		{
			res=numtostr(coef);
			if(pow==1)
			res+="x";
			else
			{
				res+=inp;
				res+="(";
				res+=power;
				res+=")";
			}
			return res;
		}
	}
	
	if(isx)
	{
		if(inp=="cosec")									//If function is of the form f(x) we can directly return the answer
		{
			coef*=-1;
			res=numtostr(coef);
			res+="cosec(x)cot(x)";
			return res;
		}
		if(inp=="sec")
		{
			res=numtostr(coef);
			res+="sec(x)tan(x)";
			return res;
		}
		if(inp=="arcsin")
		{
			res=numtostr(coef);
			res+="(1-x^(2))^(-1/2)";
			return res;
		}
		if(inp=="arccos")
		{
			coef*=-1;
			res=numtostr(coef);
			res+="(1-x^(2))^(-1/2)";
			return res;
		}
		if(inp=="arctan")
		{
			res=numtostr(coef);
			res+="(1+x^(2))^(-1)";
			return res;
		}
		if(inp=="arccot")
		{
			coef*=-1;
			res=numtostr(coef);
			res+="(1+x^(2))^(-1)";
			return res;
		}
		if(inp=="arccosec")
		{
			coef*=-1;
			res=numtostr(coef);
			res+="(x^(2)-1)^(-1/2)/x";
			return res;
		}
		if(inp=="arcsec")
		{
			res=numtostr(coef);
			res+="(x^(2)-1)^(-1/2)/x";
			return res;
		}
		if(inp=="tanh")
		{
			res=numtostr(coef);
			res+="(1-tanh^(2)(x))";
			return res;
		}
		if(inp=="coth")
		{
			res=numtostr(coef);
			res+="(1-coth^(2)(x))";
			return res;
		}
		if(inp=="cosech")
		{
			coef*=-1;
			res=numtostr(coef);
			res+="cosech(x)coth(x)";
			return res;
		}
		if(inp=="sech")
		{
			coef*=-1;
			res=numtostr(coef);
			res+="sech(x)tanh(x)";
			return res;
		}
		if(inp=="ln")
		{
			res=numtostr(coef);
			res+="x^(-1)";
			return res;
		}
		
		if(inp=="sin^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="sin(x)";
				res+=derivative;
				res+="(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="sin^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+=derivative;
				res+="(x)";
			}
			return res;
		}
		if(inp=="cos^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cos(x)";
				res+="sin(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cos^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+="sin(x)";
			}
			return res;
		}
		if(inp=="tan^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="tan(x)";
				res+=derivative;
				res+="(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="tan^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+=derivative;
				res+="(x)";
			}
			return res;
		}
		if(inp=="cot^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cot(x)";
				res+="cosec^(2)(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cot^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+="cosec^(2)(x)";
			}
			return res;
		}
		if(inp=="cosh^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cosh(x)";
				res+="sinh(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="cosh^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+="sinh(x)";
			}
			return res;
		}
		if(inp=="sinh^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="sinh(x)";
				res+="cosh(x)";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				res+="sinh^(";
				res+=numtostr(pow);
				res+=")";
				res+="(x)";
				res+="cosh(x)";
			}
			return res;
		}
		if(inp=="e^")
		{
			res=numtostr(coef);
			res+="e^(x)";
			return res;
		}
		
		coef*=getcoef(derivative);
		string der;
		if(derivative[0]=='-')
		{
			for(int size=1;size<derivative.length();size++)
			der.push_back(derivative[size]);
		}
		else
		der=derivative;
		
		res=numtostr(coef);
		res+=der;
		res+="(x)";
		return res;
	}
}

int main()
{
	fstream myfile;
	myfile.open("input1.txt");
	string inp;
	char t;
	while(myfile.get(t))
	inp.push_back(t);
	cout<<"Input:"<<inp<<endl;
	//cout<<getcoef(inp);
	cout<<diff(inp);
	//int a;
	//cin>>a;
	//cout<<numtostr(a);
}
