// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<class T> struct X0 : public T { };

template <class T>
struct X1
{
     static T & instance;
    static void use(T const &) {}
     static T & get() {
        static X0<T> t;
        use(instance);
        return static_cast<T &>(t);
    }
};

template<class T> T & X1<T>::instance = X1<T>::get();

class A { };
class B : public A { };

template<typename T> struct X2 {};
X2< B > bg = X1< X2< B > >::get(); 
X2< A > ag = X1< X2< A > >::get();
