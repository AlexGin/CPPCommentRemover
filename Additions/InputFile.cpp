// IfConstexpr.cpp : Defines the entry point for the console application.
// This example from: "C++17 STL Cookbook" by Jacek Galowicz (from chapter 1)
// https://www.amazon.com/STL-Cookbook-enhancements-programming-expressions/dp/178712049X
/* Some comments and test-strings were added by Alexander Ginzburg */
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>

template <typename T>
class addable
{
    T val;
	/* This is OLD Style C/C++ comment. 
		This Style used in the old K&R and ANSI-C standards */
public:
    addable(T v) : val{ v } {}

#if 0
    /* The C++11 way */
    template <typename U>
    std::enable_if_t<!std::is_same<T, std::vector<U>>::value, T>
        add(U x) const { return val + x; }

    template <typename U>
    std::enable_if_t<std::is_same<T, std::vector<U>>::value, std::vector<U>>
        add(U x) const {
        auto copy = val;
        for (auto &n : copy) {
            n += x;
        }
        return copy;
    }
#else
	// This is NEW Style comment 
    // The C++17 way
    template <typename U>
    T add(U x) const {
        if constexpr (std::is_same_v<T, std::vector<U>>) {
            auto copy = val;
            for (auto &n : copy) {
                n += x;
            }
            return copy;
        }
        else {
            return val + x;
        }
    }
#endif

};

template<typename V>
void ShowVector(const std::vector<V>& vectInp)
{
    bool bFirstPass = true;
    for (V value : vectInp)
    {
        if (!bFirstPass)
            std::cout << ",";

        std::cout << value;
        bFirstPass = false;
    }
    std::cout << std::endl;
}

int main()
{
	/* The 'main' - it is first function,
		called in the C/C++ application */
	double dbTestValue = 10.0 / 2.0; // Test for "valid" (no-comment) symbol '/'
    using namespace std::string_literals;

    assert(addable<int>{2}.add(3) == 5);
    assert(addable<std::string>{"aa"s}.add("bb"s) == "aabb"s);

    std::cout << addable<int>{2}.add(3) << std::endl;

    std::vector<int> v1{ 1, 2, 3 };
    ShowVector(v1);
    std::vector<int> v2{ 11, 12, 13 };
    ShowVector(v2);
    // assert(addable<std::vector<int>>{v1}.add(10) == v2);
    std::vector<int> v3 = addable<std::vector<int>>{v1}.add(10);
    ShowVector(v3);

    std::vector<std::string> sv1{ "a", "b", "c" };
    ShowVector(sv1);
    std::vector<std::string> sv2{ "az", "bz", "cz" };
    ShowVector(sv2);
    // assert(addable<std::vector<std::string>>{sv1}.add("z"s) == sv2);
    std::vector<std::string> sv3 = addable<std::vector<std::string>>{sv1}.add("z"s);
    ShowVector(sv3);

    getchar();
    // If our C/C++ application exit correctly, return-code equal zero:
    return 0;
}
