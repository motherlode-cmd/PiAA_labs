#include <iostream>
#include <vector>
std::vector <int> prefix_function(std::string & str) {
    std::vector <int> arr_pref(str.size());
    for(int i = 0; i < arr_pref.size(); i++) {
        arr_pref[i] = 0;
    }
    int k = 0;
    for (int i = 1; i < str.length(); i++){
        k = arr_pref[i-1];
        while (k > 0 && str[i] != str[k]){
            k = arr_pref[k-1];
        }
        if (str[i] == str[k]){
            k++;
        }
        arr_pref[i] = k;
        /*for (int i = 0; i < str.length(); i++){
            std::cout << arr_pref[i] << ' ';
        }
        std::cout << '\n';*/
    }
    return arr_pref;
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
int KMP(std::string str, std::string text){
    std::vector <int> phi = prefix_function(str);
    std::string res;
    int j = 0;
    int a = 0;
    int temp = 0;
    for(int i = 0; i < text.length(); i++){
        if (str[j] == text[i]){
            j++;
        }
        else if (j > 0){
            i--;
            j = phi[j-1];
        }

        if (j == str.length()){
            a = text.length() - i - 1;
            if (a == str.length()){
                return 0;
            }
            else{
                return a;
            }
            temp = 1;
            break;

        }
    }
    if (temp == 0){
        return - 1;
    }
}
std::vector <int> kmp_function(std::string & substr, std::string & str) {
    std::vector <int> A;
    int k = 0;
    std::vector <int> phi = prefix_function(substr);
    if(phi[substr.size() - 1] == substr.size() - 1) {
        //return equal(substr, str);
    }
    for(int i = 1; i < str.size(); i++) {
        while (str[i] != substr[k + 1] && k > 0) {
            if(k == phi[k] && str[i] != substr[k + 1])
                break;
            k = phi[k];
        }
        if(str[i] == substr[k + 1]) {
            k = k + 1;
        }
        if(k == substr.size() - 1 && substr[0] == str[i - substr.size() + 1]) {
            A.push_back(i - substr.size() + 1);
            k = phi[k];
        }
    }
    return A;
}

int find_shift(std::string & str, std::string & substr) {
    std::vector <int> pfi = prefix_function(substr);
    if(str.length() != substr.length()) return -1;
    if (str == substr){
        return 0;
    }
    str += str;
    return KMP(substr, str);
    //std::vector<int> res = kmp_function(substr, str);
    //return res.empty() ? -1 : res[0];
    //std::cout << res[0] << '\n';
    /*
    int i = 0, j = 0;
    while (i < str.length() && j < substr.length()) {
        if(str[i] == substr[j]) {
            i++;
            j++;
            if(j == substr.length()) return  i - j;
        } else {
            if(j > 0) j = pfi[j--];
            else i++;
        }
    }
    return -1;
    */
}

int main() {
    std::string s,T;
    std::cin>>s>>T;
    std::cout<<find_shift(s, T);
    return 0;
}
