// The MIT License (MIT)

// Copyright (c) 2015 nabijaczleweli

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.


#include "grammar.hpp"
#include <iostream>
#include <string>

#define TEST_RULE(rule, var, name)                                                                                            \
	do {                                                                                                                        \
		size_t idx{};                                                                                                             \
		for(const auto & tststr : var) {                                                                                          \
			const auto parseres = pegtl::parse<pegtl::seq<cpponfig::grammar::rule, pegtl::eof>>(tststr, #var "#" + to_string(idx)); \
			cout << name << " #" << idx << ": " << parseres << '\n';                                                                \
			result += !parseres;                                                                                                    \
			++idx;                                                                                                                  \
		}                                                                                                                         \
	} while(false)


using namespace std;


static const string comment_test[]      = {"#ffdsa", "# _9238.,;'[]1`", "#"};
static const string line_comment_test[] = {"#fasdfsadfasdf\n", "  \t\t \t\t \t    # #$%^&*(00-'\\asd`\n", "#\n"};
static const string sof_comments_test[] = {"#fasdfsadfasdf\n"
                                           "  \t\t \t\t \t    # #$%^&*(00-'\\asd`\n"
                                           "#\n",
                                           "#fasdfsadfasdf\n"
                                           "  \t\t \t\t \t    # #$%^&*(00-'\\asd`\n"
                                           "#",
                                           "#fasdfsadfasdf\n"
                                           "  \t\t \t\t \t    # #$%^&*(00-'\\asd`\n"
                                           "#\n\n",
                                           "#fasdfsadfasdf\n"
                                           "  \t\t \t\t \t    # #$%^&*(00-'\\asd`\n"
                                           "#\n\n\n"};


int main() {
	cout << boolalpha;

	int result{};

	TEST_RULE(comment, comment_test, "Comment");
	TEST_RULE(line_comment, line_comment_test, "Line comment");
	TEST_RULE(sof_comments, sof_comments_test, "SOF comment");

	return result;
}
