#include <bits/stdc++.h>
#include "str.hpp"
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Minimal runner to satisfy OJ build; no specific I/O required
    str a; // empty
    str b('x');
    str c("ab");
    str d = c;
    d[0] = 'A';
    auto e = str(", ").join(vector<str>{str('1'), str('2'), str('3')});
    auto f = e.slice(0, e.len());

    cout << (int)b[0] << " " << d.len() << " " << e.len() << " " << f.len() << "\n";
    return 0;
}
