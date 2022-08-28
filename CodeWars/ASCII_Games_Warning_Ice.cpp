 //Breadth first search with history kludge
 #include <set>
 #include <map>

 const char START = 'S';
 const char MAZEEND = 'E';
 const char ICE = ' ';
 const char SAND = 'x';
 const char ROCK = '#';

 const int VISITED = -1;
 const int END = -2;
 const int CONTINUE = -3;
 const int SKIP = -4;

 struct History {
   int index;
   bool left;
   bool right;
   bool up;
   bool down;
   History() {
     left = false;
     right = false;
     up = false;
     down = false;
   }
 };


 struct Trip {
   int x;
   int y;
   std::string path;
   int distance;
   std::map<int, History> history;
   Trip() {
     x = SKIP;
     y = SKIP;
     path = "";
     distance = 0;
   }
   Trip(int x, int y, std::string path, int distance) {
     this->x = x;
     this->y = y;
     this->path = path;
     this->distance = distance;
   }
 };

 struct TripKeyCompare {
   bool operator()(const Trip &a, const Trip &b) {
     if (a.path.size() < b.path.size()) {
       return true;
     }
     else if (a.path.size() == b.path.size() && a.distance == b.distance) {
       return (a.path < b.path); //We want to keep unique paths
     }
     else if (a.path.size() == b.path.size()) {
       return (a.distance < b.distance);
     }
     else {
       return false;
     }
   }
 };

 struct V2 {
   int x;
   int y;
 };

 int width(std::string map) {
   return map.find('\n') + 1;
 }

 int height(std::string map) {
   int w = width(map);
   //Add one for the last newline
   return (map.size() + 1) / w;
 }

 int getIndex(V2 pos, V2 wh) {
   return pos.y * wh.x + pos.x;
 }

 V2 getStart(std::string map, V2 wh) {
   for (int y = 0; y < wh.y; y++) {
     for (int x = 0; x < wh.x - 1; x++) {
       if (map[getIndex({ x,y }, wh)] == START)
         return { x, y };
     }
   }
   return { -1, -1 };
 }

 void setHistory(int index, char direction, std::map<int, History> &history) {
   switch (direction) {
   case 'u': history[index].up = true; break;
   case 'd': history[index].down = true; break;
   case 'l': history[index].left = true; break;
   case 'r': history[index].right = true; break;
   }
 }

 Trip performWalk(std::string &map, int x, int y, char direction, int &distance, Trip &pos, V2 wh) {
   int idx = getIndex({ x, y }, wh);

   if (pos.history.count(idx) > 0) {
     if (direction == 'u' && pos.history[idx].up)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'd' && pos.history[idx].down)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'l' && pos.history[idx].left)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'r' && pos.history[idx].right)
       return { VISITED, VISITED, pos.path + direction, distance };
   }

   switch (map[idx]) {
   case ICE:
     setHistory(idx, direction, pos.history);
     return { CONTINUE, CONTINUE, pos.path, ++distance };
   case ROCK:
     if (direction == 'l')
       return { x + 1, y, pos.path + direction, distance };
     else if (direction == 'r')
       return { x - 1, y, pos.path + direction, distance };
     else if (direction == 'u')
       return { x, y + 1, pos.path + direction, distance };
     else if (direction == 'd')
       return { x, y - 1, pos.path + direction, distance };
     break;
   case SAND:
     setHistory(idx, direction, pos.history);
     return { x, y, pos.path + direction, ++distance };
   case MAZEEND:
     return { END, END, pos.path + direction, distance };
   case START:
     return { VISITED, VISITED, pos.path + direction, distance };
   }
   std::cerr << "shouldn't be here" << std::endl;
   return { VISITED, VISITED, pos.path + direction, distance };
 }

 Trip walkRight(std::string &map, Trip &pos, V2 wh) {
   int d = pos.distance;
   for (int x = pos.x + 1; x < wh.x - 1; x++) {
     Trip trip = performWalk(map, x, pos.y, 'r', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { wh.x - 2, pos.y, pos.path + 'r', d };//We hit the wall;
 }

 Trip walkLeft(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int x = pos.x - 1; x > -1; x--) {
     Trip trip = performWalk(map, x, pos.y, 'l', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { 0, pos.y, pos.path + 'l', d };//We hit the wall;
 }

 Trip walkUp(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int y = pos.y - 1; y > -1; y--) {
     Trip trip = performWalk(map, pos.x, y, 'u', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { pos.x, 0, pos.path + 'u', d };//We hit the wall;
 }

 Trip walkDown(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int y = pos.y + 1; y < wh.y; y++) {
     Trip trip = performWalk(map, pos.x, y, 'd', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { pos.x, wh.y - 1, pos.path + 'd', d };//We hit the wall;
 }

 std::vector<char> walkMap(std::string map) {
   V2 wh = { width(map), height(map) };
   std::set<Trip, TripKeyCompare> queue;
   std::set<Trip, TripKeyCompare> endings;
   std::set<unsigned long long> queueHistory;

   V2 start = getStart(map, wh); 
   queue.insert({ start.x, start.y, "", 0 });
   std::vector<char> result;

   while (queue.size() > 0) {
     Trip p = *queue.begin();
     queue.erase(queue.begin());

     unsigned long long posKey = p.x;
     posKey <<= 32;
     posKey |= p.y;
     if (queueHistory.count(posKey) > 0)
       continue;

     queueHistory.insert(posKey);

     char lastDir = ' ';
     if (p.path.size() > 0) {
       lastDir = p.path[p.path.size() - 1];
     }

     Trip trips[4];
     if (lastDir != 'r')
       trips[0] = walkLeft(map, p, wh);
     if (lastDir != 'l')
       trips[1] = walkRight(map, p, wh);
     if (lastDir != 'd')
       trips[2] = walkUp(map, p, wh);
     if (lastDir != 'u')
       trips[3] = walkDown(map, p, wh);

     for (int i = 0; i < 4; i++) {
       if (trips[i].x == SKIP) continue;

       if (trips[i].x == END) {
         endings.insert(trips[i]);
       }

       if (!(trips[i].x == p.x && trips[i].y == p.y) && trips[i].x != VISITED && trips[i].x != END) {
         queue.insert(trips[i]);
       }
     }
   }

   if (endings.size() > 0) {
     Trip end = *endings.begin();
     for (int j = 0; j < (int)end.path.size(); j++) {
       result.push_back(end.path[j]);
     }  
   }

   return result;
 }

 std::vector<char> ice_maze_solver(const std::string &map)
 {
   std::cout << map << std::endl;
   return walkMap(map);
 }

     * 2 years ago
     * Refactor

 //Breadth first search with history kludge
 #include <set>
 #include <map>

 const char START = 'S';
 const char MAZEEND = 'E';
 const char ICE = ' ';
 const char SAND = 'x';
 const char ROCK = '#';

 const int VISITED = -1;
 const int END = -2;
 const int CONTINUE = -3;
 const int SKIP = -4;

 struct History {
   int index;
   bool left;
   bool right;
   bool up;
   bool down;
   History() {
     left = false;
     right = false;
     up = false;
     down = false;
   }
 };


 struct Trip {
   int x;
   int y;
   std::string path;
   int distance;
   std::map<int, History> history;
   Trip() {
     x = SKIP;
     y = SKIP;
     path = "";
     distance = 0;
   }
   Trip(int x, int y, std::string path, int distance) {
     this->x = x;
     this->y = y;
     this->path = path;
     this->distance = distance;
   }
 };

 struct TripKeyCompare {
   bool operator()(const Trip &a, const Trip &b) {
     if (a.path.size() < b.path.size()) {
       return true;
     }
     else if (a.path.size() == b.path.size() && a.distance == b.distance) {
       return (a.path < b.path); //We want to keep unique paths
     }
     else if (a.path.size() == b.path.size()) {
       return (a.distance < b.distance);
     }
     else {
       return false;
     }
   }
 };

 struct V2 {
   int x;
   int y;
 };

 int width(std::string map) {
   return map.find('\n') + 1;
 }

 int height(std::string map) {
   int w = width(map);
   //Add one for the last newline
   return (map.size() + 1) / w;
 }

 int getIndex(V2 pos, V2 wh) {
   return pos.y * wh.x + pos.x;
 }

 V2 getStart(std::string map, V2 wh) {
   for (int y = 0; y < wh.y; y++) {
     for (int x = 0; x < wh.x - 1; x++) {
       if (map[getIndex({ x,y }, wh)] == START)
         return { x, y };
     }
   }
   return { -1, -1 };
 }

 void setHistory(int index, char direction, std::map<int, History> &history) {
   switch (direction) {
   case 'u': history[index].up = true; break;
   case 'd': history[index].down = true; break;
   case 'l': history[index].left = true; break;
   case 'r': history[index].right = true; break;
   }
 }

 Trip performWalk(std::string &map, int x, int y, char direction, int &distance, Trip &pos, V2 wh) {
   int idx = getIndex({ x, y }, wh);

   if (pos.history.count(idx) > 0) {
     if (direction == 'u' && pos.history[idx].up)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'd' && pos.history[idx].down)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'l' && pos.history[idx].left)
       return { VISITED, VISITED, pos.path + direction, distance };
     else if (direction == 'r' && pos.history[idx].right)
       return { VISITED, VISITED, pos.path + direction, distance };
   }

   switch (map[idx]) {
   case ICE:
     setHistory(idx, direction, pos.history);
     return { CONTINUE, CONTINUE, pos.path, ++distance };
   case ROCK:
     if (direction == 'l')
       return { x + 1, y, pos.path + direction, distance };
     else if (direction == 'r')
       return { x - 1, y, pos.path + direction, distance };
     else if (direction == 'u')
       return { x, y + 1, pos.path + direction, distance };
     else if (direction == 'd')
       return { x, y - 1, pos.path + direction, distance };
     break;
   case SAND:
     setHistory(idx, direction, pos.history);
     return { x, y, pos.path + direction, ++distance };
   case MAZEEND:
     return { END, END, pos.path + direction, distance };
   case START:
     return { VISITED, VISITED, pos.path + direction, distance };
   }
 }

 Trip walkRight(std::string &map, Trip &pos, V2 wh) {
   int d = pos.distance;
   for (int x = pos.x + 1; x < wh.x - 1; x++) {
     Trip trip = performWalk(map, x, pos.y, 'r', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { wh.x - 2, pos.y, pos.path + 'r', d };//We hit the wall;
 }

 Trip walkLeft(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int x = pos.x - 1; x > -1; x--) {
     Trip trip = performWalk(map, x, pos.y, 'l', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { 0, pos.y, pos.path + 'l', d };//We hit the wall;
 }

 Trip walkUp(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int y = pos.y - 1; y > -1; y--) {
     Trip trip = performWalk(map, pos.x, y, 'u', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { pos.x, 0, pos.path + 'u', d };//We hit the wall;
 }

 Trip walkDown(std::string &map, Trip pos, V2 wh) {
   int d = pos.distance;
   for (int y = pos.y + 1; y < wh.y; y++) {
     Trip trip = performWalk(map, pos.x, y, 'd', d, pos, wh);
     if (trip.x != CONTINUE)
       return trip;
   }
   return { pos.x, wh.y - 1, pos.path + 'd', d };//We hit the wall;
 }

 std::vector<char> walkMap(std::string map) {
   V2 wh = { width(map), height(map) };
   std::set<Trip, TripKeyCompare> queue;
   std::set<Trip, TripKeyCompare> endings;
   std::set<unsigned long long> queueHistory;

   V2 start = getStart(map, wh);
   queue.insert({ start.x, start.y, "", 0 });
   std::vector<char> result;

   while (queue.size() > 0) {
     Trip p = *queue.begin();
     queue.erase(queue.begin());

     unsigned long long posKey = p.x;
     posKey <<= 32;
     posKey |= p.y;
     if (queueHistory.count(posKey) > 0)
       continue;

     queueHistory.insert(posKey);

     char lastDir = ' ';
     if (p.path.size() > 0) {
       lastDir = p.path[p.path.size() - 1];
     }

     Trip trips[4];
     if (lastDir != 'r')
       trips[0] = walkLeft(map, p, wh);
     if (lastDir != 'l')
       trips[1] = walkRight(map, p, wh);
     if (lastDir != 'd')
       trips[2] = walkUp(map, p, wh);
     if (lastDir != 'u')
       trips[3] = walkDown(map, p, wh);

     for (int i = 0; i < 4; i++) {
       if (trips[i].x == SKIP) continue;

       if (trips[i].x == END) {
         endings.insert(trips[i]);
       }

       if (!(trips[i].x == p.x && trips[i].y == p.y) && trips[i].x != VISITED && trips[i].x != END) {
         queue.insert(trips[i]);
       }
     }
   }

   if (endings.size() > 0) {
     Trip end = *endings.begin();
     for (int j = 0; j < end.path.size(); j++) {
       result.push_back(end.path[j]);
     }  
   }

   return result;
 }

 std::vector<char> ice_maze_solver(const std::string &map)
 {
   return walkMap(map);
 }
