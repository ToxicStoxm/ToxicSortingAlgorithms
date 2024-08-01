#include <iostream>
#include <vector>
#include <unistd.h>
#include <random>

using namespace std;

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

#define LENGTH 50
#define MAX 200

int max(vector<vector<bool>> *matrix) {
  int temp = -2147483648;
  unsigned int matrixSize = matrix->size();
  for (unsigned int i = 0; i < matrixSize; i++) {
    temp = max(temp, (int) matrix->at(i).size());
  }
  return temp;
}


void rotate(vector<vector<bool>> *matrix) {
  vector<vector<bool>> temp;

  unsigned int matrixSize = matrix->size();

  for (int i = max(matrix) - 1; i >= 0 ; i--) {
    vector<bool> tempy;
    for (unsigned int j = 0; j < matrixSize; j++) {
      tempy.push_back(matrix->at(j).at(i));
    }
    temp.push_back(tempy);
  }
  *matrix = temp;
}

void pushPixels(vector<vector<bool>> matrix) {
  rotate(&matrix);

  cout << "\033[H";
  cout.flush();

  unsigned int matrixSize = matrix.size();

  for (unsigned int i = 0; i < matrixSize; i++) {
    vector<bool> line = matrix.at(i);
    for (unsigned int j = 0;  j < line.size(); j++) {
      cout << (line.at(j) ? string(BLKB) : string(WHTB)) << "  ";
    }
    cout << reset << endl;
  }
  cout << reset;
}

int max(vector<int> *list) {
  int temp = -2147483648;
  for (unsigned int i = 0; i < list->size(); i++) {
    temp = max(temp, list->at(i));
  }
  return temp;
}

void printList(vector<int> *list) {
  /*cout << "Current List: [";
  for (unsigned int i = 0; i < list->size(); i++) {
    cout << list->at(i);
    if (i != list->size() - 1) cout << ", ";
    cout.flush();
  }
  cout << "]" << endl;*/

  vector<vector<bool>> diagram;
  vector<bool> def;
  vector<bool> temp;
  def.resize(max(list) + 2);

  diagram.push_back(def);
  for (unsigned int i = 0; i < list->size(); i++) {
    temp = def;
    for (int j = 0; j < list->at(i); j++) {
      temp.at(j + 1) = true;
    }
    diagram.push_back(temp);
    diagram.push_back(def);
  }

  pushPixels(diagram);
}

void sort(vector<int> *list) {
  int factor = 0;
  int j;
  int k;
  for (unsigned int i = 0; i < list->size(); i++) {
    for (unsigned int i = 0; i < list->size() - factor; i++) {
      if (i != list->size() - 1) {
        j = list->at(i);
        k = list->at(i + 1);
        if (j > k) {
          list->at(i + 1) =  j;
          list->at(i) = k;
        }
      }

      //usleep(100);
      printList(list);
	  }
	  factor++;
	}
}

void generateRandomList(int length, int maxVal, vector<int> *base) {

  random_device rd; // obtain a random number from hardware
  mt19937 gen(rd()); // seed the generator
  uniform_int_distribution<> distr(1, maxVal);

  for (int i = 0; i < length; i++) {
    base->push_back(distr(gen));
  }

  cout << "Current List: [";
  for (unsigned int i = 0; i < base->size(); i++) {
    cout << base->at(i);
    if (i != base->size() - 1) cout << ", ";
    cout.flush();
  }
  cout << "]" << endl;
}

int main() {
  vector<int> list;
  generateRandomList(LENGTH, MAX, &list);

	sort(&list);

	return 0;
}
