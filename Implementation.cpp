#include "Implementation.hpp"

//////////////////// Nested Loop Joins ////////////////////

std::vector<std::string> getQualifyingBusinessesIDsVector(Businesses const& b, float latMin,
																													float latMax, float longMin,
																													float longMax) {
	std::vector<std::string> qualifyingBusinesses;
	for(unsigned long i = 0; i < b.ids.size(); i++)
		if(b.latitudes[i] >= latMin && b.latitudes[i] <= latMax && b.longitudes[i] >= longMin &&
			 b.longitudes[i] <= longMax)
			qualifyingBusinesses.emplace_back(b.ids[i]);
	return qualifyingBusinesses;
}

std::vector<unsigned long> performNestedLoopJoinAndAggregation(Reviews const& r,
																												std::vector<std::string> const& qualies) {
	std::vector<unsigned long> groups(6);
	for(unsigned long j = 0; j < qualies.size(); j++)
		for(unsigned long i = 0; i < r.business_ids.size(); i++)
			if(r.business_ids[i] == qualies.at(j))
				groups[r.stars[i]]++;
	return groups;
}

//////////////////// Hash Join ////////////////////

std::unordered_set<std::string> getQualifyingBusinessesIDs(Businesses const& b, float latMin,
																													 float latMax, float longMin,
																													 float longMax) {
	std::unordered_set<std::string> qualifyingBusinesses;
	for(unsigned long i = 0; i < b.ids.size(); i++)
		if(b.latitudes[i] >= latMin && b.latitudes[i] <= latMax && b.longitudes[i] >= longMin &&
			 b.longitudes[i] <= longMax)
			qualifyingBusinesses.insert(b.ids[i]);
	return qualifyingBusinesses;
}

std::vector<unsigned long>
aggregateStarsOfQualifyingBusinesses(Reviews const& r,
																		 std::unordered_set<std::string> const& qualifyingBusinesses) {
	std::vector<unsigned long> groups(6);
	for(unsigned long i = 0; i < r.business_ids.size(); i++)
		if(qualifyingBusinesses.count(r.business_ids[i]) > 0)
			groups[r.stars[i]]++;
	return groups;
}
