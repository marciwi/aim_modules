/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief ...
 * @file kMeans.h
 * 
 * This file is created at Almende B.V. and Distributed Organisms B.V. It is open-source software and belongs to a
 * larger suite of software that is meant for research on self-organization principles and multi-agent systems where
 * learning algorithms are an important aspect.
 *
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless, we personally strongly object
 * against this software being used for military purposes, factory farming, animal experimentation, and "Universal
 * Declaration of Human Rights" violations.
 *
 * Copyright (c) 2013 Anne C. van Rossum <anne@almende.org>
 *
 * @author    Anne C. van Rossum
 * @date      Oct 2, 2013
 * @project   Replicator 
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case      Clustering
 */

#ifndef FUZZYCMEANS_H_
#define FUZZYCMEANS_H_

#include <Eigen/LU>
#include <vector>
#include <set>
#include <cmath>
#include <cstddef>
#include <algorithm>

/**
 * The k-means algorithm, also called Lloyd's algorithm. A generalization is the Linde-Buzo-Gray algorithm for vector
 * quantization, see https://en.wikipedia.org/wiki/Linde%E2%80%93Buzo%E2%80%93Gray_algorithm
 */
class FuzzyCMeans {
public:
	typedef float value_t;
	typedef Eigen::Matrix<value_t,1,Eigen::Dynamic> vector_t; // row_vector

	struct Pair {
		Pair(size_t ground_truth) {
			this->prediction = 0;
			this->ground_truth = ground_truth;
		}
		size_t prediction;
		size_t ground_truth;
	};

	// Cluster has a mean and references a subset of vectors in the data set
	struct Cluster {
		vector_t center;
	};

	// Membership is defined for each data point - cluster pair
	struct Membership{
		std::vector<value_t> mu;
	};

	FuzzyCMeans(int K, int D) {
		srand(time(NULL));

		clusters.resize(K);
		for (int k = 0; k < K; ++k) {
			init(k, D);
		}
	}

	~FuzzyCMeans() {}

	void tick() {
//		for (int k = 0; k < data_set.size(); ++k) {
//			clear(k);
//		}
		for (int i = 0; i < data_set.size(); ++i) {
			calc_membership(i);
		}
		for (int j = 0; j < clusters.size(); ++j) {
			update_center(j);
		}
	}

	/**
	 * Add a sample, size is given as separate parameter, so it is possible to take only the first N items from the
	 * sample rather than the entire vector.
	 */
	void addSample(std::vector<value_t> & x, size_t label, size_t size = 0) {
		if (!size) size = x.size();
		assert (size <= x.size());
		vector_t v(size); v.setZero();
		v = vector_t::Map(x.data(), 1, size); // create row-vector
		data_set.push_back(v);
		labels.push_back(Pair(label));
	}

	std::vector<Pair> & result() {
		return labels;
	}

	void initPostSample(){
		m=4;
		beta=0.5;
		memberships.resize(data_set.size());
	}

	void evaluate() {

		std::vector<value_t>::iterator elements;
		for (int s=0;s<data_set.size();s++){
			calc_membership(s);
			elements = std::max_element(memberships[s].mu.begin(),memberships[s].mu.end());
			labels[s].prediction = std::distance(memberships[s].mu.begin(),elements);
		}

//		std::cout << labels[3].ground_truth << std::endl;


		size_t a, b, c, d; a = b = c = d = 0;
		for (int i = 0; i < data_set.size(); ++i) {
			for (int j = i+1; j < data_set.size(); ++j) {
				if (labels[i].ground_truth == labels[j].ground_truth) {
					if (labels[i].prediction == labels[j].prediction) {
						a++;
					} else {
						c++;
					}
				} else {
					if (labels[i].prediction == labels[j].prediction) {
						d++;
					} else {
						b++;
					}
				}
			}
		}

		value_t quality = (a+b) / value_t(a+b+c+d);
		std::cout << "Rand index is " << quality << std::endl;
	}


protected:
	void init(int k, int d) {
		clusters[k].center.setRandom(d);
		clusters[k].center = (clusters[k].center.array() + 1) / 2;
	}

	void calc_membership(int s){
		std::vector<value_t> memships;
		memships.clear();					memships.resize(clusters.size());
		std::vector<value_t> distances;		distances.resize(clusters.size());
		for(int i=0;i<clusters.size();i++){
			distances[i] = (data_set[s]-clusters[i].center).squaredNorm();
		}
		for(int i=0;i<clusters.size();i++){
			for(int j=0;j<clusters.size();j++){
				memships[i] = memships[i] + pow(distances[i]/distances[j],2*(m-1));
			}
		memships[i] = 1.0/memships[i];
		}
		assert (s < memberships.size());
		memberships[s].mu=memships;
	}

	void update_center(int j){
		vector_t numerator;
		value_t common;
		assert (data_set.size() > 0);
		numerator.setZero(data_set[0].size());
		value_t denominator = 0;
		for(int i=0;i<data_set.size();i++){
			common = pow(memberships[i].mu[j],m);
			numerator = numerator + common*data_set[i];
			denominator = denominator + common;
		}
		assert (denominator);
		assert (j < clusters.size());
		numerator /= denominator;
		clusters[j].center = numerator;
	}

//	// delete all data references in clusters
//	void clear(int k) {
//		memberships[k].mu.clear();
//	}

private:
	std::vector<Cluster> clusters;

	std::vector<vector_t> data_set;

	std::vector<Pair> labels;

	std::vector<Membership> memberships;

	value_t m;		// fuzziness parameter

	value_t beta;	// stopping criterium
};


#endif /* FUZZYCMEANS_H_ */
