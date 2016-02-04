//
//  mybacktrack.h
//  BackTrack
//
//  Created by Saeid on 11/25/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#ifndef mybacktrack_h
#define mybacktrack_h
#include <cmath>

/**************************(TIP: to get the path must start at s and follow the largest number arround your current position)*****************************/

struct POSITION {
    signed int x;
    signed int y;
}current;

///////////////////////////////////////position stack
class posstack {
    struct linkedlist {
        POSITION data;
        linkedlist *next;
    };
    
    linkedlist *top;
    int size;
    
public:
    posstack() {
        top = NULL;
        size = 0;
    }
    ~posstack() {
        linkedlist *temp = top;
        
        for (int i = 0; i < size; i++) {
            temp = temp -> next;
            delete top;
            top = temp;
        }
    }
    void push(POSITION);
    POSITION pop(void);
    POSITION show(void);
    
}stack;

void posstack::push(POSITION n) {
    linkedlist *New = new linkedlist;
    New -> data = n;
    New -> next = top;
    top = New;
    size++;
}

POSITION posstack::pop(void) {
    if (size) {
        POSITION data = top -> data;
        linkedlist *temp = top;
        top = top -> next;
        delete temp;
        size--;
        return data;
    }
    POSITION negone;
    negone.x = -1;
    negone.y = -1;
    return negone;
}

POSITION posstack::show(void) {
    if (size)
        return top -> data;
    POSITION negone;
    negone.x = -1;
    negone.y = -1;
    return negone;
}


///////////////////////////////////////int stack
class intstack {
public:
    struct linkedlist {
        signed int data;
        linkedlist *next;
        linkedlist *prev;
    };
    
    linkedlist *top, *bottom;
    int size;
    

    intstack() {
        top = NULL;
        bottom = NULL;
        size = 0;
    }
    void push(signed int);
    signed int pop(void);
    signed int show(void);
    void equals(intstack);
    void destroy(void);    ///remember to destroy when done!!!
};

void intstack::push(signed int n) {
    linkedlist *New = new linkedlist;
    New -> data = n;
    New -> next = top;
    if (top) top -> prev = New;
    if (top == NULL) bottom = New;
    top = New;
    top -> prev = NULL;
    size++;
}

signed int intstack::pop(void) {
    if (size) {
        int data = top -> data;
        linkedlist *temp = top;
        top = top -> next;
        top -> prev = NULL;
        delete temp;
        size--;
        return data;
    }
    bottom = NULL;
    return -1;
}

signed int intstack::show(void) {
    if (size)
        return top -> data;
    return -1;
}

void intstack::equals(intstack x) {
    if (size) {
        linkedlist *temp = top;
        
        for (int i = 0; i < size; i++) {
            temp = temp -> next;
            delete top;
            top = temp;
        }
        size = 0;
    }
    
    linkedlist *temp;
    temp = x.bottom;
    for (int i = 0; i < x.size; i++) {
        push(temp -> data);
        temp = temp -> prev;
    }
}

void intstack::destroy() {
    linkedlist *temp = top;
    
    for (int i = 0; i < size; i++) {
        temp = temp -> next;
        delete top;
        top = temp;
    }
}

////////////////////////////////////////////The AI Map Place Holders

class PATH_HOLDER {
public:
    struct linkedlist {
        int data;
        linkedlist *next;
    };
    
    linkedlist *first;
    
    PATH_HOLDER() {
        first = NULL;
    }
    
    ~PATH_HOLDER() {
        linkedlist *temp;
        temp = first;
        
        for (; temp;) {
            temp = temp -> next;
            delete first;
            first = temp;
        }
    }
    
    signed int search(int n) {
        linkedlist *temp;
        temp = first;
        for (int i = 0; temp; i++) {
            if (temp -> data == n) return i;
            temp = temp -> next;
        }
        return -1;
    }
    
    void add(int n) {
        linkedlist *New = new linkedlist;
        New -> data = n;
        New -> next = NULL;
        if (!first) first = New;
        else {
            linkedlist *temp = first;
            for (; temp -> next;)
                temp = temp -> next;
            temp -> next = New;
        }
        return;
    }
    
    void remove(int k) {
        if (k == 0) {
            linkedlist *temp = first;
            first = first -> next;
            delete temp;
        }
        else {
            linkedlist *temp = first -> next, *tmp = first;
            for (int i = 1; i < k; i++) {
                tmp = temp;
                temp = temp -> next;
                if (!temp) return;
            }
            tmp -> next = temp -> next;
            delete temp;
        }
    }
    
    
}deadends;

