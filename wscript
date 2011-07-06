#! /usr/bin/env python
# encodeing: utf-8
# Richard Plangger 2011

top = '.'
out = '_build_'

def options(opt):
    opt.tool_options('compiler_cxx')
    opt.add_option('--release',action='store_true',default=False,help='build release version')

def configure(conf):
    conf.check_tool('compiler_cxx')

def build(bld):
    bld.recurse('box2d')
    bld.recurse('src')
