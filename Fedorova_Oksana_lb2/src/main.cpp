#include <iostream>
#include <vector>
#include <map>
#include "math.h"
struct Node{
    char key = '0';
    double g = -1;
    double f = -1;
    bool tentative_is_better = false;
    std::map < Node *, double> next;
};

double h_x(Node * curr, char end) {
    return fabs((double)((int)(curr->key) - (int)end));
}
void get_table(std::map <char, Node * > & list){
    std::string asstr, aestr;
    std::string sym;
    for(int i = 0; i < 26; i++) {
        Node * new_node = new Node;
        new_node->key = (char )((int)('a') + i);
        list.insert({new_node->key, new_node});
    }
    double cst;
    while(std::cin) {
        std::cin>>asstr>>aestr>>cst;
        (list[asstr[0]]->next).insert({list[aestr[0]], cst});
    }
}

Node * min_f(std::map<char, Node *> map, char end) {
    double min = -1;
    Node * new_key;
    for(std::pair <char, Node *> i : map) {
        if(i.second->g != -1 && (min == -1 || min > i.second->f ||
            min == i.second->f && h_x(i.second, end) <= h_x(new_key, end))){
            min= i.second->f;
            new_key = i.second;
        }
    }
    return new_key;
}

void print_map(std::map <char, Node *> table) {
    for(auto i : table) {
        std::cout<<i.first<<" : " << i.second->key<<" cost " << i.second->g<<std::endl;
    }
}
void print_path(std::map <char, Node *> from_set, char start, char end) {
    std::string ans;
    ans += end;
    char curr = end;
    while(curr != start) {
        curr = from_set.find(curr)->second->key;
        ans += curr;
    }
    for(int i = ans.size() - 1; i >= 0; i--) {
        std::cout<<ans[i];
    }
}
void a_star(char start, char end, std::map <char, Node *> & table) {
    std::map <char, Node *> closed_set;
    std::map <char, Node *> open_set;
    std::map <char, Node *> from_set;
    open_set.insert({start, table.find(start)->second});
    table.find(start)->second->g = 0;
    table.find(start)->second->f = 0 + h_x(table.find(start)->second, end);
    while (!open_set.empty()) {
        Node * curr;
        curr = min_f(open_set, end);
        if(curr->key == end) {
            print_path(from_set, start, end);
            return;
        }
        open_set.erase(curr->key);
        closed_set.insert({curr->key, curr});
        for(auto neighbour  : curr->next) {
            double tentative_to_score = curr->g + curr->next[neighbour.first];
            if(closed_set.find(neighbour.first->key) != closed_set.end()) {//отличие от псевдокода
                if(tentative_to_score <= neighbour.first->g || neighbour.first->g == -1)
                    neighbour.first->tentative_is_better = true;
                else
                    neighbour.first->tentative_is_better = false;
            }
            if(open_set.find(neighbour.first->key) == open_set.end() &&
                closed_set.find(neighbour.first->key) == closed_set.end()) {
                open_set.insert({neighbour.first->key ,neighbour.first});//отличие от псевдокода, на сайте они проверяют лишь на наличие в open_set а надо еще и в close_set
                neighbour.first->tentative_is_better = true;
            } else {
                if (tentative_to_score < neighbour.first->g || neighbour.first->g == -1) {
                    neighbour.first->tentative_is_better = true;
                } else {
                    neighbour.first->tentative_is_better = false;
                }
            }
            if(neighbour.first->tentative_is_better) {
                from_set[neighbour.first->key] = curr;
                neighbour.first->g = tentative_to_score;
                neighbour.first->f = tentative_to_score + h_x(neighbour.first, end);
                neighbour.first->tentative_is_better = false;
            }
        }
    }
    print_path(from_set, start, end);
}


int main() {
    std::string s_str, e_str;
    std::cin>>s_str>>e_str;
    char s = s_str[0], e = e_str[0];
    std::map <char, Node *> vec;
    get_table(vec);
    a_star(s, e, vec);
    return 0;
}