struct ROAD {
    int type;
    int length;
    bool direction[4];
    intstack path;
    PATH_HOLDER went;
    
    ROAD() {
        for (int i = 0; i < 4; i++)
            direction[i] = true;
    }
    
};


////////////////////////////////////////The Back Track Function

int surrounding(int** , POSITION, bool*);
int find_dir(POSITION, POSITION, bool*);
int path_holder;

int Quick_BackTrack(int** map, int n, int m, POSITION s, POSITION e) {
    
    //////////////////Recursion Cundition
    if (abs(s.x - e.x) < 2 && abs(s.y - e.y) < 2) return path_holder;
    
    
    
    path_holder = 2;
    posstack stack_inv;
    
    map[s.y][s.x] = -1;
    map[e.y][e.x] = -2;
    
    /////////make direction
    
    /*
        0
    3       1
        2
     */
    
    
    bool direction[4];
    for (int i = 0; i < 4; i++)
        direction[i] = false;
    
    ////////Start The Back Tracking
    current.x = s.x;
    current.y = s.y;
    
    for (int i = surrounding(map, current, &direction[0]); i > -1; i = surrounding(map, current, &direction[0])) {
        system("clear");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                switch (map[i][j]) {
                    case 1:
                        cout << "  ";
                        break;
                        
                    case -2:
                        cout << "E ";
                        break;
                        
                    case -1:
                        cout << "S ";
                        break;
                        
                    case 0:
                        cout << "# ";
                        break;
                        
                    default:
                        cout << ". ";
                        break;
                }
            }
            cout << endl;
        }
        cout << endl;
        usleep(200000);
        
        
        /////dead ends
        if (!i) {
            if (stack.show().x == -1) return 0;
            current = stack.pop();
            /***********************************************************************/
            stack_inv.push(current);
            /*
             * quick and affecient(It is quicker and the path is likely to be shortest)
             * 
             *IMPORTANT: If you use this, the next two "stack_inv.push(current); path_holder++;" commands should be commented!!!!!!!
             *
             */
            /***********************************************************************/
            path_holder++;
        }
        
        
        
        
        /////only one way to go
        else if (i == 1) {
            for (int k = 0; k < 4; k++) {
                if (direction[k]) {
                    switch (k) {
                        case 0:
                            current.y--;
                            break;
                            
                        case 1:
                            current.x++;
                            break;
                            
                        case 2:
                            current.y++;
                            break;
                            
                        case 3:
                            current.x--;
                            break;
                    }
                }
            }
            
            map[current.y][current.x] = path_holder;
        }
        
        
        
        
        /////more than one way
        else {
            stack.push(current);
            
            /***********************************************************************/
            //stack_inv.push(current);
            //path_holder++;
            /*
             * slow(It is slow but the path is the more likely the shortest path)
             *
             *IMPORTANT: If you use this, the previous "stack_inv.push(current);" command should be commented!!!!!!!
             *
             */
            /***********************************************************************/
            
            bool clockwise;
            int dir = find_dir(e, current, &clockwise), ph;
            
            if (clockwise) {
                for (ph = dir; !direction[ph]; ph++)
                    if (ph == 3) ph = -1;
            }
            else {
                for (ph = dir; !direction[ph]; ph--)
                    if (ph == 0) ph = 4;
            }
            
            switch (ph) {
                case 0:
                    current.y--;
                    break;
                    
                case 1:
                    current.x++;
                    break;
                    
                case 2:
                    current.y++;
                    break;
                    
                case 3:
                    current.x--;
                    break;
            }
            map[current.y][current.x] = path_holder;
        }
    }//// end of pathfinder.
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] > 1 && map[i][j] < path_holder) map[i][j] = 1;
            else if (map[i][j] == path_holder || map[i][j] < 0) map[i][j] = -5;
        }
    }
    
    if (stack_inv.show().x == -1) return path_holder;
    return Quick_BackTrack(map, n, m, s, stack_inv.pop());
}

///////////////////////////////////////////////////////////////////////Back Track with shortest path
int surrounding2(ROAD** , POSITION, bool*);
struct PATH {
    signed int length;
    intstack path;
    
    PATH() {
        length = -1;
    }
}shortest;
posstack stack_inv1;
bool real = true;

