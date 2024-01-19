#include <cassert>
#include <algorithm>
#include <unordered_map>
#include "modules/a_star.hpp"
#include <fstream>
#include <SFML/Graphics.hpp>

void read_file(std::string & s_str, std::string & e_str, char & start, char & end, std::map <char, Node *> & table, std::string filename) {
    table.clear();
    std::ifstream f;
    f.open(filename);
    f>>s_str>>e_str;
    start = s_str[0];
    end = e_str[0];
    get_table(table, f);
    f.close();
}

void get_pick(std::map<char, Node * > & table, std::map <char, std::pair <double, double>> & new_map, double R, double center) {
    int counter = 0;
    for(auto i : table) {
        if(i.second->in_list) {
            new_map.insert({i.first, {0,0}});
            counter++;
        }
    }
    double phi = 0;
    //double R = 200;
    for(auto i : new_map) {
        double x = R * cos(phi) + center;
        double y = R * sin(phi) + center;
        new_map[i.first] = {x, y};
        phi += 2 * 3.14159 / counter;
        //std::cout<<x<<" "<<y<<" "<<phi;
    }
}

void get_lines(std::map <char, Node *> & table, std::map <std::pair<char, char>, double> & lines) {
    for(auto curr : table) {
        if(curr.second->in_list)
            for(auto neighbour : curr.second->next) {
                lines.insert({{curr.first, neighbour.first->key}, neighbour.second});
            }
    }
}
void get_strel(sf::VertexArray & my_lines, double from_x, double from_y, double to_x, double to_y, int & counter) {
    double a_x = (from_x * 1 + to_x * 9)/10;
    double a_y = (from_y * 1 + to_y * 9)/10;
    double length = sqrt((from_x - to_x) * (from_x - to_x) + (from_y - to_y) * (from_y - to_y));
    length /= 8;
    std::pair <double, double> l_vector = {(to_x - from_x) / length, (to_y - to_x)/length};
    sf::Vector2f first_sim_dot(a_x + l_vector.second * (-1), a_y + l_vector.first);
    sf::Vector2f second_sim_dot(a_x + l_vector.second, a_y + l_vector.first * (-1));
    my_lines[counter].position = sf::Vector2f(to_x, to_y);
    my_lines[counter + 1].position = first_sim_dot;
    my_lines[counter + 2].position = sf::Vector2f(to_x, to_y);
    my_lines[counter + 3].position = second_sim_dot;
    counter += 4;
}

void get_text(std::vector <sf::Text> & text, std::map <std::pair<char, char>, double> & lines, std::map <char, std::pair<double, double>> & dots) {
    for(auto i : lines) {
        sf::Text cost;
        cost.setFillColor(sf::Color::Green);
        cost.setString(std::to_string(i.second));
        char a = i.first.first, b = i.first.second;
        double x = (dots[a].first + dots[b].first)/2;
        double y = (dots[b].second + dots[a].second)/2;
        cost.setPosition(x,y);
        text.push_back(cost);
    }
    for(auto i : dots) {
        sf::Text dot;
        sf::Text cost;
        dot.setFillColor(sf::Color::Cyan);
        dot.setString(i.first);
        dot.setPosition(i.second.first, i.second.second);
        text.push_back(dot);
    }
    std::cout<<text.size()<<std::endl;
}

void get_circles(std::vector <sf::CircleShape> & circles, std::map<char, std::pair <double, double>> & dots) {
    for(auto circ : dots) {
        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(circ.second.first - 10, circ.second.second - 10);
        circles.push_back(shape);
    }
}
void get_lines(sf::VertexArray & my_lines, std::map <std::pair<char, char>, double> &lines,
               std::map<char, std::pair <double, double>> & dots, sf::VertexArray & my_strels ) {
    int i = 0;
    int counter_for_str = 0;
    for(auto pairs : lines) {
        char from = pairs.first.first;
        char to = pairs.first.second;
        my_lines[i].position = sf::Vector2f(dots[from].first, dots[from].second);
        my_lines[i+1].position = sf::Vector2f(dots[to].first, dots[to].second);
        i+=2;
        get_strel(my_strels, dots[from].first, dots[from].second, dots[to].first, dots[to].second, counter_for_str);
    }
}
void drow(std::map<char, std::pair <double, double>> & dots, std::map <std::pair<char, char>, double> &lines) {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::VertexArray my_lines(sf::Lines, lines.size() * 2);
    sf::VertexArray my_strels(sf::Lines, lines.size() * 4);
    std::vector <sf::CircleShape> circles;
    std::vector <sf::Text> text;
    get_text(text, lines, dots);
    get_circles(circles, dots);
    get_lines(my_lines, lines, dots, my_strels);
    sf::Font font;
    font.loadFromFile("calibri_bold.ttf");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for(auto i : circles) {
            window.draw(i);
        }
        for(auto i : text) {
            i.setCharacterSize(18);
            i.setFont(font);
            window.draw(i);
        }
        window.draw(my_strels);
        window.draw(my_lines);
        window.display();
    }
}

void start() {
    std::string s_str, e_str;
    char start, end;
    std::map <char, Node *> table;
    read_file(s_str, e_str, start, end, table, "modules/tests/input2.txt");
    std::map <char, std::pair <double, double>> dots;
    std::map <std::pair <char, char>, double> lines;
    get_lines(table, lines);
    get_pick(table, dots, 200, 250);
    for(auto i:dots) {
        std::cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<std::endl;
    }
    for(auto i: lines) {
        std::cout<<i.second<<" "<<i.first.first<<" "<<i.first.second<<std::endl;
    }
    drow(dots, lines);
}

int main() {
    start();
    return 0;
}
