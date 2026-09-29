struct ACAM
{
	struct Node
	{
		int ch[27],tot,nxt;bool vis;
		Node(){memset(ch,0,sizeof(ch));tot=nxt=0;vis=false;}
	};
	vector<Node> a;queue<int> q;
	inline void Init(){a.assign(1,Node());return;}
	ACAM(){a.assign(1,Node());return;}
	inline int newNode()
	{
		int tmp=a.size();
		a.push_back(Node());
		return tmp;
	}
	inline void ins(char *s)
	{
		int p=0,len=strlen(s);
		rep(0,len-1,i)
		{
			int x=a[p].ch[s[i]-'a'];
			if(!x)x=newNode(),a[p].ch[s[i]-'a']=x;p=x;
		}
		a[p].tot++;
		
	}
	inline void build()
	{
		while(!q.empty())q.pop();
		rep(0,26,i)if(a[0].ch[i])
		{
			q.push(a[0].ch[i]);
			a[a[0].ch[i]].nxt=0;
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			rep(0,26,i)
			{
				if(a[u].ch[i])
				{
					q.push(a[u].ch[i]);
					a[a[u].ch[i]].nxt=a[a[u].nxt].ch[i];
				}
				else
				{
					a[u].ch[i]=a[a[u].nxt].ch[i];
				}
			}
		}
	}
	inline int qry(char *s)
	{
		for(Node&v:a)v.vis=false;
		int len=strlen(s),p=0,ans=0;
		rep(0,len-1,i)
		{
			p=a[p].ch[s[i]-'a'];
			for(int j=p;!a[j].vis&&j;j=a[j].nxt)
			{
				ans+=a[j].tot;
				a[j].vis=true;
			}
		}
		return ans;
	}
};

/*
s1
s2
s3
...

qry(t): how many s_i is substring of t
*/