PATH* My_BackTrack(ROAD** map, int n, int m, POSITION s, POSITION e, int p) {
    
    //////////////////Recursion Cundition
    if (s.x == -1) return &shortest;
    
    real = true;
    path_holder = p;
    posstack stack1;
    
    /*
         0
     3       1
         2
     */
    
    ////////Start The Back Tracking
    current.x = s.x;
    current.y = s.y;
    
    if (map[current.y][current.x].type >=1) {
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((map[i][j].type > map[current.y][current.x].type && deadends.search(map[i][j].type) == -1) || map[i][j].type == p) map[i][j].type = 1;
            }
        }
    }
    
    for (int i = surrounding2(map, current, &map[current.y][current.x].direction[0]); i > -1; i = surrounding2(map, current, &map[current.y][current.x].direction[0])) {
        system("clear");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                switch (map[i][j].type) {
                    case 1:
                        cout << "  ";
                        break;
                        
                    case -2:
                        cout << "E ";
                        break;
                        
                    case -1:
                        cout << "S ";
                        break;
                        
                    case 0:
                        cout << "# ";
                        break;
                        
                    default:
                        cout << ". ";
                        break;
                }
            }
            cout << endl;
        }
        cout << endl;
        usleep(200000);
        
        //////cancel out paths taken
        if (path_holder == p) {
            for (int h = 0; h < 4; h++) {
                if (map[current.y][current.x].went.search(h) != -1 && map[current.y][current.x].direction[h]) {
                    map[current.y][current.x].direction[h] = false;
                    i--;
                }
            }
            path_holder++;
        }
        
        
        /////dead ends
        if (!i) {
            if ((map[current.y - 1][current.x].type == 0 || map[current.y][current.x].type == map[current.y - 1][current.x].type) &&
                (map[current.y][current.x - 1].type == 0 || map[current.y][current.x].type == map[current.y][current.x - 1].type) &&
                (map[current.y + 1][current.x].type == 0 || map[current.y][current.x].type == map[current.y + 1][current.x].type) &&
                (map[current.y][current.x + 1].type == 0 || map[current.y][current.x].type == map[current.y][current.x + 1].type))
                deadends.add(path_holder);
            if (stack1.show().x == -1) {
                real = false;
                break;
            }
            current = stack1.pop();
            stack_inv1.pop();
            path_holder++;
        }
        
        
        
        
        /////only one way to go
        else if (i == 1) {
            for (int k = 0; k < 4; k++) {
                if (map[current.y][current.x].direction[k]) {
                    switch (k) {
                        case 0:
                            map[current.y][current.x].went.add(0);
                            current.y--;
                            map[current.y][current.x].path.equals(map[current.y + 1][current.x].path);
                            map[current.y][current.x].path.push(0);
                            map[current.y][current.x].length = map[current.y + 1][current.x].length + 1;
                            break;
                            
                        case 1:
                            map[current.y][current.x].went.add(1);
                            current.x++;
                            map[current.y][current.x].path.equals(map[current.y][current.x - 1].path);
                            map[current.y][current.x].path.push(1);
                            map[current.y][current.x].length = map[current.y][current.x - 1].length + 1;
                            break;
                            
                        case 2:
                            map[current.y][current.x].went.add(2);
                            current.y++;
                            map[current.y][current.x].path.equals(map[current.y - 1][current.x].path);
                            map[current.y][current.x].path.push(2);
                            map[current.y][current.x].length = map[current.y - 1][current.x].length + 1;
                            break;
                            
                        case 3:
                            map[current.y][current.x].went.add(3);
                            current.x--;
                            map[current.y][current.x].path.equals(map[current.y][current.x + 1].path);
                            map[current.y][current.x].path.push(3);
                            map[current.y][current.x].length = map[current.y][current.x + 1].length + 1;
                            break;
                    }
                    break;
                }
            }
            if (map[current.y][current.x].type == 1) map[current.y][current.x].type = path_holder;
            
        }
        
        
        
        
        /////more than one way
        else {
            stack_inv1.push(current);
            stack1.push(current);
            
            bool clockwise;
            int dir = find_dir(e, current, &clockwise), ph;
            
            if (clockwise) {
                for (ph = dir; !map[current.y][current.x].direction[ph]; ph++)
                    if (ph == 3) ph = -1;
            }
            else {
                for (ph = dir; !map[current.y][current.x].direction[ph]; ph--)
                    if (ph == 0) ph = 4;
            }
            
            switch (ph) {
                case 0:
                    map[current.y][current.x].went.add(0);
                    current.y--;
                    map[current.y][current.x].path.equals(map[current.y + 1][current.x].path);
                    map[current.y][current.x].path.push(0);
                    map[current.y][current.x].length = map[current.y + 1][current.x].length + 1;
                    break;
                    
                case 1:
                    map[current.y][current.x].went.add(1);
                    current.x++;
                    map[current.y][current.x].path.equals(map[current.y][current.x - 1].path);
                    map[current.y][current.x].path.push(1);
                    map[current.y][current.x].length = map[current.y][current.x - 1].length + 1;
                    break;
                    
                case 2:
                    map[current.y][current.x].went.add(2);
                    current.y++;
                    map[current.y][current.x].path.equals(map[current.y - 1][current.x].path);
                    map[current.y][current.x].path.push(2);
                    map[current.y][current.x].length = map[current.y - 1][current.x].length + 1;
                    break;
                    
                case 3:
                    map[current.y][current.x].went.add(3);
                    current.x--;
                    map[current.y][current.x].path.equals(map[current.y][current.x + 1].path);
                    map[current.y][current.x].path.push(3);
                    map[current.y][current.x].length = map[current.y][current.x + 1].length + 1;
                    break;
            }
            path_holder++;
            if (map[current.y][current.x].type == 1) map[current.y][current.x].type = path_holder;
        }
    }//// end of pathfinder.
        
    if ((map[current.y][current.x].length < shortest.length || shortest.length == -1) && real) {
        shortest.length = map[current.y][current.x].length;
        shortest.path.equals(map[current.y][current.x].path);
    }
    
    return My_BackTrack(map, n, m, stack_inv1.pop(), e, path_holder);
}






