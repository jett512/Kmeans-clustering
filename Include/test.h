#include <vector>
#include <string>

using namespace std;

    map<string, int> getImgMap(hid_t &group, vector<string> &imgNames, string &dataset_name);
    map<string, int> getFeatMap(hid_t &group, vector<string> &imgNames, string dataset_name);

    vector<string> getImgNameVec(hid_t &group, vector<string> &imgNames, string dataset_name);
   // vector<float> getDataVec(hid_t &dataset, hid_t &datatype, hid_t &dataspace,hid_t &group, string &dataset_name, vector<float> dataVec);

    vector<vector<float>> makeData2D(vector<float> &dataVec);



