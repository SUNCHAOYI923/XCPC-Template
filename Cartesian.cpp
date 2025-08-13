//heap-order on values and BST-order on keys
stack <int> s;
vector <int> L (n + 1,0),R (n + 1,0);
for (int i = 1;i <= n;++i)
{
    int la = -1;
    while (!s.empty () && a[s.top ()] > a[i]) la = s.top (),s.pop ();
    if (!s.empty ()) R[s.top ()] = i;
    if (la != -1) L[i] = la;
    s.push (i);
}