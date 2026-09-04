struct Seg{int l,r,val;}t[N*64]; int cnt,a[N],Rt[N],dep[N],Mx[N];
inline void build(int &x,int l,int r)
{
	int mid=(l+r)>>1;x=++cnt;if(l==r){t[x].val=a[l];return;}
	build(t[x].l,l,mid);build(t[x].r,mid+1,r);return;
}
inline void Fix(int cur,int &x,int loc,int val,int l,int r)
{
	t[x=++cnt]=t[cur];int mid=(l+r)>>1;
	if(l==r){t[x].val=val;dep[x]=dep[cur];return;}
	if(loc<=mid)Fix(t[cur].l,t[x].l,loc,val,l,mid);
	else Fix(t[cur].r,t[x].r,loc,val,mid+1,r);
}
inline int Query(int cur,int loc,int l,int r)
{
	int mid=(l+r)>>1;if(l==r)return t[cur].val;
	if(loc<=mid)return Query(t[cur].l,loc,l,mid);
	return Query(t[cur].r,loc,mid+1,r);
}