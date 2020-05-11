#!/usr/bin/python

import os
import sys

tests = ['2+2', '2+2_var', 'if_else', 'interactive', 'println', 'scopes', 'local_scope', 'shadowed_modified', 'undecl_var']

def java_file(test):
	return test_id + '.java'

def dot_file(test):
	return test_id + '.dot'

def png_file(test):
	return test_id + '.png'

output_dir = "TestOutput"

executable = './bin/jc'
parse_command = "{executable} ./JavaExamples/{test}.java --ast ./{dir}/{test}.dot"
compile_and_run_command = "{executable} ./JavaExamples/{test}.java"
render_image_command = "dot -Tpng ./{dir}/{test}.dot -o {dir}/{test}.png"

def parse_cmd(test):
	return parse_command.format(executable=executable, test=test, dir=output_dir)

def render_cmd(test, dir):
	return render_image_command.format(test=test, dir=dir)

def run_cmd(test):
	return compile_and_run_command.format(executable=executable, test=test)

def render(test, dir):
	print("[*] Rendering \'{}\'".format(test))
	stream = os.popen(render_cmd(test, dir))
	print(stream.read())

def run_single_test(test, ast):
	print("-------------------------------------------")
	print("Running test \'{test}\'".format(test=test))

	if ast:
		stream = os.popen(parse_cmd(test))
		print(stream.read())
	else:
		stream = os.popen(run_cmd(test))
		print(stream.read())

def main(png_dir, ast=False):
	for test in tests:
		run_single_test(test, ast)

	if ast:
		for test in tests:
			render(test, png_dir)

def usage():
	print ("\tUsage: test.py [ast]\n")

if __name__ == "__main__":
    ast = False
        
    if len(sys.argv) > 1:
        if sys.argv[1] == "ast":
        	ast = True

    path = output_dir
    main(path, ast)
