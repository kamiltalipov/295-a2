#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
using namespace std;
class Hash_table{
public:
	vector<vector <string> > s;
	int mod;
	int pr;
	int number;
	Hash_table() { s.resize(128); mod = 128; pr = 97; number=0; }
	class iterator{
	private:
		Hash_table *table;
		int r;
		vector <string> :: iterator it;
	public:
		iterator() {}
		iterator(int R, vector<string>::iterator It) { r = R; it = It; }
		bool operator !=(iterator it1){
			return it1.it != it;
		}
		iterator operator ++(){
			it++;
			if(it == table->s[r].end() && r+1!=table->mod)
					it=table->s[r+1].begin();
			return *this;
		}
		iterator operator --(){
			if(it == table->s[r].begin() && r!=0)
				it=table->s[r-1].end() - 1;
			else
				it--;
		}
		string operator *(){
			if(it==table->s[r].end())
				runtime_error("forbidden");
			return *it;
		}
	};
	iterator begin(){
		return iterator(0, s[0].begin());
	}
	iterator end(){
		return iterator(mod - 1, s[mod - 1].end()); 
	}
	int count_hash(string q){
		int ans=q[0]%mod;
		for(int i=1;i<q.length();i++)
			ans=(ans*pr+q[i])%mod;
		return ans;
	}
	
	void reallocate(){
		vector <string> w;
		for(iterator t=begin(); t != end(); ++t)
			w.push_back(*t);
		for(int i=0;i<mod;i++)
			s[i].clear();
		mod=2*number;
		for(int i=0;i<w.size();i++)
			insert(w[i]);
	}

	void insert(string q){
		int hash=count_hash(q);
		for(int i=0;i<s[hash].size();i++)
			if(s[hash][i]==q)
				return;
		s[hash].push_back(q);
		number++;
		if(number>4*mod)
			reallocate();
	}
	void remove(string q){
		int hash=count_hash(q);
		for(vector <string>::iterator i=s[hash].begin();i!=s[hash].end();i++)
			if((*i)==q){
				s[hash].erase(i);
				number--;
				if(4*number<mod)
					reallocate();
				return;
			}
	}
	bool find(string q){
		int hash=count_hash(q);
		for(int i=0;i<s[hash].size();i++)
			if(s[hash][i]==q)
				return true;
		return false;
	}
	int max_kollizy(){
		int ans=0;
		for(int i=0;i<mod;i++)
			ans=max(ans,(int)s[i].size());
		return ans;
	}
	int size(){
		int ans=0;
		for(int i=0;i<mod;i++)
			ans+=(int)s[i].size();
		return ans;
	}
};

int main(){
	return 0;
}