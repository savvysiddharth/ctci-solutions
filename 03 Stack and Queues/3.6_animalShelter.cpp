#include <queue>
using namespace std;

class Animal {
  public:
  int type; // 0: cat, 1: dog
  int order; // higher means later

  Animal(int type, int order) {
    this->type = type;
    this->order = order;
  }
};

class AnimalShelter {
  public:
  queue<Animal> dogs, cats;
  int order;

  AnimalShelter() {
    order = 0;
  }

  void push(int type) {
    if(type == 1) { // dog
      Animal temp(1, order++);
      dogs.push(temp);
    } else { // dog
      Animal temp(0, order++);
      dogs.push(temp);
    }
  }

  void dequeueAny() {
    if(cats.front().order > dogs.front().order && cats.size() > 0) {
      this->dequeueCat();
    } else if(dogs.size() > 0) this->dequeueDog();
  }

  void dequeueCat() {
    cats.pop();
  }

  void dequeueDog() {
    dogs.pop();
  }
};

int main() {
  
}