#ifndef ARCHIVE_H
#define ARCHIVE_H


#define WM_MACRO_MAP2_(_1, _2, name, ...) name
#define WM_MACRO_MAP3_(_1, _2, _3, name, ...) name
#define WM_MACRO_MAP4_(_1, _2, _3, _4, name, ...) name
#define WM_MACRO_MAP5_(_1, _2, _3, _4, _5, name, ...) name

// clang-format off
//#define WM_ARCLASS1_(name) class name
//#define WM_ARCLASS2_(name, parent) class name : public parent
//#define WM_ARCLASS3_(name, parent1, parent2) class name : public parent1, public parent2
//#define ARCHIVE_CLASS(...) WM_MACRO_MAP3_(__VA_ARGS__, WM_ARCLASS3_, WM_ARCLASS2_, WM_ARCLASS1_)(__VA_ARGS__)

#define WM_ARCLASS1_(name) template< typename AR >  friend void serialize(AR& ar, name& obj)
#define WM_ARCLASS2_(name, parent) template< typename AR >  friend void serialize(AR& ar, name& obj)
#define WM_ARCLASS3_(name, parent1, parent2) template< typename AR >  friend void serialize(AR& ar, name& obj)
#define ARCHIVE_CLASS(...) WM_MACRO_MAP3_(__VA_ARGS__, WM_ARCLASS3_, WM_ARCLASS2_, WM_ARCLASS1_)(__VA_ARGS__)

#define ARCHIVE_DECLARE(name)  template< typename AR >  friend void serialize(AR& ar, name& obj);

#define ARCHIVE(field) field
// clang-format on


// class MyDataBase;
// template<>
// class ArchiveMixin< MyDataBase >
//{
// public:
//    template< typename ARCH >
//    void serialize(ARCH& ar)
//    {
//        MyDataBase* pThis = static_cast< MyDataBase* >(this);
//    }
//};


// using namespace std;
// template<typename archive, typename T>
// void load(archive& ar, T t)
//{
//
//}

#endif  // ARCHIVE_H
