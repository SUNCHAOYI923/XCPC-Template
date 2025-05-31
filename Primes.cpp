class Prime
{
    int mx;
    vector <int> p,phi,mu;
    void pre ()
    {
        vector <int> fl (mx + 1,0);
        phi[1] = mu[1] = 1;
        for (int i = 2;i <= mx;++i)
        {
            if (!fl[i]) p.push_back (i),phi[i] = i - 1,mu[i] = -1;
            for (auto v : p)
            {
                if (i * v > mx) break;
                fl[i * v] = 1;
                if (i % v == 0) {phi[i * v] = phi[i] * v,mu[i * v] = 0;break;}
                phi[i * v] = phi[i] * (v - 1);mu[i * v] = -mu[i];
            }
        }
    }
    public : 
    Prime (int mx) : mx (mx),phi (mx + 1,0),mu (mx + 1,0) {pre ();}
    auto get_prime () {return p;}
    auto get_phi () {return phi;}
    auto get_mu () {return mu;}
};