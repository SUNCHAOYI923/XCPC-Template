template <typename T>
class FWT
{
    public:
    const int P = 998244353;
    const ll inv_2 = 499122177;//500000004 for 1e9 + 7
    private:
    void Or (vector <T> &F,int op = 1)
    {
        int n = F.size ();
        for (int i = 2;i <= n;i <<= 1)
        {
            int o = i >> 1;
            for (int j = 0;j < n;j += i)
                for (int k = 0;k < o;++k) F[j + k + o] = (F[j + k + o] + F[j + k] * op % P) % P;
        }
    }
    void And (vector <T> &F,int op = 1)
    {
        int n = F.size ();
        for (int i = 2;i <= n;i <<= 1)
        {
            int o = i >> 1;
            for (int j = 0;j < n;j += i)
                for (int k = 0;k < o;++k) F[j + k] = (F[j + k] + F[j + k + o] * op % P) % P;
        }
    }
    void Xor (vector <T> &F,int op = 1)
    {
        int n = F.size ();
        for (int i = 2;i <= n;i <<= 1)
        {
            int o = i >> 1;
            for (int j = 0;j < n;j += i)
            {
                for (int k = 0;k < o;++k)
                {
                    F[j + k] = (F[j + k] + F[j + k + o]) % P;
                    F[j + k + o] = (F[j + k] - 2 * F[j + k + o] % P + P) % P;
                    F[j + k] = F[j + k] * op % P;
                    F[j + k + o] = F[j + k + o] * op % P;
                }
            }
        }
    }
    vector <T> mul (vector <T> A,vector <T> B)
    {
        int n = A.size ();
        vector <T> C (n);
        for (int i = 0;i < n;++i) C[i] = A[i] * B[i] % P;
        return C;
    }
    public : 
    FWT () {}
    vector <T> calc_Or (vector <T> A,vector <T> B)
    {
        Or (A);Or (B);
        auto C = mul (A,B);
        Or (C,P - 1);
        return C;
    }
    vector <T> calc_And (vector <T> A,vector <T> B)
    {
        And (A);And (B);
        auto C = mul (A,B);
        And (C,P - 1);
        return C;
    }
    vector <T> calc_Xor (vector <T> A,vector <T> B)
    {
        Xor (A);Xor (B);
        auto C = mul (A,B);
        Xor (C,inv_2);
        return C;
    }
};