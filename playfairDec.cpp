#include <iostream>
#include <map>
using namespace std;
class Decrypt 
{
	private:
  	string inptext, key, decptext;
  	char mat[5][5];
  	map<char, pair<int, int>> mapp;
  	
	void makeMatrix();
  	//string makePairs();

	public:
  	Decrypt(string, string);
  	void decrypt();
	string getDecpText();
};
Decrypt::Decrypt(string inp, string k) 
{
	inptext = inp;
	key = k;
}
void Decrypt::makeMatrix() 
{
  	string t = "";
  	for (char c : key) 
  	{
    		if (c == 'J')
      			c = 'I';
    		if (t.find(c) == string::npos)
      			t += c;
  	}
  	for (char c = 'A'; c <= 'Z'; c++) 
  	{
    		if (t.find(c) == string::npos && c != 'J')
      			t += c;
  	}
  	int l = 0;
  	for (int i = 0; i < 5; i++) 
  	{
    		for (int j = 0; j < 5; j++) 
    		{
      			mapp[t[l]] = {i, j};
      			mat[i][j] = t[l];
      			l++;
    		}
  	}
}
/*string Decrypt::makePairs() 
{
  	string p = "";
  	p += inptext[0];
  	for (int i = 1; i < inptext.length(); i++) 
  	{
    		if (inptext[i] == inptext[i - 1] && p.length() % 2 != 0)
      			p += 'X';

    		p += inptext[i];
  	}
  	if (p.length() % 2 != 0)
    		p += 'Z';

  	return p;
}
*/
void Decrypt::decrypt() 
{
  	makeMatrix();
  	char a, b;
  	decptext = "";
  	for (int i = 0; i < inptext.length(); i += 2) 
  	{
    		a = inptext[i] == 'J' ? 'I' : inptext[i];
    		b = inptext[i + 1] == 'J' ? 'I' : inptext[i + 1];
    		if (mapp[a].first == mapp[b].first) 
    		{
      			decptext += mat[mapp[a].first][(mapp[a].second - 1 + 5) % 5];
      			decptext += mat[mapp[b].first][(mapp[b].second - 1 + 5) % 5];
    		} 
    		else if (mapp[a].second == mapp[b].second) 
    		{
      			decptext += mat[(mapp[a].first - 1 + 5) % 5][mapp[a].second];
      			decptext += mat[(mapp[b].first - 1 + 5) % 5][mapp[b].second];
    		} 
    		else 
    		{
      			decptext += mat[mapp[a].first][mapp[b].second];
     	 		decptext += mat[mapp[b].first][mapp[a].second];
    		}
  	}
}
string Decrypt::getDecpText()
{
	return decptext;
}

int main() 
{
	string inp,k;
	cout<<"Enter text: ";
	cin>>inp;
	cout<<"Enter key: ";
	cin>>k;
  	Decrypt d(inp,k);
  	d.decrypt();
	cout<<"Decrypted text: "<<d.getDecpText()<<"\n";
	return 0;
}
