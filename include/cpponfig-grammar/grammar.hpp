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


#pragma once


#include <iostream>
#include "pegtl.hh"


namespace cpponfiguration {
	namespace grammar {
		using namespace pegtl;

		// not_space ::= '!'..'~'
		struct not_space : range<'!', '~'> {};  // `print` except ' '

		// name ::= '"' .* '"'
		struct name : if_must<one<'"'>, until<one<'"'>, print>> {};


		// comment ::= '#' .*
		struct comment : seq<string<'#'>, star<not_one<'\n'>>> {};

		// commented ::= \s+ [comment]
		struct commented : opt<seq<plus<blank>, comment>> {};

		// line_comment ::= \s* comment eol
		struct line_comment : seq<star<blank>, comment, eolf> {};

		// sof_comments ::= line_comment* eol*
		struct sof_comments : seq<star<line_comment>, star<eolf>> {};


		// property ::= name '=' name
		struct property : seq<name, string<'='>, name> {};

		// property_line ::= \s* property commented eol
		struct property_line : seq<star<blank>, property, commented, eolf> {};


		// category ::= [name \s*] { commented eol
		//                      property_line*
		//                      } eol+
		struct category : seq<opt<name>, star<blank>, string<'{'>, commented, eolf,  //
		                      star<property_line>,                                   //
		                      string<'}'>, eolf> {};


		// file ::= sof_comments
		//          category*
		//          [eol comment]
		//          eol*
		//          eof
		struct file : seq<sof_comments,        //
		                  star<category>,      //
		                  opt<eolf, comment>,  //
		                  star<eol>,           //
		                  eof> {};


		template <class Rule>
		struct action : nothing<Rule> {};

		template <>
		struct action<line_comment> {
			template <class T0, class LineCommentsAcc, class... TT>
			static void apply(const input & in, T0 &&, LineCommentsAcc & acc, TT &&...) {
				std::cout << "line_comment:\"" << (std::find(in.begin(), in.end(), '#') + 1) << "\"XXXXX\n";
				acc.emplace_back(std::find_if(std::find(in.begin(), in.end(), '#') + 1, in.end(), [](auto c) { return c != ' ' && c != '\t'; }));
			}
		};

		template <>
		struct action<sof_comments> {
			template <class SOFComments, class LineCommentsAcc, class... TT>
			static void apply(const input &, SOFComments & comments, LineCommentsAcc & acc, TT &&...) {
				std::move(comments.begin(), comments.end(), std::back_inserter(comments));
				acc.clear();
			}
		};
	}
}

namespace cpponfig = cpponfiguration;
