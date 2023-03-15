# Scalable High Dimensional Indexing and Search

# Kmeans++ on HDF5 data
* Kmeans++ implementation from https://github.com/ieyjzhou/KmeansPlusPlus, that has been modified to accept HDF5 datasets. The goal of this program is to give a cluster assignment to vectors that are close together. The vectors should be given one assignment each, and clustered around an initialized centroid based on the Kmeans++ algorithm.
* The example data is included under the H5Data folder, but has been zipped to allow for uploads onto github. Unzip this file to test the data using the ground truth features.
* Included accuracy function for determining how accurate clustering algorithm assignments are.
* The Plot folder includes some example plots for the program with varying values of K. Also, the ground truth for this dataset has been plotted and is included as GtPlot.png. The 2D_cluster_plot.ipynb makes use of the dataOut.csv file created by the cpp program to reduce dimensionality for plotting. When trying to plot the data, make sure to upload the dataOut.csv to the file via google collab for plotting.
* Program also plots data into .svg file format, but these plots have not been reduced in dimension, so their results may vary

 

# Dependencies
* HDF5 folder and the separate include folder. The HDF5 folder allows for use of the HDF5 library and header files needed to access HDF5 files and datasets.The include folder contains necessary headers for the clustering algorithm to function. 
* The hdf5.lib and hdf5_cpp.lib libraries located inside the lib under HDF5 folder.
* Environment search directories should include the plugin and bin folders under the HDF5/1.12.12 folder.
* Environment linker settings should include hdf5.lib and hdf5_cpp.lib libraries.


  
