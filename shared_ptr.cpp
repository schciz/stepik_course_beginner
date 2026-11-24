#include <iostream>
#include <cassert>
#include <memory>

struct Expression {
  static int alive_count;
  int number;

  Expression(int n = 0) : number(n) {
    ++alive_count;
  }
  Expression(const Expression& other) : number(other.number) {
    ++alive_count;
  }
  ~Expression() {
    --alive_count;
  }
};

int Expression::alive_count = 0;
// struct Expression;
// struct Number;
// struct BinaryOperation;

class ControlBlock {
public:
  ControlBlock() : references(1) {}

  int use_count() const {
    return references;
  }
  int IncrementReferences() {
    return ++references;
  }
  int DecrementReferences() {
    return --references;
  }
private:
  int references;
};

struct SharedPtr {
  // реализуйте следующие методы
  explicit SharedPtr(Expression *ptr = 0)
    : ptr_(ptr), control_block_(nullptr)
  {
    if (ptr_ != nullptr) {
      control_block_ = new ControlBlock;
    }
  }
  ~SharedPtr() {
    if (control_block_ != nullptr) {
      int references = control_block_->DecrementReferences();
      if (0 == references) {
        delete ptr_;
        delete control_block_;
      }
    }
  }
  SharedPtr(const SharedPtr & shared_ptr)
    : ptr_(nullptr), control_block_(nullptr)
  {
    if (shared_ptr.control_block_ != nullptr) {
      ptr_ = shared_ptr.ptr_;
      control_block_ = shared_ptr.control_block_;
      control_block_->IncrementReferences();
    }
  }
  SharedPtr& operator=(const SharedPtr &other) {
    if (this != &other) {
      if (control_block_ != nullptr) {
        int references = control_block_->DecrementReferences();
        if (0 == references) {
          delete ptr_;
          delete control_block_;
          ptr_ = nullptr;
          control_block_ = nullptr;
        }
      }
      ptr_ = other.ptr_;
      control_block_ = other.control_block_;
      if (control_block_ != nullptr) {
        control_block_->IncrementReferences();
      }
    }
    return *this;
  }
  Expression* get() const {
    return ptr_;
  }
  void reset(Expression *ptr = 0) {
    if (ptr_ != ptr) {
      if (control_block_ != nullptr) {
        int references = control_block_->DecrementReferences();
        if (0 == references) {
          delete ptr_;
          delete control_block_;
          ptr_ = nullptr;
          control_block_ = nullptr;
        }
      }
      ptr_ = ptr;
      if (ptr != nullptr) {
        control_block_ = new ControlBlock;
      } else {
        control_block_ = nullptr;
      }
    }
  }
  Expression& operator*() const {
    return *ptr_;
  }
  Expression* operator->() const {
    return ptr_;
  }
  int use_count() const {
    if (control_block_ != nullptr) {
      return control_block_->use_count();
    }
    return 0;
  }

private:
  Expression *ptr_;
  ControlBlock *control_block_;
};

