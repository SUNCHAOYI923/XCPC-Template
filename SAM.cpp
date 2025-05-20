class SAM
{
	class node
	{
		public:int ch[26],len,fa;
		node (const int &L = 0) {memset (ch,0,sizeof (ch));fa = 0;len = L;}
	};
	public:
	vector <node> t;int lst;
	void GetParentTree (vector <vector <int>> &G)
	{
		G.resize (t.size ());
		for (unsigned i = 1;i < t.size ();++i) G[t[i].fa].push_back (i);
	}
	void extend (const int &c)
	{
		int p = lst,np = lst = t.size ();
		t.push_back (node (t[p].len + 1));
		for (;p&&!t[p].ch[c];p = t[p].fa) t[p].ch[c] = np;
 		if (!p) t[np].fa = 1;
 		else
 		{
 			int v = t[p].ch[c];
 			if (t[v].len == t[p].len + 1) t[np].fa = v;
 			else
 			{
 				int nv = t.size ();t.push_back (t[v]);
 				t[nv].len = t[p].len + 1;
 				for (;p && t[p].ch[c] == v;p = t[p].fa) t[p].ch[c] = nv;
 				t[np].fa = t[v].fa = nv;
			}
		}
	}
	SAM () {t.assign (2,node ());lst = 1;}
	inline void clear () {t.assign (2,node ());lst = 1;}
	inline int next (int p,int c) {return t[p].ch[c];}
	inline int Len (int p) {return t[p].len;}
};