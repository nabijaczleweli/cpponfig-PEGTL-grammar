#!/usr/bin/env python


def options(opts):
	opts.load('compiler_cxx')

def configure(conf):
	conf.load('compiler_cxx')
	conf.env.append_value('INCLUDES', ['.', '../include/cpponfig-grammar', '../PEGTL'])
	conf.check(features='cxx cxxprogram', cxxflags=['-std=c++14', '-Wall', '-Wextra', '-O3', '-pedantic', '-pipe'], uselib_store='M')

def build(buld):
	buld(features='cxx cxxprogram', source=buld.path.ant_glob('test/**/*.cpp'), target='cpponfig-grammar_test', use=['M'])
