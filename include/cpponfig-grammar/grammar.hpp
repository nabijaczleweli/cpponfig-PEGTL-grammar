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


#include "pegtl.hh"


namespace cpponfiguration {
	namespace grammar {
		using namespace pegtl;

		// not_space ::= '!'..'~'
		struct not_space : range<'!', '~'> {};  // pretty much all printables


		// comment ::= '#' .*
		struct comment : seq<string<'#'>, star<any>> {};

		// commented ::= \s+ comment(opt)
		struct commented : opt<seq<plus<blank>, comment>> {};

		// line_comment ::= \s* '#' .* eol
		struct line_comment : seq<star<blank>, comment, eolf> {};

		// sof_comments ::= line_comment* eol*
		struct sof_comments : seq<star<line_comment>, star<eolf>> {};


		// property ::= not_space+ \s+ '=' \s+ not_space+
		struct property : seq<plus<not_space>, blank, string<'='>, blank, plus<not_space>> {};

		// property_line ::= \s* property commented eol
		struct property_line : seq<star<blank>, property, commented, eolf> {};


		// unnamed_category ::= \s* { commented eol
		//                      property_line*
		//                      } eol+
		struct unnamed_category : seq<star<blank>, string<'{'>, commented, eolf,  //
		                              star<property_line>,                        //
		                              string<'}'>, plus<eolf>> {};
	}
}

namespace cpponfig = cpponfiguration;