int surrounding(int** map, POSITION current, bool* direction) {
    int n = 0;
    
    ////Top
    if (map[current.y - 1][current.x] == 1) {
        direction[0] = true;
        n++;
    }
    else if (map[current.y - 1][current.x] == -2) return -1;
    else direction[0] = false;
    
    ////Right
    if (map[current.y][current.x + 1] == 1) {
        direction[1] = true;
        n++;
    }
    else if (map[current.y][current.x + 1] == -2) return -1;
    else direction[1] = false;
    
    ////Bottom
    if (map[current.y + 1][current.x] == 1) {
        direction[2] = true;
        n++;
    }
    else if (map[current.y + 1][current.x] == -2) return -1;
    else direction[2] = false;
    
    ////Left
    if (map[current.y][current.x - 1] == 1) {
        direction[3] = true;
        n++;
    }
    else if (map[current.y][current.x - 1] == -2) return -1;
    else direction[3] = false;
        
    return n;
}

int surrounding2(ROAD** map, POSITION current, bool* direction) {
    int n = 0;
    
    ////Top
    if (map[current.y - 1][current.x].type == 1) {
        map[current.y][current.x].direction[0] = true;
        n++;
    }
    else if (map[current.y - 1][current.x].type == -2) return -1;
    else map[current.y][current.x].direction[0] = false;
    
    ////Right
    if (map[current.y][current.x + 1].type == 1) {
        map[current.y][current.x].direction[1] = true;
        n++;
    }
    else if (map[current.y][current.x + 1].type == -2) return -1;
    else map[current.y][current.x].direction[1] = false;
    
    ////Bottom
    if (map[current.y + 1][current.x].type == 1) {
        map[current.y][current.x].direction[2] = true;
        n++;
    }
    else if (map[current.y + 1][current.x].type == -2) return -1;
    else map[current.y][current.x].direction[2] = false;
    
    ////Left
    if (map[current.y][current.x - 1].type == 1) {
        map[current.y][current.x].direction[3] = true;
        n++;
    }
    else if (map[current.y][current.x - 1].type == -2) return -1;
    else map[current.y][current.x].direction[3] = false;
    
    return n;
}

int find_dir(POSITION E, POSITION curr, bool *clk) {
    int xdif = E.x - curr.x, ydif = E.y - curr.y;
    
    if (xdif >= 0 && ydif >= 0) {
        if (abs(xdif) >= abs(ydif)) { *clk = true;return 1;}
        else { *clk = false;return 2;}
    }
    else if (xdif <= 0 && ydif <= 0) {
        if (abs(xdif) >= abs(ydif)) { *clk = true;return 3;}
        else { *clk = false;return 0;}
    }
    else if (xdif <= 0 && ydif >= 0) {
        if (abs(xdif) >= abs(ydif)) { *clk = false;return 3;}
        else { *clk = true;return 2;}
    }
    else {
        if (abs(xdif) >= abs(ydif)) { *clk = false;return 1;}
        else { *clk = true;return 0;}
    }
}




#endif /* mybacktrack_h */
