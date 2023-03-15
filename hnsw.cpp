/* A C++ Translation of 'hnsw.py' by Toufik
 * C++ code written by Jake Stuart
 */

//TODO: add ifndef statement and beautify class declaration
// - assign types to all member variables (talk with Toufik)
#include <random>
#include <vector>


class HNSW {
private:
    //void members are of unknown type
    //all types subject to change
    void data;
    //TODO Use a function pointer to implement the selection of different distance functions and preserve
    // the behavior of the source
    void distance;
    void distance_func;
    void vectorized_distance
    int _m;
    int _ef;
    int _m0;
    void _level_mult;
    void _graphs;
    int _enter_point;
    void _select;

public:
    //Open CV has functions for linear algebra calcs, may be a candidate to replace "norm" function
    // in the "l2_distance" and "cosine_distance" function
    int l2_distance(int[] a,int[] b);
    int cosine_distance(int[] a, int[] b);
    int distance(int[] x, int[] y);
    int vectorized_distance(int[] x, int[]y);

    /* Class Constructor
        parameters:
          string  distance_type - indicates which dist function to use ('l2' or 'cosine')
          int m -
          int ef -
          int m0 - default init to 'None' in source
          bool heuristic - defaults to true
          bool vectorized - defaults to false
        effect:
            initialize HNSW object upon instantiation
    */
    HNSW(string distance_type, int m = 5, int ef = 200, int m0, bool heuristic = true, bool vectorized = false ) {
        // self.data = []
        if(distance_type == "l2") {
            //use l2 distance
        }
        else if(distance_type == "cosine") {
            //use cosine distance
        }
        else {
            //raise an error for incorrect distance entry
        }

        //assign distance function value

        if(vectorized) {
            //self.distance = self._distance
            //self.vectorized_distance = self.vectorized_distance_
        }
        else {
            //self.distance = distance_func
            //self.vectorized_distance = self.vectorized_distance_
        }

        _m = m;
        _ef = ef;
        //_m0 = (m0 == None) ? 2*m : m0; //what is the equivalent for "None"
        _level_mult = 1 / log2(m);
        //graphs = []  //what is the equivalent here, what is the python expression saying?
        // _enter_point = None; //Again, what does "None" represent here

        //A function pointer may work here to make the function chosen dynamic and callable by a single function
        //self.select = (heuristic) ? _select_heurisitic : _select_naive
    }

    /* Add
        parameters:
            void elem -
            void ef - [a heap of entry points?]
        effect:

    */
    void add(void elem, int ef = None) {
        //What is the equivalent of "None" here?
        //MAYBE: NAN and isNAN(), but they invlove an additional library
        if(ef == None) {
            ef = _ef;
        }

        // ~ distance = self.distance
        // ~ data = self.data
        // ~ graphs = self._graphs
        // ~ point = self._enter_point
        // ~ m = self._m


        double random; //define random value here
        //What data type should this random number be?

        //Level at which the element will be inserted
        int level = (int)(-1 * log2(random) * _level_mult) + 1;

        int idx; //Need to know the type of "data" to get its length
        data.append(elem); //seems to be a vector of integers

        if(point != None) {
            void dist = distance(elem, data[point]);

            //for all levels in which we don't have to insert elem,
            //we search for the closest neighbor

            //For loop itereates over each "layer" in "reversed(graphs[level:])"
            for() {
                // ~ point, dist = self._search_graph_ef1(elem, point, dist, layer)
            }
            //at these levels we have to insert elem; ep is a heap of entry points

            // ~ ep = [(-dist, point)]

            // ~ layer0 = graphs[0];

            //For loop itereates over each "layer" in "reversed(graphs[level:])"
            for() {
                int level_m = (layer != layer0) ? m : _m0;
                //navigate the graph and update ep with the closest
                // nodes we find
                // ~ ep = self._search_graph(elem, ep, layer, ef)
                //insert the best neighbors into g[idx]
                // ~ layer[idx] = layer_idx = {}
                // ~ self._select(layer_idx, ep, level_m, layer, heap = true)

                //insert backlinks to the new node

                //for each j and dist in layer_idx.items() [Items gives a list of tuples in a dictionary]
                for() {
                    // ~ self._select(layer[j], (idx,dist), level_m, layer)
                }

            }
        }


        for(int i = [len(graphs)], i < levels; i++) {
            //for all new levels, create an empty graph
            // ~ graphs.append({idx: {}})
            // ~ self._enter_point = idx
        }
    }

    /* Balanced Add
        parameters:
            void elem -
            void ef - [a heap of entry points?]
        effect:

    */
    void balanced_add(elem, ef = None) {

    }

    /* Search
        parameters:
            void q -
            void k - default to "None"
            void ef - [a heap of entry points?] default to "None"
        effect:

        return:
            return [(idx, -md) for md, idx in ep],data
            [unsure of the makeup of this so I will leave the type void for now]

    */

    //TODO: Make a struct return for this
    // "SEARCH_RESULT", perhaps
    void search(void q, void k = None, void ef = None) {

    }

    /* Search Graph EF1
        parameters:
            void q -
            void ep -
            void layer -
            void ef - [a heap of entry points?]
        effect:
            "Equivalent to _search_graph when ef = 1"
        return:
            return best, best_dist,data
            [unsure of the makeup of this so I will leave the type void for now]

    */
    void _search_graph_ef1(void q, void ep, void layer, void ef) {

    }

    /* Search Graph
        parameters:
            void q -
            void ep -
            void layer -
            void ef - [a heap of entry points?]
        effect:

        return:
            return best, best_dist,data
            [unsure of the makeup of this so I will leave the type void for now]

    */
    void _search_graph(void q, void ep, void layer, void ef) {

    }

    void _select_naive(void d, void to_insert, void m, void layer, bool heap = false) {

    }

    void _select_heuristic(void d, void to_insert, void m, void g, bool heap = false) {

    }

    void __getitem__(void idx) {

    }




}
