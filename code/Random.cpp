int rd(int a, int b)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution <int> dist(a, b);
    return dist(gen);
}