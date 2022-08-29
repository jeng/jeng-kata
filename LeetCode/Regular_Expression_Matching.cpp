enum nodetype_t {
    NTT_ANY,
    NTT_WILD,
    NTT_CHAR,
    NTT_START,
    NTT_END
};
struct node_t {
    int id;
    nodetype_t type;
    char value;
    std::vector<node_t*> outgoing;
    std::vector<node_t*> incoming;
};
class Solution {
private:
    node_t* BuildDAG(std::string regex) {
    int nodeIds = 0;
    node_t* start = new node_t; 
    start->type = NTT_START;
    start->value = 's';
    start->id = nodeIds++;
    node_t* current = start;
    for (int i = 0; i < regex.size(); i++) {
        switch (regex[i]) {
        case '*': {
            node_t* n = new node_t;
            n->type = NTT_WILD;
            n->value = '*';
            n->id = nodeIds++;
            current->outgoing.push_back(n);
            n->incoming.push_back(current);
            current = n;
            break;
        }
        case '.': {
            node_t* n = new node_t;
            n->type = NTT_ANY;
            n->value = '.';
            n->id = nodeIds++;
            current->outgoing.push_back(n);
            n->incoming.push_back(current);
            current = n;
            break;
        }
        default: {
            node_t* n = new node_t;
            n->type = NTT_CHAR;
            n->value = regex[i];
            n->id = nodeIds++;
            current->outgoing.push_back(n);
            n->incoming.push_back(current);
            current = n;
            break;
        }
        }
    }
    node_t* end = new node_t;
    end->type = NTT_END;
    end->value = 'e';
    end->id = nodeIds++;
    end->incoming.push_back(current);
    current->outgoing.push_back(end);
    //Second pass compresses wildcards
    current = end;
    while (current->type != NTT_START) {
                node_t* previous = current->incoming[0];
        assert(current->incoming.size() == 1);
        if (current->type == NTT_WILD) {            
            // 1. Remove outgoing from previous to wild card
            assert(previous->outgoing.size() == 1);
            previous->outgoing.clear();
            // 2. Link previous to any outgoing of wildcard
            for (int i = 0; i < current->outgoing.size(); i++) {
                previous->outgoing.push_back(current->outgoing[i]);
                // 3. Remove incoming from next to wild card
                std::vector<node_t*> incoming;
                for (int j = 0; j < current->outgoing[i]->incoming.size(); j++) {
                    if (current->outgoing[i]->incoming[j]->type != NTT_WILD) {
                        incoming.push_back(current->outgoing[i]->incoming[j]);      
                                                                }
                }
                // Copy the new outgoing vector
                current->outgoing[i]->incoming.clear();
                for (int j = 0; j < incoming.size(); j++) {
                    current->outgoing[i]->incoming.push_back(incoming[j]);
                }
            }           
                        // 4. Link previous' previous to any previous outgoing
            for (int j = 0; j < previous->incoming.size(); j++) {
                node_t* previousPrevious = previous->incoming[j];
                for (int k = 0; k < previous->outgoing.size(); k++) {
                    previousPrevious->outgoing.push_back(previous->outgoing[k]);
                }
            }
                        // 5. Link previous to itself
            previous->outgoing.push_back(previous);
            // 6. Free current
            delete current;
        }
        // 7. Move down the stack
        current = previous;
    }
    return start;
}
bool DAGMatches(node_t* dag, std::string input, int inputIdx) {
    if (dag->type == NTT_END && inputIdx > input.size()) {
        return true;
    } else if (inputIdx < 0 || inputIdx > input.size()) {
        return false;
    } else {
        for (int i = 0; i < dag->outgoing.size(); i++) {
            if (dag->outgoing[i]->type == NTT_END) {
                if (DAGMatches(dag->outgoing[i], input, inputIdx + 1))
                    return true;
            } else if (dag->outgoing[i]->type == NTT_CHAR
                && dag->outgoing[i]->value == input[inputIdx]) {
                if (DAGMatches(dag->outgoing[i], input, inputIdx + 1))
                    return true;
            }
            else if (dag->outgoing[i]->type == NTT_ANY) {
                if (DAGMatches(dag->outgoing[i], input, inputIdx + 1))
                    return true;
            }
        }
        return false;
    }
}
public:
    bool isMatch(string s, string p) {
        node_t* dag = BuildDAG(p);
        return DAGMatches(dag, s, 0);
    }
};