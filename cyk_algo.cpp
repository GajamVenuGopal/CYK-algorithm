#include<bits/stdc++.h>
using namespace std;

vector<string> wordsof(string str)					//returns the string array of str...
{
	vector<string> tmpset;
	string tmp="";
	int i=0;
	while(str[i])
	{
		if(isalnum(str[i]))tmp+=str[i];
		else {
			if(tmp.size()>0)
				tmpset.push_back(tmp);
			tmp="";
		}
		i++;
	}
	if(tmp.size()>0)tmpset.push_back(tmp);
	return tmpset;
}
string combine(vector<string> &arr,int miss)					//combines the strings in the array and return the combined string...
{
	string str;
	for(int i=0;i<arr.size();i++)
		if(i!=miss)str+=arr[i]+" ";
	str=str.substr(0,str.size()-1);
	return str;
}
void formProds(string pfile,map<string, vector<string> >&prods)
{
	ifstream fin;
	fin.open(pfile.c_str());
	string line;
	while(!fin.eof())
	{
		getline(fin,line);
		vector<string> tokens=wordsof(line);
		prods[tokens[0]].push_back(combine(tokens,0));
	}
}
void printProds(map<string,vector<string> >&prods)
{
	map<string, vector<string> > ::iterator it=prods.begin();
	
	while(it!=prods.end())
	{
		cout<<it->first<<"-> ";
		for(int i=0;i<it->second.size();i++)cout<<it->second[i]<<" / ";
		cout<<endl;
		it++;
	}
}

void printTable(vector<vector<set<string> > >&table,int n)
{
	cout<<endl;
	for(int i=1;i<=n;i++)cout<<"( "<<*table[0][i].begin()<<" ) ";
	cout<<endl<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n-i+1;j++)
		{
			cout<<"( ";
			
			for(set<string> ::iterator it=table[i][j].begin();it!=table[i][j].end();it++)
				cout<<*it<<",";
			cout<<"\b ) ";
		}
		cout<<endl;
	}
}
int main(){
	
	map<string,vector<string> > prods;
	vector<string> input;
	string line;
	
	formProds("cyk_algo.in",prods);
	printProds(prods);
	
	
	cout<<"Input String:";
	getline(cin,line);
	input=wordsof(line);
	
	vector<vector<set<string> > >table(input.size()+1,vector<set<string> > (input.size()+1));
	
	for(int i=1;i<=input.size();i++)table[0][i].insert(input[i-1]);
	for(int j=1;j<=input.size();j++)
	{
		map<string, vector<string> >:: iterator it=prods.begin();
		for(;it!=prods.end();it++)
			if(find(it->second.begin(),it->second.end(),*table[0][j].begin())!=it->second.end())
				table[1][j].insert(it->first);
	}
	for(int i=2;i<=input.size();i++)
	{
		for(int j=1;j<=input.size()-i+1;j++)
		{
			for(int k=1;k<i;k++)
			{
				for(set<string>::iterator it1=table[k][j].begin();it1!=table[k][j].end();it1++)
				{
					for(set<string>::iterator it2=table[i-k][k+j].begin();it2!=table[i-k][k+j].end();it2++)
					{
						for(map<string, vector<string> >:: iterator it3=prods.begin();it3!=prods.end();it3++)
							if(find(it3->second.begin(),it3->second.end(),(*it1)+" "+(*it2))!=it3->second.end())
								table[i][j].insert(it3->first);
					}
				}
			}
		}
	}
	printTable(table,input.size());
	if(table[input.size()][1].find("S")!=table[input.size()][1].end())cout<<"input string is part of language!!\n";
	else cout<<"input string is not part of language!!\n";
	return 0;
}

