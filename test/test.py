#!/usr/bin/env python

import sys
import os
import subprocess as cmd

debug_dir = "debug_test"
try:
    os.rmdir(debug_dir)
except:
    pass

def create_debug_file(file, content):
    if os.path.exists(debug_dir) == False:
        os.mkdir(debug_dir)
    file = open(file, "w")
    file.write(content)
    file.close()

def output_otool(file):
    com = "otool -t " + file
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

def output_ftotool(file):
    com = "../ft_otool " + file
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

def compare_otool_on_file(file):
    official = output_otool(file)
    mine = output_ftotool(file)
    if (mine == official):
        print ("OK")
    else:
        print ("ERROR");
        create_debug_file(debug_dir + "/" + file.replace('/', '_') + "_otool_off", official)
        create_debug_file(debug_dir + "/" + file.replace('/', '_') + "_otool_mine", mine)

def output_nm(file):
    com = "nm " + file
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

def output_ftnm(file):
    com = "../ft_nm " + file
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output

def compare_nm_on_file(file):
    official = output_nm(file)
    mine = output_ftnm(file)
    if (mine == official):
        print ("OK")
    else:
        print ("ERROR");
        create_debug_file(debug_dir + "/" + file.replace('/', '_') + "_nm_off", official)
        create_debug_file(debug_dir + "/" + file.replace('/', '_') + "_nm_mine", mine)

if __name__ == '__main__':
    sys.argv.pop(0)
    if len(sys.argv) != 0:
        print("OTOOL TEST ---------")
        for file in sys.argv:
             print(file + ":"),
             compare_otool_on_file(file)
        print("NM TEST ------------")
        for file in sys.argv:
             print(file + ":"),
             compare_nm_on_file(file)
