#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

#include "archive.h"

// template< typename CHILD_CLASS >
// class ArchiveMixin
//{
// public:
//    template< typename ARCH >
//    void serialize(ARCH* ar)
//    {
//        CHILD_CLASS* pThis = static_cast< CHILD_CLASS* >(this);
//    };
//};


enum {
    is_loading = 0,  //
    is_saving = 1,
};


// clang-format off
struct archive_reader
{
public:
    //archive_reader& read(string& val)   { printf("reader(string)%s\n", val.c_str());return *this;};
    archive_reader& read(uint8_t& val)  { printf("reader(uint8_t)%u\n", val);return *this;};
    archive_reader& read(uint16_t& val) { printf("reader(uint16_t)%u\n", val);return *this;};
    archive_reader& read(uint32_t& val) { printf("reader(uint32_t)%u\n", val);return *this;};
    archive_reader& read(uint64_t& val) { printf("reader(uint64_t)%llu\n", val);return *this;};
    archive_reader& read(int8_t& val)   { printf("reader(uint8_t)%d\n", val);return *this;};
    archive_reader& read(int16_t& val)  { printf("reader(int16_t)%d\n", val);return *this;};
    archive_reader& read(int32_t& val)  { printf("reader(int32_t)%d\n", val);return *this;};
    archive_reader& read(int64_t& val)  { printf("reader(int64_t)%lld\n", val);return *this;};
};
template <typename T>
archive_reader& operator>>(archive_reader& ar, T& val)
{
    return ar.read(val);
}

class archive_writer
{
public:
    //archive_writer& write(const string& val)   { printf("writer(string),%s\n", val.c_str());return *this;};
    archive_writer& write(const uint8_t& val)  { printf("writer(uint8_t)%u\n", val);return *this;};
    archive_writer& write(const uint16_t& val) { printf("writer(uint16_t)%u\n", val);return *this;};
    archive_writer& write(const uint32_t& val) { printf("writer(uint32_t)%u\n", val);return *this;};
    archive_writer& write(const uint64_t& val) { printf("writer(uint64_t)%llu\n", val);return *this;};
    archive_writer& write(const int8_t& val)   { printf("writer(uint8_t)%d\n", val);return *this;};
    archive_writer& write(const int16_t& val)  { printf("writer(int16_t)%d\n", val);return *this;};
    archive_writer& write(const int32_t& val)  { printf("writer(int32_t)%d\n", val);return *this;};
    archive_writer& write(const int64_t& val)  { printf("writer(int64_t)%lld\n", val);return *this;};
};
template <typename T>
archive_writer& operator<<(archive_writer& ar, T& val)
{
    return ar.write(val);
}

//template <typename T>
//void serialize(archive_reader& ar, T& val)  {ar>>val;}

//template <typename T>
//void serialize(archive_writer& ar, const T& val)  {ar<<val;}

void serialize(archive_reader& ar, uint8_t& val)  {ar>>val;}
void serialize(archive_reader& ar, uint16_t& val) {ar>>val;}
void serialize(archive_reader& ar, uint32_t& val) {ar>>val;}
void serialize(archive_reader& ar, uint64_t& val) {ar>>val;}
void serialize(archive_reader& ar, int8_t& val)   {ar>>val;}
void serialize(archive_reader& ar, int16_t& val)  {ar>>val;}
void serialize(archive_reader& ar, int32_t& val)  {ar>>val;}
void serialize(archive_reader& ar, int64_t& val)  {ar>>val;}

void serialize(archive_writer& ar, uint8_t& val)  {ar<<val;}
void serialize(archive_writer& ar, uint16_t& val) {ar<<val;}
void serialize(archive_writer& ar, uint32_t& val) {ar<<val;}
void serialize(archive_writer& ar, uint64_t& val) {ar<<val;}
void serialize(archive_writer& ar, int8_t& val)   {ar<<val;}
void serialize(archive_writer& ar, int16_t& val)  {ar<<val;}
void serialize(archive_writer& ar, int32_t& val)  {ar<<val;}
void serialize(archive_writer& ar, int64_t& val)  {ar<<val;}

// clang-format on

// void serialize(archive_reader& ar, T& obj)
//{
//    ar.read(obj);
//}

// void serialize(archive_writer& ar, T& obj)
//{
//    ar.write(obj);
//}


// template <typename T>
// archive_reader& operator^(archive_reader& ar, T& val)
//{
//    serialize(ar, val);
//    return ar;
//}

// template <typename T>
// archive_writer& operator^(archive_writer& ar, T& val)
//{
//    serialize(ar, val);
//    return ar;
//}

class MyDataBase
{
    ARCHIVE_CLASS(MyDataBase);
    string ARCHIVE(str1);
    string ARCHIVE(str2);

public:
    MyDataBase()
    {
        str1 = "str1";
        str2 = "str2";
    }
};


class MyDataDrive : public MyDataBase
{
    ARCHIVE_CLASS(MyDataDrive, MyDataBase);
    int ARCHIVE(int1);
    int ARCHIVE(int2);

public:
    MyDataDrive()
    {
        int1 = 111;
        int2 = 222;
    }
};

void serialize(archive_reader& ar, string& obj)
{
    printf("reader:string:%s\n", obj.c_str());
}

void serialize(archive_writer& ar, string& obj)
{
    printf("writer:string:%s\n", obj.c_str());
}


template <typename AR>
void serialize(AR& ar, MyDataBase& obj)
{
    serialize(ar, obj.str1);
    serialize(ar, obj.str2);
}

template <typename AR>
void serialize(AR& ar, MyDataDrive& obj)
{
    serialize<AR>(ar, (MyDataBase&)obj);
    serialize(ar, obj.int1);
    serialize(ar, obj.int2);
}


int main()
{
    MyDataBase base;
    MyDataDrive drive;

    archive_reader reader;
    archive_writer writer;

    serialize(reader, base);
    printf("1111\n");
    serialize(reader, drive);
    printf("2222\n");

    serialize(writer, base);
    printf("3333\n");
    serialize(writer, drive);

    return 0;
}
