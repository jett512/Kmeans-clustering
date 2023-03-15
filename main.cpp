//HDF5
#include <stdio.h>
#include <h5.hpp>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <hdf5.h>
#include <H5Cpp.h>

//output
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json.hpp>
#include <cstdio>

//data structures
#include <vector>
#include <string>
#include <map>
#include"kmeans.h"
#include "kmeansplusplus.h"

//random and math
#include <algorithm>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;
using json = nlohmann::json;//plotting output

void getAccuracyVar(string &dataset_name, int &occurance, string &key, string &gt){
     //obtain feature name
        string fullDataName = dataset_name;
        int i = fullDataName.find_first_of("_");
        key = fullDataName.substr(i+1);
        string dataName = fullDataName.substr(i+1);
        if(key.size() == 12){
            key.resize(key.size() - 7);
        }
        if(key.size() == 11){
            key.resize(key.size() - 6);
        }

        //obtain feature occurances
        occurance = 0;
        string occTemp = dataset_name;
        int o = occTemp.find("_");
        occTemp.resize(o);
        if(occTemp.size() == 4){
            string occ = occTemp.substr(o - occTemp.size());
            occurance = (std::stoi(occ)) - 1000;
        }
        else if(occTemp.size() == 3){
            string occ = occTemp.substr(o - occTemp.size());
            occurance = (std::stoi(occ)) - 100;
        }
        else{
            string occ = occTemp.substr(o - occTemp.size());
            occurance = std::stoi(occ);
        }

        //obtains gt variable at end of feature name
        string featName = dataName.c_str();
        int j = featName.find_first_of("_");
        gt = featName.substr(j+1);
}

void accuracy(map<int, string> &imgNames, map<int, string> &gtMap, map<int, int> &idMap){
    int match = 0;
    int miss = 0;
    int clustId = -1;
    int truthId = -1;
    int group = -1;
    float accuracy = 0.0;
    map<int, int> clustMap;
    map<int, int> truthMap;

    ofstream out2;
    out2.open("output.csv");

    vector<int> id;
    vector<int> tru;
    for(auto item: imgNames){
        /*feature index: */ //cout << item.first << endl;
        clustId = idMap[item.first];
        clustMap[item.first] = clustId;
        id.push_back(clustId);
        string truth = gtMap[item.first];
        int truthId = std::stoi(truth);
        truthMap[item.first] = truthId;
        tru.push_back(truthId);
    }

    map<int, vector<int>> accMap;

    for(int x = 0; x < 21; x++){
        vector<int> clust_x;
        for(int i = 0; i < 8191; i++){
            //cout << truthMap[i] << ", " <<clustMap[i] << endl;
            if(truthMap[i] == x){
                int temp = clustMap[i];
                clust_x.push_back(temp);

            }
        }
        accMap[x] = clust_x;
    }

    int v = 0;
     for(map<int, vector<int> >:: iterator ii= accMap.begin(); ii != accMap.end(); ++ii){
        //cout <<(*ii).first<< ": ";
        //cout << " Cluster " << v << " :-------------------- " << endl;
        vector<int> accVect = (*ii).second;
        for(int x = 0; x < 21; x++){
                //cout << "For TruthID: "<< v << ", Cluster " << x << " appears " << count(accVect.begin(), accVect.end(), x) << endl;

        }
        v++;
        //cout << endl;
    }

    out2.close();

    accuracy = (match / 8192.00) * 100.00;
    cout << accuracy <<"% accurate cluster assignments" << endl;
    cout << miss <<" incorrect assignments" << endl;
}

