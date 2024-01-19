#include <iostream>
#include <vector>
std::vector <int> prefix_function(std::string & str) {
    std::vector <int> p(15000);
    for(int i = 0; i < str.size(); i++) {
        p.push_back(0);
    }
    for(int i = 1; i < str.size(); i++) {
        int k = p[i - 1];
        while(k > 0 && str[k] != str[i])
            k = p[k - 1];
        if(str[k] == str[i])
            k += 1;
        p[i] = k;
    }
    return p;
}

int counter = 0;
std::vector <int> equal(std::string & subsrr, std::string & str) {
    int count = 0;
    std::vector <int> p(500000);
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == subsrr[0])count++;
        else count = 0;
        if(count == subsrr.size()) {
            p[counter++] = i - subsrr.size() + 1;
            count--;
        }
    }
    return p;
}
std::vector <int> kmp_function(std::string & substr, std::string & str) {
    std::vector <int> A(500000);
    int k = 0;
    std::vector <int> phi = prefix_function(substr);
    if(phi[substr.size() - 1] == substr.size() - 1) {
        return equal(substr, str);
    }
    for(int i = 1; i < str.size(); i++) {
        while (str[i] != substr[k + 1] && k > 0) {
            //std::cout<<"k = "<<k<<"\n";
            k = phi[k];
        }
        if(str[i] == substr[k + 1]) {
            k = k + 1;
        }
        if(k == substr.size() - 1) {
            A[counter++] = i - substr.size() + 1;
            k = phi[k];
        }
    }
    return A;
}

int main() {
    std::string s,T;
    std::cin>>s>>T;

    std::vector <int> p = kmp_function(s, T);
    /*std::vector <int>p = prefix_function(s);
    for(int i = 0; i < s.size(); i++) {
        std::cout<<p[i]<<" ";
    }*/
    if(counter != 0)
        std::cout<<p[0];
    else
        std::cout<<-1;
    for(int i = 1; i < counter; i++)
        std::cout<<","<<p[i];
    return 0;
}
