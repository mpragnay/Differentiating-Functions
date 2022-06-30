//Representation:
//For implementing chain rule I have taken function like f(g(x)) ex:sin(tan(x))
//Power of a function represented as sin^(n)(x)

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

string differentiate(string);
int universal=0;

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

string multiply(string a,string b)
{
	int coef=getcoef(a)*getcoef(b),st=0,i=0,j=0;
	string c,d,res;
	if(a[0]=='-')
	st=1;
	for(i=st;i<a.length();i++)
	{
		if(a[i]<58 && a[i]>47)
		continue;
		break;
	}
	while(i<a.length())
	{
		c.push_back(a[i]);
		i++;
	}
	st=0;
	if(b[0]=='-')
	st=1;
	for(j=st;j<b.length();j++)
	{
		if(b[j]<58 && b[j]>47)
		continue;
		break;
	}
	
	while(j<b.length())
	{
		d.push_back(b[j]);
		j++;
	}
	if(coef!=1 && coef!=-1)
	res=numtostr(coef);
	else
	{
		if(coef==-1)
		res+='-';
	}
	res+=c;res+=d;
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
	
	else											//If function is of type f(g(x)) to implement chain rule we have this part
	{
		string der1=diff(inp2),res1;
		//cout<<der1<<endl;
		
		int start=0;
		if(der1[0]=='-')
		start=1;
		int sz;
		for(sz=start;sz<der1.length();sz++)
		{
			if(der1[sz]<58 && der1[sz]>47)
			continue;
			else break;
		}
		int ck=1;									//variable ck is used to check if we need to print g'(x) 
		coef*=getcoef(der1);
		if(sz==der1.length())
		{
			ck=0;
		}
		else
		{
			while(sz<der1.length())
			{
				res1.push_back(der1[sz]);
				sz++;
			}
		}
		//cout<<coef<<endl;
		
		if(inp=="cosec")									
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="cosec(";res+=inp2;res+=")cot(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="sec")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="sec(";res+=inp2;res+=")tan(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="arcsin")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1-(";res+=inp2;res+=")^(2))";res+="^(-1/2)";
			return res;
		}
		if(inp=="arccos")
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1-(";res+=inp2;res+=")^(2))";res+="^(-1/2)";
			return res;
		}
		if(inp=="arctan")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1+(";res+=inp2;res+=")^(2))";res+="^(-1)";
			return res;
		}
		if(inp=="arccot")
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1+(";res+=inp2;res+=")^(2))";res+="^(-1)";
			return res;
		}
		if(inp=="arccosec")
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="((";res+=inp2;res+=")^(2)-1)^(-1/2)/(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="arcsec")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="((";res+=inp2;res+=")^(2)-1)^(-1/2)/(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="tanh")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1-tanh^(2)(";res+=inp2;res+="))";
			return res;
		}
		if(inp=="coth")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(1-coth^(2)(";res+=inp2;res+="))";
			return res;
		}
		if(inp=="cosech")
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="cosech(";res+=inp2;res+=")coth(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="sech")
		{
			coef*=-1;
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="sech(";res+=inp2;res+=")tanh(";res+=inp2;res+=")";
			return res;
		}
		if(inp=="ln")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="(";res+=inp2;res+=")^(-1)";
			return res;
		}
		if(inp=="sin^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="sin(";res+=inp2;res+=")";
				res+=derivative;
				res+="(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="sin^(";
				res+=numtostr(pow);
				res+=")";
				res+="(";res+=inp2;res+=")";
				res+=derivative;
				res+="(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="cos^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cos(";res+=inp2;res+=")";
				res+="sin(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cos^(";
				res+=numtostr(pow);
				res+=")(";
				res+=inp2;res+=")";
				res+="sin(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="tan^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="tan(";res+=inp2;res+=")";
				res+=derivative;
				res+="(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="tan^(";
				res+=numtostr(pow);
				res+=")(";
				res+=inp2;res+=")";
				res+=derivative;
				res+="(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="cot^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cot(";res+=inp2;res+=")";
				res+="cosec^(2)(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cot^(";
				res+=numtostr(pow);
				res+=")(";
				res+=inp2;res+=")";
				res+="cosec^(2)(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="cosh^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cosh(";res+=inp2;res+=")";
				res+="sinh(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="cosh^(";
				res+=numtostr(pow);
				res+=")";
				res+="(";res+=inp2;res+=")";
				res+="sinh(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="sinh^")
		{
			if(pow==1)
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="sinh(";res+=inp2;res+=")";
				res+="cosh(";res+=inp2;res+=")";
			}
			else
			{
				coef*=getcoef(derivative);
				res=numtostr(coef);
				if(ck)
			    res+=res1;
				res+="sinh^(";
				res+=numtostr(pow);
				res+=")";
				res+="(";res+=inp2;res+=")";
				res+="cosh(";res+=inp2;res+=")";
			}
			return res;
		}
		if(inp=="e^")
		{
			res=numtostr(coef);
			if(ck)
			res+=res1;
			res+="e^(";res+=inp2;res+=")";
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
		if(ck)
		res+=res1;
		res+=der;res+="(";res+=inp2;res+=")";
		return res;	
	}
}

string differentiate(string a)								//Differentiates any expression implementing u*v,u/v,u+v,u-v and chain rules
{
	universal++;
	string inp1,inp2,inp,res;
	if(a[0]=='(')											//cases for product,division or powers of complex functions
	{
		//cout<<"False"<<endl;
		int brackt=1,j=1;
		while(j<a.length())
		{
			if(a[j]=='(')
			brackt++;
			if(a[j]==')')
			brackt--;
			if(brackt==0)
			break;
			inp1.push_back(a[j]);
			j++;
		}
		//cout<<'\n'<<inp1<<endl;
		j++;
		if(j==a.length())
		res=diff(inp1);
		else
		{
			//cout<<"Maybe"<<endl;
			string der1,der2;
			int l=j;
			j+=2;
			int b1=1;
			while(j<a.length())
			{
				if(a[j]=='(')
				b1++;
				if(a[j]==')')
				b1--;
				if(b1==0)
				break;
				inp2.push_back(a[j]);
				j++;
			}
			der1=diff(inp1),der2=diff(inp2);
			if(a[l]=='*')									//case for product rule
			{
				res+=multiply(inp1,der2);
				string check=multiply(inp2,der1);
				if(check[0]!='-')
				res+="+";
				res+=check;
			}
			else											//case for quotient rule
			{
				res+="(";
				res+=multiply(der1,inp2);
				string check=multiply(inp1,der2);
				string add;
				if(check[0]=='-')
				{
					res+="+";
					for(int index=1;index<check.length();index++)
					add.push_back(check[index]);
				}
				else
				{
					res+="-";
					add=check;
				}
				res+=add;res+=")/(";res+=inp2;res+=")^(2)";
			}
		}
		j++;
		if(j!=a.length())
		{
			if(a[j]=='+')
			j++;
			string restof;
			while(j<a.length())
			{
				restof.push_back(a[j]);
				j++;
			}
			string remadd=diff(restof);
			if(remadd[0]!='-')
			res+='+';
			res+=remadd;
		}
	}
	
	else													//cases for simpler functions 
	{
		//cout<<"True"<<endl;
		string terms[100];
		int ind=0,simple=1,start,done=0;
		char prev='+';
		if(a[0]=='-')
		{
			prev='-';
			start=1;
		}
		for(int i=start;i<a.length();i++)
		{
			cout<<"Yes "<<endl;
			if(a[i]=='^')
			{
				//cout<<"1"<<endl;
				while(a[i]!=')')
				{
					terms[ind].push_back(a[i]);
					i++;
				}
				terms[ind].push_back(a[i]);
				i++;
			}
			if(a[i]=='(')
			{
				//cout<<"2 "<<endl;
				int brackt=0;
				while(i<a.length())
				{
					if(a[i]=='*' || a[i]=='/')
					simple=0;
					if(a[i]=='(')
					brackt++;
					if(a[i]==')')
					brackt--;
					terms[ind].push_back(a[i]);
					if(brackt==0)
					break;
					i++;
				}
			}
			if(a[i]=='-' || a[i]=='+')
			{
				done=1;												//remember to write done=1 later
				//cout<<"3 "<<endl;
				string resi,resf;
				if(simple)
				{
					//cout<<"4 "<<endl;
					resi=diff(terms[ind]);
					if(resi[0]=='-')
					{
						if(prev=='+')
						resf=resi;
						else
						{
							resf+='+';
							for(int k=1;k<resi.length();k++)
							resf.push_back(resi[k]);
						}
					}
					else
					{
						res+=prev;
						resf=resi;
					}
					res+=resf;
					ind++;
					prev=a[i];
					i++;
				}
				else
				{
					resi=diff(terms[ind]);
					if(resi[0]=='-')
					{
						if(prev=='+')
						resf=resi;
						else
						{
							resf+='+';
							for(int k=1;k<resi.length();k++)
							resf.push_back(resi[k]);
						}
					}
					else
					{
						res+=prev;
						resf=resi;
					}
					res+=resf;
					ind++;
				}
			}
			terms[ind].push_back(a[i]);
		}
		string resi,resf;
		if(simple)
		{
			resi=diff(terms[ind]);
			//cout<<resi<<endl;
			if(resi[0]=='-')
			{
				if(prev=='+')
				resf=resi;
				else
				{
					resf+='+';
					for(int k=1;k<resi.length();k++)
					resf.push_back(resi[k]);
				}
			}
			else
			{
				res+=prev;
				resf=resi;
			}
			res+=resf;
			ind++;
		}
		else
		{
			resi=diff(terms[ind]);
			if(resi[0]=='-')
			{
				if(prev=='+')
				resf=resi;
				else
				{
					resf+='+';
					for(int k=1;k<resi.length();k++)
					resf.push_back(resi[k]);
				}
			}
			else
			{
				res+=prev;
				resf=resi;
			}
			res+=resf;
			ind++;
		}
	}
	string resfinal;
	int st=0;
	if(res[0]=='+')
	st=1;
	for(int n=st;n<res.length();n++)
	resfinal.push_back(res[n]);
	return resfinal;
}
int main()
{
	fstream myfile;
	myfile.open("input3.txt");
	string inp;
	char t;
	while(myfile.get(t))
	inp.push_back(t);
	cout<<"Input:"<<inp<<endl;
	cout<<"Output:"<<differentiate(inp)<<endl;
}
