namespace Seg
{
	struct SEG{int l,r,sum,tag,vl,vr;}t[N];int Rt,cnt;
	inline void update(int k){t[k].sum=t[t[k].l].sum+t[t[k].r].sum;}
	inline void pushdown(int k)
	{
		if(t[k].l)t[t[k].l].sum+=t[k].tag*(t[t[k].l].vr-t[t[k].l].vl+1),t[t[k].l].tag+=t[k].tag;
		if(t[k].r)t[t[k].r].sum+=t[k].tag*(t[t[k].r].vr-t[t[k].r].vl+1),t[t[k].r].tag+=t[k].tag;t[k].tag=0;
	}
	void add(int cur,int ql,int qr,int val,int l,int r)
	{
		int l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		if(ql<=l&&r<=qr){t[cur].sum+=val*(r-l+1);t[cur].tag+=val;return;}
		pushdown(cur);if(ql<=mid)add(t[cur].l,ql,qr,val,l,mid);
		if(qr>mid)add(t[cur].r,ql,qr,val,mid+1,r);update(cur);
	}
	int query(int cur,int ql,int qr,int l,int r)
	{
		int res=0,l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		pushdown(cur);if(ql<=l&&r<=qr){return t[cur].sum;}
		if(ql<=mid)res+=query(t[cur].l,ql,qr,l,mid);
		if(qr>mid)res+=query(t[cur].r,ql,qr,mid+1,r);update(cur);return res;
	}
	void build(int l,int r,int &cur)
	{
		t[cur=++cnt].vl=l;t[cur].vr=r;if(l==r){t[cur].sum=a[l];return;}
		int mid=(l+r)>>1;if(l<=mid)build(l,mid,t[cur].l);
		if(r>mid)build(mid+1,r,t[cur].r);update(cur);
	}
    int find(int cur,int ql,int qr,int x,int l,int r)
	{
		int l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		if(ql<=l&&r<=qr)
		{
			if(t[cur].sum<x)return -1;
			if(l==r)return l;
			pushdown(cur);
			if(t[t[cur].l].sum>=x)return find(t[cur].l,ql,qr,x,l,mid);
			return find(t[cur].r,ql,qr,x-t[t[cur].l].sum,mid+1,r);
		}
		pushdown(cur);
		if(qr<=mid)return find(t[cur].l,ql,qr,x,l,mid);
		if(ql>mid)return find(t[cur].r,ql,qr,x,mid+1,r);
		int res=find(t[cur].l,ql,qr,x,l,mid);
		if(res!=-1)return res;
		int sum=query(t[cur].l,ql,mid,l,mid);
		return find(t[cur].r,ql,qr,x-sum,mid+1,r);
	}
	inline int merge(int x,int y,int l=1,int r=N-10)
	{
		if(!x||!y)return x|y;
		if(l==r){t[x].sm+=t[y].sm;return x;}
		int mid=(l+r)>>1;
		t[x].l=merge(t[x].l,t[y].l,l,mid);
		t[x].r=merge(t[x].r,t[y].r,mid+1,r);
		update(x);return x;
	}
}