int main() {
  // 1. Конструктор по умолчанию (пустой указатель)
  {
    SharedPtr p1;
    assert(p1.get() == nullptr);
    assert(p1.use_count() == 0);
  }

  // 2. Владение одним объектом и доступ к нему
  {
    SharedPtr p1(new Expression{42});
    assert(p1.get() != nullptr);
    assert(p1.use_count() == 1);
    assert((*p1).number == 42);
    assert(p1->number == 42);
  }

  // 3. Копирование непустого указателя
  {
    SharedPtr p1(new Expression{10});
    {
      SharedPtr p2(p1);
      assert(p1.get() == p2.get());
      assert(p1.use_count() == 2);
      assert(p2.use_count() == 2);
    }
    assert(p1.use_count() == 1);
    assert(p1->number == 10);
  }

  // 4. Копирование пустого указателя
  {
    SharedPtr p1;
    SharedPtr p2(p1);
    assert(p1.get() == nullptr);
    assert(p2.get() == nullptr);
    assert(p1.use_count() == 0);
    assert(p2.use_count() == 0);
  }

  // 5. Оператор присваивания
  {
    SharedPtr p1(new Expression{1});
    SharedPtr p2(new Expression{2});
    p2 = p1;
    assert(p1.get() == p2.get());
    assert(p1.use_count() == 2);
    assert(p2.use_count() == 2);
    assert(p2->number == 1);
  }

  // 6. Присваивание пустого указателя непустому и наоборот
  {
    SharedPtr p1(new Expression{5});
    SharedPtr p2;
    p1 = p2;
    assert(p1.get() == nullptr);
    assert(p1.use_count() == 0);

    SharedPtr p3(new Expression{7});
    p2 = p3;
    assert(p2.get() == p3.get());
    assert(p2.use_count() == 2);
  }

  // 7. Самоприсваивание
  {
    SharedPtr p1(new Expression{99});
    p1 = p1;
    assert(p1.get() != nullptr);
    assert(p1.use_count() == 1);
    assert(p1->number == 99);
  }

  // 8. Метод reset()
  {
    SharedPtr p1(new Expression{100});
    SharedPtr p2(p1);
    assert(p1.use_count() == 2);

    p1.reset(new Expression{200});
    assert(p1->number == 200);
    assert(p1.use_count() == 1);
    assert(p2->number == 100);
    assert(p2.use_count() == 1);

    p1.reset();
    assert(p1.get() == nullptr);
    assert(p1.use_count() == 0);
  }

  // 9. Сброс на тот же самый сырой указатель (reset(p.get()))
  {
    SharedPtr p1(new Expression{55});
    p1.reset(p1.get());
    assert(p1.get() != nullptr);
    assert(p1.use_count() == 1);
    assert(p1->number == 55);
  }

  // 10. Работа с константным SharedPtr
  {
    const SharedPtr p1(new Expression{77});
    assert(p1.get() != nullptr);
    assert(p1.use_count() == 1);
    assert((*p1).number == 77);
    assert(p1->number == 77);
  }
  std::cout << "Все базовые тесты пройдены!\n";

   // 11. Контроль утечек при базовых операциях
  {
    assert(Expression::alive_count == 0);
    {
      SharedPtr p1(new Expression{10});
      SharedPtr p2(p1);
      SharedPtr p3;
      p3 = p2;
      assert(Expression::alive_count == 1);
    }
    assert(Expression::alive_count == 0);
  }

  // 12. Сброс одного из нескольких владельцев (reset на nullptr и на новый объект)
  {
    SharedPtr p1(new Expression{1});
    SharedPtr p2(p1);
    SharedPtr p3(p1);
    assert(Expression::alive_count == 1);

    p2.reset();
    assert(p2.get() == nullptr);
    std::cout << p2.use_count() << '\n';
    assert(p2.use_count() == 0);
    assert(p1.use_count() == 2);
    assert(p3.use_count() == 2);
    assert(Expression::alive_count == 1);

    p3.reset(new Expression{2});
    assert(Expression::alive_count == 2);
    assert(p3.use_count() == 1);
    assert(p1.use_count() == 1);
    assert(p1->number == 1);
    assert(p3->number == 2);
  }
  assert(Expression::alive_count == 0);

  // 13. Сброс пустого указателя (reset на пустом SharedPtr)
  {
    SharedPtr p1;
    p1.reset();
    assert(p1.get() == nullptr);
    assert(p1.use_count() == 0);
    assert(Expression::alive_count == 0);

    p1.reset(new Expression{15});
    assert(p1.get() != nullptr);
    assert(p1.use_count() == 1);
    assert(Expression::alive_count == 1);
  }
  assert(Expression::alive_count == 0);

  // 14. Присваивание между указателями, уже владеющими одним и тем же объектом
  {
    SharedPtr p1(new Expression{42});
    SharedPtr p2(p1);
    assert(p1.use_count() == 2);
    assert(Expression::alive_count == 1);

    p1 = p2;
    assert(p1.get() == p2.get());
    assert(p1.use_count() == 2);
    assert(p2.use_count() == 2);
    assert(p1->number == 42);
    assert(Expression::alive_count == 1);
  }
  assert(Expression::alive_count == 0);

  // 15. Цепочечное присваивание (a = b = c)
  {
    SharedPtr p1(new Expression{100});
    SharedPtr p2(new Expression{200});
    SharedPtr p3;

    p3 = p2 = p1;
    assert(Expression::alive_count == 1);
    assert(p1.use_count() == 3);
    assert(p2.use_count() == 3);
    assert(p3.use_count() == 3);
    assert(p3->number == 100);
  }
  assert(Expression::alive_count == 0);

  // 16. Сброс на тот же самый сырой указатель при наличии других владельцев
  {
    SharedPtr p1(new Expression{88});
    SharedPtr p2(p1);
    assert(p1.use_count() == 2);
    assert(Expression::alive_count == 1);

    p1.reset(p1.get());
    assert(Expression::alive_count == 1);
    assert(p1.use_count() == 2);
    assert(p2.use_count() == 2);
    assert(p1->number == 88);
  }
  assert(Expression::alive_count == 0);

  // 17. Изменение объекта через один указатель и чтение через другой
  {
    SharedPtr p1(new Expression{5});
    SharedPtr p2(p1);
    p1->number = 777;
    assert(p2->number == 777);
    (*p2).number = 888;
    assert(p1->number == 888);
  }
  assert(Expression::alive_count == 0);

  // 18. Передача по значению и возврат из функции
  {
    auto pass_by_value = [](SharedPtr ptr, int expected_count) {
      assert(ptr.use_count() == expected_count);
      return ptr;
    };

    SharedPtr p1(new Expression{33});
    assert(p1.use_count() == 1);
    SharedPtr p2 = pass_by_value(p1, 2);
    assert(p1.use_count() == 2);
    assert(p2.use_count() == 2);
    assert(Expression::alive_count == 1);
  }
  assert(Expression::alive_count == 0);

  std::cout << "Все дополнительные тесты пройдены!\n";
  return 0;
}
// int main() {
//   std::cout << "Test 1\n";
//   SharedPtr ptr1(new Expression);
//   SharedPtr ptr2(new Expression);
//   std::cout << ptr1.use_count() << ' ' << ptr2.use_count() << '\n';
//   ptr1 = ptr2;
//   std::cout << ptr1.use_count() << ' ' << ptr2.use_count() << '\n';
//   if (ptr1.get()) {
//     std::cout << ptr1->number << '\n';
//   }
//   if (ptr2.get()) {
//     std::cout << ptr2->number << '\n';
//   }
//   std::cout << "Test 2\n";
//   SharedPtr ptr3(nullptr);
//   SharedPtr ptr4(new Expression);
//   std::cout << ptr3.use_count() << ' ' << ptr4.use_count() << '\n';
//   ptr3 = ptr4;
//   std::cout << ptr3.use_count() << ' ' << ptr4.use_count() << '\n';
//   if (ptr3.get()) {
//     std::cout << ptr3->number << '\n';
//   }
//   if (ptr4.get()) {
//     std::cout << ptr4->number << '\n';
//   }
//   std::cout << "Test 3\n";
//   SharedPtr ptr5(new Expression);
//   SharedPtr ptr6(nullptr);
//   std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   ptr5 = ptr6;
//   std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   if (ptr5.get()) {
//     std::cout << ptr5->number << '\n';
//   }
//   if (ptr6.get()) {
//     std::cout << ptr6->number << '\n';
//   }
//   std::cout << "Test 4\n";
//   SharedPtr ptr7(nullptr);
//   SharedPtr ptr8(nullptr);
//   std::cout << ptr7.use_count() << ' ' << ptr8.use_count() << '\n';
//   if (ptr7.get()) {
//     std::cout << ptr7->number << '\n';
//   }
//   if (ptr8.get()) {
//     std::cout << ptr8->number << '\n';
//   }
//   std::cout << "Test 5\n";
//   std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   ptr5.reset(new Expression);
//   std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   ptr6.reset(new Expression);
//   std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   // ptr5.reset(nullptr);
//   // std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
//   // ptr6.reset(nullptr);
//   // std::cout << ptr5.use_count() << ' ' << ptr6.use_count() << '\n';
// }

