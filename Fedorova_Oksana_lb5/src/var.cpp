#include <iostream>
#include "vector"
#include "map"
#include "string"
#include <cstring>
#include "algorithm"
const int k = 127-33;
char start = (char)33;
struct Vertex {
    int next_vertex[k];
    int pat_num;
    bool terminal = false;
    int suffix_link;
    int auto_move[k];
    int par; //auto_move - запоминание перехода автомата, par - вершина-отец в дереве
    char symb; //символ на ребре от par к этой вершине
    int suff_flink;
};

std::vector <Vertex> bohr;
std::vector <std::string> pattern;

Vertex make_bohr_vertex(int p, char c){
    Vertex v;
    //(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
    memset(v.next_vertex, 255, sizeof(v.next_vertex));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.terminal = false;
    v.suffix_link = -1;
    v.suff_flink = -1;
    v.par = p;
    v.symb = c;
    return v;
}


void bohr_ini(){
    //добавляем единственную вершину - корень
    bohr.push_back(make_bohr_vertex(0, '$'));
}


void add_str_to_bohr(std::string s){
    int num=0; //начинаем с корня
    for (int i=0; i<s.length(); i++){
        char ch = s[i]-start; //получаем номер в алфавите
        if (bohr[num].next_vertex[ch]==-1){ //-1 - признак отсутствия ребра
            bohr.push_back(make_bohr_vertex(num, ch));
            bohr[num].next_vertex[ch] = bohr.size()-1;
        }
        num=bohr[num].next_vertex[ch];
    }
    bohr[num].terminal = true;
    pattern.push_back(s);
    bohr[num].pat_num = pattern.size()-1;
}

bool is_string_in_bohr(std::string s){
    int num=0;
    for (int i=0; i < s.length(); i++){
        char ch = s[i]-start;
        if (bohr[num].next_vertex[ch]==-1){
            return false;
        }
        num = bohr[num].next_vertex[ch];
    }
    return true;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v){
    if (bohr[v].suffix_link==-1) //если еще не считали
        if (v==0 || bohr[v].par==0) //если v - корень или предок v - корень
            bohr[v].suffix_link=0;
        else
            bohr[v].suffix_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suffix_link;
}

int get_suff_flink(int v){
    if (bohr[v].suff_flink==-1){
        int u = get_suff_link(v);
        if (u==0) //либо v - корень, либо суф. ссылка v указывает на корень
            bohr[v].suff_flink=0;
        else
            bohr[v].suff_flink=(bohr[u].terminal)?u:get_suff_flink(u);
    }
    return bohr[v].suff_flink;
}

int get_auto_move(int v, char ch){
    if (bohr[v].auto_move[ch]==-1)
        if (bohr[v].next_vertex[ch]!=-1)
            bohr[v].auto_move[ch]=bohr[v].next_vertex[ch];
        else
        if (v==0)
            bohr[v].auto_move[ch]=0;
        else
            bohr[v].auto_move[ch]=get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}
std::vector <std::pair <int, int>> ans;
void check(int v,int i){
    for(int u=v;u!=0;u=get_suff_flink(u)){
        if (bohr[u].terminal)
            ans.push_back(std::pair<int, int> (i-pattern[bohr[u].pat_num].length()+1, bohr[u].pat_num + 1));
        //std::cout<<i-pattern[bohr[u].pat_num].length()+1<<" "<<bohr[u].pat_num + 1<<std::endl;
    }
}

void find_all_pos(std::string s){
    int u=0;
    for(int i=0;i<s.length();i++){
        u=get_auto_move(u,s[i]-start);
        check(u,i+1);
    }
}
bool cmp(std::pair <int, int> & p1, std::pair <int, int> & p2) {
    if(p1.first < p2.first) return true;
    if(p1.first == p2.first && p1.second < p2.second) return true;
    return false;
}

void create_bohr(std::string tmp, int pos, char jock) {
    if(pos == tmp.length()) add_str_to_bohr(tmp);
    else if(tmp[pos] != jock) create_bohr(tmp, pos+1, jock);
    else if(tmp[pos] == jock) {
        for(int i = 0; i < 127-start; i++) {
            if(start + i != jock) {
                tmp[pos] = char(start + i);
                create_bohr(tmp, pos + 1, jock);
            }
        }
    }
}

int main() {
    std::string txt;
    std::cin>>txt;
    bohr_ini();
    std::string tmp;
    char jock;
    std::cin>>tmp>>jock;
    create_bohr(tmp, 0, jock);
    find_all_pos(txt);
    for(auto i : ans)
        std::cout<<i.first<<std::endl;
    return 0;
}