/**
 * @file ClusterModuleExt.cpp
 * @brief ClusterModule extension
 *
 * This file is created at Almende B.V. It is open-source software and part of the Common 
 * Hybrid Agent Platform (CHAP). A toolbox with a lot of open-source tools, ranging from 
 * thread pools and TCP/IP components to control architectures and learning algorithms. 
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless,
 * we personally strongly object against this software being used by the military, in the
 * bio-industry, for animal experimentation, or anything that violates the Universal
 * Declaration of Human Rights.
 *
 * Copyright © 2013 Your Name <your@email>
 *
 * @author	Your Name
 * @date	Current date
 * @company	Your Company
 * @project	Specific Software Project
 */

#include <ClusterModuleExt.h>

using namespace rur;

enum DataSet { D_ABALONE, D_GAUSSIAN, D_IRIS, NUMBER_OF_DATASETS };

ClusterModuleExt::ClusterModuleExt(){
	time_begin_ms = get_cur_1ms();
	std::ifstream f;
	DataSet dataset;
	dataset = D_ABALONE;
//	dataset = D_IRIS;
//	dataset = D_GAUSSIAN;
	std::string file = "";


	switch(dataset){
	case D_ABALONE: {
		file = "../../data/abalone2.data";
		predefined_clusters = 28;

//		file = "../../data/abalone4.data";
//		predefined_clusters = 3;
	}
	break;
	case D_IRIS:{
		file = "../../data/iris2.data";
		predefined_clusters = 3;
	}
	break;
	case D_GAUSSIAN: {
		file = "../../data/gaussian.data";
		predefined_clusters = 2;
	}
	break;
	}

	f.open(file.c_str());
	if (f.is_open()) {
		f >> d;
	} else {
		std::cerr << "File " << file << " does not exist " << std::endl;
	}

	index = 0;

	stop = false;
}

//! Replace with your own functionality
void ClusterModuleExt::Tick() {
	std::vector<value_t> & item = d.pop();
	int D = item.size() - 1; // dimensionality of data samples (length of vector minus field for label)
	std::cout << "Dimensionality is " << D << std::endl;
	int K = predefined_clusters;

	FuzzyCMeans fuzzycmeans(K,D);

	int S = d.size(); // # samples
	std::cout << "Load all " << S << " samples" << std::endl;
	for (int s = 0; s < S; ++s) {
		fuzzycmeans.addSample(item, item[D], D);
		item = d.pop();
	}

	fuzzycmeans.initPostSample();

	int T = 400; // time span
	for (int t = 0; t < T; ++t) {
		if (!(t%10)) std::cout << '.'; flush(std::cout);
		fuzzycmeans.tick();
	}
std::cout << std::endl;

fuzzycmeans.evaluate();

	long time = get_cur_1ms()-time_begin_ms;
	std::cout << "Clustering took " << time << " ms" << std::endl;
	stop = true;
}

//! Replace with your own functionality
bool ClusterModuleExt::Stop() {
	return stop;
}

