namespace Seg
{
	struct SEG{int l,r,sum,tag,vl,vr;}t[N];int Rt,cnt;
	inline void update(int k){t[k].sum=t[t[k].l].sum+t[t[k].r].sum;}
	inline void pushdown(int k)
	{
		if(t[k].l)t[t[k].l].sum+=t[k].tag*(t[t[k].l].vr-t[t[k].l].vl+1),t[t[k].l].tag+=t[k].tag;
		if(t[k].r)t[t[k].r].sum+=t[k].tag*(t[t[k].r].vr-t[t[k].r].vl+1),t[t[k].r].tag+=t[k].tag;t[k].tag=0;
	}
	void add(int cur,int ql,int qr,int val)
	{
		int l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		if(ql<=l&&r<=qr){t[cur].sum+=val*(r-l+1);t[cur].tag+=val;return;}
		pushdown(cur);if(ql<=mid)add(t[cur].l,ql,qr,val);
		if(qr>mid)add(t[cur].r,ql,qr,val);update(cur);
	}
	int query(int cur,int ql,int qr)
	{
		int res=0,l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		pushdown(cur);if(ql<=l&&r<=qr){return t[cur].sum;}
		if(ql<=mid)res+=query(t[cur].l,ql,qr);
		if(qr>mid)res+=query(t[cur].r,ql,qr);update(cur);return res;
	}
	void build(int l,int r,int &cur)
	{
		t[cur=++cnt].vl=l;t[cur].vr=r;if(l==r){t[cur].sum=a1[l];return;}
		int mid=(l+r)>>1;if(l<=mid)build(l,mid,t[cur].l);
		if(r>mid)build(mid+1,r,t[cur].r);update(cur);
	}
    int find(int cur,int ql,int qr,int x)
	{
		int l=t[cur].vl,r=t[cur].vr,mid=(l+r)>>1;
		if(ql<=l&&r<=qr)
		{
			if(t[cur].sum<x)return -1;
			if(l==r)return l;
			pushdown(cur);
			if(t[t[cur].l].sum>=x)return find(t[cur].l,ql,qr,x);
			return find(t[cur].r,ql,qr,x-t[t[cur].l].sum);
		}
		pushdown(cur);
		if(qr<=mid)return find(t[cur].l,ql,qr,x);
		if(ql>mid)return find(t[cur].r,ql,qr,x);
		int res=find(t[cur].l,ql,qr,x);
		if(res!=-1)return res;
		int sum=query(t[cur].l,ql,mid);
		return find(t[cur].r,ql,qr,x-sum);
	}
}