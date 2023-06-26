#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



struct pizza {    
    int s, t, r;
};



bool compareRatio(pizza p1, pizza p2) {
    
    double ratio1 = (double) p1.r/p1.t;
    double ratio2 = (double) p2.r/p2.t;
    
    return ratio1 > ratio2;
}



int solve(vector<pizza> &pizzas, int N, int T) {
    
    vector<vector<int> > s;
    int newFlavor = 0, oldFlavor = 0, maxFlavor = 0;
    
    
    
    /* We begin by ordering the pizzas based on their flavor loss to time cost ratio
     * The optimal solution to our problem is achieved by prioritizing 
     * the pizzas with high flavor loss (r) and low cooking time (t), 
     * since leaving then uncooked results in high overall flavor loss
     */
    sort(pizzas.begin(), pizzas.end(), compareRatio);
    
    
    
    /* Then, we apply a Dynamic Programming algorithm 
     * to establish the maximum flavor we can have 
     * with n pizzas and t time, where 
     * 0 <= n <= N and 0 <= t <= T
     */
    
    s.resize(N + 1);
    
    for (int n = 0; n < N + 1; n++) {
        
        s[n].resize(T + 1);
        s[n][0] = 0;
    }
    
    for (int t = 0; t < T + 1; t++)
        s[0][t] = 0;
    
    for (int n = 1; n < N + 1; n++) {
        
        for (int t = 1; t < T + 1; t++) {
            
            oldFlavor = s[n-1][t];            
            s[n][t] = oldFlavor;
            
            if (pizzas[n-1].t <= t) {
                
                newFlavor = pizzas[n-1].s - pizzas[n-1].r*t + s[n-1][t-pizzas[n-1].t];
                
                if (newFlavor > oldFlavor)
                    s[n][t] = newFlavor;
            }
        }
    }
    
    
    
    /* Our solution is the biggest number in the last row,
     * which represents the maximum flavor for N pizzas
     */
    for (int t = 0; t < T + 1; t++) {
        
        if (s[N][t] > maxFlavor)
            maxFlavor = s[N][t];
    }        
    
    return maxFlavor;
}



int main() {

    int N, T;
    cin >> N >> T;

    vector<pizza> pizzas(N);
    for (int i = 0; i < N; ++i)
        cin >> pizzas[i].s >> pizzas[i].t >> pizzas[i].r;

    cout << solve(pizzas, N, T) << endl;
    
    return 0;
}
