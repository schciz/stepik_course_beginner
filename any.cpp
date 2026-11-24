
#include <algorithm>
#include <iostream>
struct ICloneable {
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : ICloneable {
  T data_;
  ValueHolder(T data): data_(data) {}
  ICloneable* clone() const override {
    ICloneable* cloned = new ValueHolder(*this);
    return cloned;
  }
};

// // Эти классы реализовывать заново не нужно
// struct ICloneable;
//
// // Поле data_ типа T в классе ValueHolder
// // открыто, к нему можно обращаться
// template <typename T>
// struct ValueHolder;

class Any {
public:
  // В классе Any должен быть конструктор,
  // который можно вызвать без параметров,
  // чтобы работал следующий код:
  //    Any empty; // empty ничего не хранит
  Any() : holder(nullptr) { }

  // В классе Any должен быть шаблонный
  // конструктор от одного параметра, чтобы
  // можно было создавать объекты типа Any,
  // например, следующим образом:
  //    Any i(10); // i хранит значение 10
  template<typename T>
  Any(T value) : holder(new ValueHolder<T>(value)) { }

  // Не забудьте про деструктор. Все выделенные
  // ресурсы нужно освободить.
  ~Any() {
    delete holder;
  }

  // В классе Any также должен быть конструктор
  // копирования (вам поможет метод clone
  // интерфейса ICloneable)
  Any(const Any& other) : holder(nullptr) {
    if (other.holder != nullptr) {
      holder = other.holder->clone();
    }
  }
  
  friend void swap(Any& left, Any& right) {
    std::swap(left.holder, right.holder);
  }
  // В классе должен быть оператор присваивания и/или
  // шаблонный оператор присваивания, чтобы работал
  // следующий код:
  //    Any copy(i); // copy хранит 10, как и i
  //    empty = copy; // empty хранит 10, как и copy
  //    empty = 0; // а теперь empty хранит 0
  Any& operator=(Any other) {
    swap(*this, other);
    return *this;
  }

  // Ну и наконец, мы хотим уметь получать хранимое
  // значение, для этого определите в классе Any
  // шаблонный метод cast, который возвращает
  // указатель на хранимое значение, или нулевой
  // указатель в случае несоответствия типов или
  // если объект Any ничего не хранит:
  //    int *iptr = i.cast<int>(); // *iptr == 10
  //    char *cptr = i.cast<char>(); // cptr == 0,
  //        // потому что i хранит int, а не char
  //    Any empty2;
  //    int *p = empty2.cast<int>(); // p == 0
  template<typename T>
  T* cast() {
    ValueHolder<T>* casted = dynamic_cast<ValueHolder<T>*>(holder);
    if (casted != nullptr) {
      return &casted->data_;
    }
    return nullptr;
  }
private:
  ICloneable *holder;
  // При реализации используйте оператор dynamic_cast.
  //
  // Допустим у вас есть два наследника класса Base: Derived1 
  // и Derived2. Кроме того у вас есть указать baseptr
  // типа Base*. Как проверить указывает ли этот указатель на
  // самом деле на объект класса Derived1 или на объект 
  // класса Derived2? Для этого можно воспользоваться dynamic_cast-ом:
  //
  // Derived1 *derived1ptr = dynamic_cast<Derived1*>(baseptr);
  //
  // Если derived1ptr не равен 0, то  baseptr на самом деле
  // указывал на объект класса Derived1, если же derivedptr равен 0,
  // то baseptr на самом деле указывал на объкт какого-то другого 
  // класса (например, Derived2). Это можно проверить так:
  //
  // Derived2 *derived2ptr = dynamic_cast<Derived2*>(baseptr);
  //
  // dynamic_cast работает только, если в классе есть хотя бы
  // один виртуальный метод, и в шаблоне ValueHolder такой
  // как раз имеется.
};

int main() {
  Any ten(10);
  Any empty(5.5f);
  std::cout << *ten.cast<int>() << ' ' << *empty.cast<float>() << '\n';
}