list<Point> readcsv() {
    list<Point> points;

    string line;
    ifstream file("data.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        float x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }


    return points;
}

vector<string> getImgNameVec(hid_t &group, vector<string> &imgNames, string dataset_name){

int index = 0;
char name[25];
H5G_info_t group_info;
herr_t status = H5Gget_info(group, &group_info);

// Iterate over the objects in the group.
    while (index < group_info.nlinks)
    {

        // Get the name of the object and its type.
        H5Gget_objname_by_idx(group, (hsize_t)index, name, (size_t)25 );
        H5G_obj_t obj_type = H5Gget_objtype_by_idx(group, (hsize_t)index);

        imgNames.push_back(name);
        dataset_name = imgNames.at(index);

        //cout << dataset_name << " ";
        index++;// Increment the index and continue the iteration.
    }
    return imgNames;
}

vector<string> getfeatureName(){
    hid_t file_id, group;
    string file_name, group_name, dataset_name;

    //access file
    file_name = "H5Data/features_with_GT.h5";//hard coded, h5 file dependent
    //file_name = "H5Data/unknown_features.h5";//hard coded, h5 file dependent
    file_id = H5Fopen(file_name.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

    //access group
    group_name = "FeatureAndBbox";//hard coded, h5 file dependent
    group = H5Gopen(file_id, group_name.c_str(), H5P_DEFAULT);

    vector<string> imgNames;//image names vector

    imgNames = getImgNameVec(group, imgNames, dataset_name);//store feature vector

    return imgNames;
}

int main()
{
    json j;//json object

    int k ;
    cout << "Enter k"<< endl;
    cin >> k;
    int occurance;
    string dataset_name, key, gt;


    //maps to improve performance
    map<int, vector<float>> dataMap;//map to store data vectors
    map<int, string> imgNames;
    map<int, string> featMap;//map to store feature keys
    map<int, string> gtMap;//map to store ground truth for accuracy
    map<int, int> occMap;//map to store feature occurance

    vector<string> feat = getfeatureName();//feature name vector
    int featNum = feat.size() - 1;
    for(int i = 0; i < featNum; i++){
        dataset_name = feat.at(i);
        imgNames[i] = dataset_name;
    }

    int vecElem_Buf = 1028;
    int vecElem = vecElem_Buf - 4;
    h5::file file("H5Data/features_with_GT.h5", "r");
    //h5::file file("H5Data/unknown_features.h5", "r");
    vector<float> buf(vecElem_Buf);
    h5::shape<1> shape = {vecElem_Buf};

    //store data vectors into map for each feature
    for(int f = 0; f < featNum; f++){
        dataset_name = imgNames[f];

        //uses dataset_name to obtain info about each feature for accuracy
        getAccuracyVar(dataset_name, occurance, key, gt);

        occMap[f] = occurance;//store occurances in its map
        featMap[f] = key;//store feature key in its map
        gtMap[f] = gt;//store ground truth in its map

        file.dataset<h5::f32, 1>("FeatureAndBbox/"+ dataset_name).read(buf.data(), shape);
        dataMap[f] = buf;

    }


    ofstream out;
    out.open("data.csv");
    /*
    //output to csv file
    for(int i = 0; i < vecElem; i++){
        out << i << ", ";
    }
    out << "id" << endl;
    */
    map<int, vector<float>> fltMap;
    for(map<int, vector<float> >:: iterator ii= dataMap.begin(); ii != dataMap.end(); ++ii){
        //cout <<(*ii).first<< ": ";
        vector<float> inVect = (*ii).second;
        for(unsigned j = 0; j < vecElem; j++){

            out << inVect[j] << ", ";
        }
        out << endl;
    }
    out.close();


/*
  //relative output for debugging
   for(auto item: imgNames){
        cout << "Index: " << item.first << ", feature name: " << featMap[item.first] << ", Occurance: " << occMap[item.first]
        << ", GT: " << gtMap[item.first] << ", ClusterID: " << idMap[item.first] << endl;
    }
*/
    //function to output number of clusters in ground truth and id assignemnts
    //getNumberCluster(gtMap, idMap);


    list<Point> dataPoints = readcsv();
    std::clock_t start;
	double duration;

    KmeansPlusPlus kmeansPlusPlus(k);
	kmeansPlusPlus.InitPoints(dataPoints);
	start = std::clock();
	kmeansPlusPlus.InitCenters();
	//kmeans.InitSpecifiedCenters();
	kmeansPlusPlus.RunKmean();
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "calculate time " << duration << std::endl;
	kmeansPlusPlus.SaveEPS("S1_++.eps");
	kmeansPlusPlus.SaveSVG("S1_++.svg");
	system("pause");


    ifstream out1;
    out1.open("output.csv");

    map<int, int> idMap;

    int id;
    int index = 0;
    //populates idMap
    while (out1 >> id ) {
        idMap[index] = id;
        index++;
    }
    out1.close();


    ofstream out2;
    out2.open("dataOut.csv");

    //output to csv file
    int i = 0;
    for(i; i < vecElem; i){
        out2 << i << ", ";
        i++;
    }
    out2 << i;
    out2 << endl;

    int idx = 0;
    for(map<int, vector<float> >:: iterator ii= dataMap.begin(); ii != dataMap.end(); ++ii){
        //cout <<(*ii).first<< ": ";
        vector<float> inVect2 = (*ii).second;

        for(unsigned j = 0; j < vecElem; j++){

            out2 << inVect2[j] << ", ";
        }
        out2 << idMap[idx];
        out2 << endl;
        idx++;
    }

    out.close();

    //accuracy(imgNames, gtMap, idMap);//check

/*
    // Create the script file for gnuplot
   ofstream script("plot.gp");

   // Set the data file and the plot style
   script << "set datafile separator ','\n";
   script << "plot 'centroids.json' using 1:2:3 with points pt 4 lc variable\n";

   // Set the x and y ranges and add labels and a title
   script << "set xrange [-10:10]\n";
   script << "set yrange [-10:10]\n";
   script << "set xlabel 'x'\n";
   script << "set ylabel 'y'\n";
   script << "set title 'Scatter Plot'\n";

   // Close the script file
   script.close();

   // Execute the script using gnuplot
   system("gnuplot -p plot.gp");

*/
    return 1;
}

