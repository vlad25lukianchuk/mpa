#ifndef MPA_MPABASE_TOOLS_SINGLETON_H_
#define MPA_MPABASE_TOOLS_SINGLETON_H_

namespace mpa {

template<typename T>
class Singleton {
 public:
  static T&  Instance() {
    static T instance;
    return instance;
  }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

 protected:
  Singleton() = default;
};

} // namespace mpa

#endif // MPA_MPABASE_TOOLS_SINGLETON_H_
