#include <tuple>
#include <map>
#include <stdio.h>
#include <string>

typedef std::tuple<std::string, std::string, std::string> pageCombo; // change this if comboLength changes

#define stringSpace 300

#define comboLength 3

/* Read from stdin lines like:
timestamp customerID page
Then count the most popular 3-page combination
*/

using namespace std;

int main(int argc, char* argv[]) {
	std::map<pageCombo, int> votes; // hold the votes for each possible pageCombo
	std::multimap<std::string, std::string> visits; // hold the sequences that each customer has visited

	long long timestamp;
	char customerId[stringSpace];
	char pageType[stringSpace];
	int maxCombo = 0; // highest vote at the moment
	pageCombo popularCombo; // most popular combo at the moment
	while(scanf("%lld %s %s", &timestamp, customerId, pageType) == comboLength) {
		//visits[customerId].push_back(pageType);
		visits.insert(std::pair<string, string>(customerId, pageType));

		//printf("%s has %d page views\n",customerId, visits.count(customerId));
		if(visits.count(customerId) > comboLength) {
			std::multimap<string,string>::iterator vi = visits.find(customerId);
			visits.erase(vi); // no need to hang onto a combo that's already been counted
		}
		if(visits.count(customerId) == comboLength) {
			// count a vote
			std::multimap<string,string>::iterator vi = visits.find(customerId);
			string &page1 = vi->second;
			vi++;
			string &page2 = vi->second;
			vi++;
			string &page3 = vi->second;
			pageCombo pc = std::make_tuple(page1,page2,page3);
			
			votes[pc] += 1;
			//printf("vote is: %s, %s, %s\n",get<0>(pc).c_str(), get<1>(pc).c_str(), get<2>(pc).c_str());
			if(votes[pc] >= maxCombo) {
				popularCombo = pc; // keep track of the most popular combo
				maxCombo = votes[pc];
			}
		}
	}
	
	if(maxCombo > 0) {
		printf("%s\n",std::get<0,std::string>(popularCombo).c_str());
		printf("%s\n",std::get<1,std::string>(popularCombo).c_str());
		printf("%s\n",std::get<2,std::string>(popularCombo).c_str());
		// templates must be known at compile time; makes iteration difficult
	} else {
		printf("no sequence found\n");
	}

	return EXIT_SUCCESS;
}