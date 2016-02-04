//
//  main.cpp
//  BackTrack
//
//  Created by Saeid on 11/25/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "mybacktrack.h"

int main(void) {
    
    /***********************(important: Do not put spaces between the maze characters unless its a pathh way!)**************************/
    
    ifstream in("input.txt");
    
    if (in) { // Verify that the file was open successfully
        
        
        
        ///*
        //////////////////////////////////////////////////////////////the shortest way
        POSITION S, E;
        
        string tmp; // Construct a string to hold the line
        getline(in, tmp);
        
        stringstream stream(tmp);
        int n,m;
        
        if(!stream) {
            in.close();
            return 1;
        }
        stream >> n;
        
        if(!stream) {
            in.close();
            return 1;
        }
        stream >> m;
        
        
        ROAD** map = new ROAD*[n];
        for(int i = 0; i < n; i++)
            map[i] = new ROAD[m];
        
        
        for (int i = 0; i < n; i++) {
            if (getline(in, tmp)) {
                for (int j = 0; j < m; j++) {
                    switch (tmp[j]) {
                        case 'E':
                            map[i][j].type = -2;
                            E.x = j;
                            E.y = i;
                            break;
                            
                        case 'S':
                            map[i][j].type = -1;
                            S.x = j;
                            S.y = i;
                            break;
                            
                        case '#':
                            map[i][j].type = 0;
                            break;
                            
                        case ' ':
                            map[i][j].type = 1;
                            break;
                        default:
                            cout << "Wrong maze characters!" << endl;
                            cout << "Wall:        #" << endl;
                            cout << "Start Point: S" << endl;
                            cout << "End Point:   E" << endl;
                            cout << "Path Ways:  (space)" << endl;
                            in.close();
                            return 2;
                    }
                }
            }
            else {
                in.close();
                return 1;
            }
        }
        
        
        /////////////Safe Check
        if ( S.x == 0 || S.y == 0 || E.x == 0 || E.y == 0 ) {
            in.close();
            cout << endl << "S & E can't be on the borders!" << endl;
            for (int i = 0; i < n; i++)
                delete map[i];
            delete map;
            return 2;
        }
        
        
        ////////////Calculate answer
        map[S.y][S.x].length = 0;
        PATH *found = My_BackTrack(map, n, m, S, E, 2);
        
        cout << endl << "Your Answer Is:" << endl;
        system("clear");
        if (found -> length != -1) {
            
            int len = found -> path.size;
            intstack way;
            way.equals(found -> path);
            POSITION go;
            go.x = S.x;
            go.y = S.y;
            
            for (int i = 0; i < len; i++) {
                switch (way.bottom -> data) {
                    case 0:
                        go.y--;
                        break;
                        
                    case 1:
                        go.x++;
                        break;
                        
                    case 2:
                        go.y++;
                        break;
                        
                    case 3:
                        go.x--;
                        break;
                }
                map[go.y][go.x].type = -5;
                way.bottom = way.bottom -> prev;

            }
            
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (map[i][j].type > 1) map[i][j].type = 1;
                }
            }
            
            map[S.y][S.x].type = -1;
            map[E.y][E.x].type = -2;
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    switch (map[i][j].type) {
                        case -5:
                            cout << ". ";
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
                            
                        case 1:
                            cout << "  ";
                            break;
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
        else
            cout << "The maze doesn't have a solution" << endl;
        
        
        in.close();
        delete map;
        return 0;
         
        //*/
        
        
        
        
        
        
        
        
        
        
        
        
        
        /*
        
        /////////////////////////////////////////////////////////////////////////////the quick way
        
        
        
        POSITION S, E;
        
        string tmp; // Construct a string to hold the line
        getline(in, tmp);
        
        stringstream stream(tmp);
        int n,m;
        
        if(!stream) {
            in.close();
            return 1;
        }
        stream >> n;
        
        if(!stream) {
            in.close();
            return 1;
        }
        stream >> m;
        
        
        int** map = new int*[n];
        for(int i = 0; i < n; i++)
            map[i] = new int[m];
        
        
        for (int i = 0; i < n; i++) {
            if (getline(in, tmp)) {
                for (int j = 0; j < m; j++) {
                    switch (tmp[j]) {
                    case 'E':
                        map[i][j] = -2;
                        E.x = j;
                        E.y = i;
                        break;
                        
                    case 'S':
                        map[i][j] = -1;
                        S.x = j;
                        S.y = i;
                        break;
                        
                    case '#':
                        map[i][j] = 0;
                        break;
                        
                    case ' ':
                        map[i][j] = 1;
                        break;
                    default:
                            cout << "Wrong maze characters!" << endl;
                            cout << "Wall:        #" << endl;
                            cout << "Start Point: S" << endl;
                            cout << "End Point:   E" << endl;
                            cout << "Path Ways:  (space)" << endl;
                            in.close();
                            return 2;
                    }
                }
            }
            else {
                in.close();
                return 1;
            }
        }

        
        /////////////Safe Check
        if ( S.x == 0 || S.y == 0 || E.x == 0 || E.y == 0 ) {
            in.close();
            cout << endl << "S & E can't be on the borders!" << endl;
            for (int i = 0; i < n; i++)
                delete map[i];
            delete map;
            return 2;
        }
        
        
        ////////////Calculate answer
        
        int found = Quick_BackTrack(map, n, m, S, E);

        cout << endl << "Your Answer Is:" << endl;
        if (found) {
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (map[i][j] > 1 && map[i][j] < found) map[i][j] = 1;
                    else if (map[i][j] == found || map[i][j] < 0) map[i][j] = -5;
                }
            }
            
            map[S.y][S.x] = -1;
            map[E.y][E.x] = -2;
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    switch (map[i][j]) {
                        case -5:
                            cout << ". ";
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
                            
                        case 1:
                            cout << "  ";
                            break;
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
        else
            cout << "The maze doesn't have a solution" << endl;
        
        
        in.close();
        for (int i = 0; i < n; i++)
            delete map[i];
        delete map;
        return 0;
        */
        
        
    }
    else {
        cerr << "File could not be opened!\n"; // Report error
        cerr << "Error code: " << strerror(errno) << endl; // Get some info as to why
        return 1;
    }
    
}
